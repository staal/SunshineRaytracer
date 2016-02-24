#include "lightsource.h"

namespace sunshine {
namespace engine{


// *****************************************************************************
LightSource::LightSource(Triangle* t1, Triangle* t2)
{
    int numTriangles = 2; //Support for more than 2 later :-)

    mTriangle[0] = t1;
    mTriangle[1] = t2;

    //Generate uniform PDF's
    for (int i = 0; i < numTriangles; i++) {
        float area = mTriangle[i]->area();
        mPdf[i] = 1.0f / numTriangles * 1.0f / area;
    }
}


// *****************************************************************************
void LightSource::generatePoint(HitRecord& rec, float* pdf, RNG &rng) const
{
    float r = rng.GetRandom01();

    float u = rng.GetRandom01(); 
    float v = rng.GetRandom01();

    if (u + v >= 1.0f) {
        u = 1.0f - u;
        v = 1.0f - v;
    }

    int index;
    if (r < 0.5)
        index = 0;
    else
        index = 1;

    rec.point = mTriangle[index]->v1.v +
        u * (mTriangle[index]->v2.v - mTriangle[index]->v1.v) +
        v * (mTriangle[index]->v3.v - mTriangle[index]->v1.v);

    rec.surface = mTriangle[index];
    rec.normal = mTriangle[index]->v1.normal;
    *pdf = mPdf[index];
}

} // namespace engine
} // namespace sunshine
