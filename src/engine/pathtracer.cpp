#include <math.h>
#include <iostream>

#include "pathtracer.h"
#include "engineversion.h"

namespace sunshine {
namespace engine{

#define DEBUG 1
#define NUM_SHADOW_RAYS 1
#define NUM_INDIRE_RAYS 1

using namespace glm;


// *****************************************************************************
PathTracer::PathTracer(std::shared_ptr<Image> image, SceneGraph* sceneGraph,
    Scene* scene) :
    mImage(std::move(image)), mScene(scene), mSceneGraph(sceneGraph), mRng(0),
    mCamera(Camera(scene->cameraPosition, scene->cameraViewDirection,
    scene->cameraUp, scene->cameraFov, scene->width, scene->height))
{
    mRng.seed(scene->seed);
}


// *****************************************************************************
/*
Compute the entire image,
samples : Number of samples per pixel
*/
void PathTracer::render()
{
    int p = mScene->width / 10;
    int progress = 0;
    for (int y = 0; y < mScene->height; y++) {
        if (y % p == 0) {
            std::cout << "\t" << progress * 10 << "% done" << std::endl;
            progress++;
        }

        for (int x = 0; x < mScene->width; x++) {
            //For each pixel
            vec3 color = pixelColor((float)x, (float)y, mScene->samplesPerPixel);

            //Clamp the color
            color = glm::clamp(color, 0.0f, 1.0f);
            mImage->setPixel(x, y, color);
        }
    }
}


// *****************************************************************************
const std::string PathTracer::getVersion()
{
    return engineVersion;
}


// *****************************************************************************
/*
Computes the flux for a given pixel
x, y : pixel coordinate on the image plane
*/
vec3 PathTracer::pixelColor(float x, float y, int samples)
{
    vec3 radiance(0.0f, 0.0f, 0.0f);

    //H = integral for now, just box filtering
    for (int i = 0; i < samples; i++) {
        float sample_x = x + mRng.GetRandom01() - 0.5f;
        float sample_y = y + mRng.GetRandom01() - 0.5f;

        //Generate primary ray
        Ray r = mCamera.getRay(sample_x, sample_y);
        radiance = radiance + rad(r, 0.0f, std::numeric_limits<float>::infinity());
    }

    radiance /= samples;

    return radiance;
}


// *****************************************************************************
vec3 PathTracer::rad(const Ray &r, float t0, float t1)
{
    HitRecord rec;

    //Find closest intersection point x of ray with scene
    if (mSceneGraph->hit(r, t0, t1, rec)) {
        //Compute radiance
        vec3 theta = normalize(r.origin - rec.point);
        return rec.surface->material->Ke + computeRadiance(rec, theta, 0);
    }

    //Ambient
    return vec3(0.0f, 0.0f, 0.0f);
}


// *****************************************************************************
/*
Compute radiance in direction @theta at point @recX
*/
vec3 PathTracer::computeRadiance(HitRecord &recX, vec3 theta, int bounces)
{
    vec3 dir = directIllumination(recX, theta);
    vec3 ind = indirectIllumination(recX, theta, bounces);

    //return estimated radiance
    return dir + ind;
}


// *****************************************************************************
vec3 PathTracer::directIllumination(HitRecord &recX, vec3 theta)
{
    vec3 estimatedRadiance(0.0f);

    for (int i = 0; i < NUM_SHADOW_RAYS; i++) {
        float light_pdf;
        HitRecord recY;
        mSceneGraph->getLight()->generatePoint(recY, &light_pdf, &mRng);

        vec3 brdf = Phong_BRDF(recX.point,
            recX.normal,
            theta, //indir
            normalize(recY.point - recX.point), //outdir
            recX.surface->material);

        float transfer = radianceTransfer(recX, recY);

        vec3 emission = recY.surface->material->Ke;

#if DEBUG
        if (transfer > 1.0)
            throw "Critical";
#endif

        estimatedRadiance += emission * brdf * transfer / light_pdf;
    }

    float invRaySum = 1.0f / (NUM_SHADOW_RAYS + NUM_INDIRE_RAYS);
    return estimatedRadiance * invRaySum;
}


// *****************************************************************************
vec3 generateHemisphereDirection(vec3 &normal, float* pdf, RNG* rng)
{
    //sample hemisphere
    //Based on http://people.cs.kuleuven.be/~philip.dutre/GI/TotalCompendium.pdf

    const float pi = 3.14159265f;

    float azimuth = 2 * pi * rng->GetRandom01();

    float r2 = rng->GetRandom01();

    //We dont like 0.000 samples, the PDF is 0 for this value!
    while (r2 == 0.00000f) {
        r2 = rng->GetRandom01();
    }

    float x = cos(azimuth)*sqrtf(1.0f - r2);
    float y = sin(azimuth)*sqrtf(1.0f - r2);
    float z = sqrtf(r2);

    //Compute world space
    vec3 tangent = cross(normal, vec3(1, 0, 0));
    if (length(tangent) < 0.1)
        tangent = cross(normal, vec3(0, 1, 0));
    vec3 bitangent = cross(normal, tangent);

    //Transform
    vec3 psi = x * tangent + y * bitangent + z * normal;

#if DEBUG
    float dotf = dot(psi, normal);
    if (dotf < 0.0f)
        throw "critical";
#endif
    //Cosine lobe pdf!
    *pdf = sqrtf(r2) / pi; //cosf(acosf(srtq(r2)) / PI;

    return psi;
}


// *****************************************************************************
vec3 PathTracer::indirectIllumination(HitRecord &recX, vec3 theta, int bounces)
{
    vec3 estimatedRadiance(0.0f);

    //Make sure we get atleast _recursion_depth bounces (the exponent is negative till we do so).
    //1 - (1 - abs)^n
    float absorbtion = 1.0f - powf(1.0f - mScene->absorbtion, (float)bounces - mScene->recursionDepth);
    if (absorbtion < 0.0)
        absorbtion = 0.0;

    float r = mRng.GetRandom01();
    if (r >= absorbtion) //Terminate by russian roulette
    {
        for (int i = 0; i < NUM_INDIRE_RAYS; i++) {
            //sample hemisphere
            float pdf_psi;
            vec3 psi = generateHemisphereDirection(recX.normal, &pdf_psi, &mRng);

            //Compute outbound ray
            Ray r = Ray(recX.point, psi);
            HitRecord recY;

            vec3 brdf = Phong_BRDF(recX.point,
                recX.normal,
                theta, //indir
                psi, //outdir
                recX.surface->material);

            //Compute the radiance comming from -psi. Ambient if scene is missed.
            vec3 radiance;
            if (mSceneGraph->hit(r, mScene->epsilon, std::numeric_limits<float>::infinity(), recY)) {
                radiance = computeRadiance(recY, -psi, ++bounces);
            } else {
                radiance = recX.surface->material->Ka;
            }

            estimatedRadiance += radiance * brdf * dot(recX.normal, psi) / pdf_psi;
        }
    }

    //Normalize radiance by multiplying inverse sum of rays

    float invRaySum = 1.0f / (NUM_SHADOW_RAYS + NUM_INDIRE_RAYS);
    return estimatedRadiance * invRaySum;
}


// *****************************************************************************
/*
Compute the radiance transfer G(x,y)V(x,y)
*/
float PathTracer::radianceTransfer(HitRecord &recX, HitRecord &recY)
{
    if (mSceneGraph->visible(recX, recY)) //V(x,y)
    {
        vec3 xy = recY.point - recX.point;
        float len = length(xy);
        vec3 direction = xy / len;

        //G(x,y)
        float transfer = dot(recX.normal, direction)*dot(recY.normal, -direction)
            / pow(len, 2);
        return (transfer >= 0.0f) ? transfer : 0.0f;
    }
    return 0.0f; //Not visible
}


// *****************************************************************************
vec3 PathTracer::Phong_BRDF(vec3 x, vec3 Nx, vec3 outDir, vec3 inDir, Material* surfaceMat)
{
    //Modified blinn phong (p 39 AGI)
    vec3 half_vec = normalize(inDir + outDir);

    vec3 result = surfaceMat->Ks*powf(dot(Nx, half_vec), surfaceMat->Ns) + surfaceMat->Kd;

#if DEBUG
    if (result.r < 0.0 || result.g < 0.0 || result.b < 0.0)
        throw "Critical";
#endif

    return result;
}


} // namespace engine
} // namespace sunshine