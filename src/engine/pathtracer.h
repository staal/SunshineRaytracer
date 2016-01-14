#ifndef PATH_TRACER_H_
#define PATH_TRACER_H_

#include "image.h"
#include "scene/camera.h"
#include "scene.h"
#include "scenegraph.h"
#include "rng.h"

namespace sunshine {

class PathTracer {
public:
    PathTracer(std::shared_ptr<Image> image, SceneGraph* sceneGraph, Scene* scene);
    ~PathTracer();
    void render();
    const std::string getVersion();

private:
    glm::vec3 pixelColor(float x, float y, int samples);
    glm::vec3 rad(const Ray &r, const float t0, const float t1);
    glm::vec3 computeRadiance(HitRecord &recX, glm::vec3 theta, int bounces);
    glm::vec3 Phong_BRDF(glm::vec3 x, glm::vec3 Nx, glm::vec3 outDir, glm::vec3 inDir, Material* surfaceMat);
    glm::vec3 directIllumination(HitRecord &recX, glm::vec3 theta);
    glm::vec3 indirectIllumination(HitRecord &recX, glm::vec3 theta, int bounces);
    float radianceTransfer(HitRecord &recX, HitRecord &recY);

    RNG mRng;
    Camera mCamera;
    std::shared_ptr<Image> mImage;
    SceneGraph *mSceneGraph;
    Scene *mScene;
};


} // namespace sunshine
#endif // !PATH_TRACER_H_