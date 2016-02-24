#ifndef SUNSHINE_ENGINE_PATH_TRACER_H_
#define SUNSHINE_ENGINE_PATH_TRACER_H_

#include <memory>

#include <thread>
#include <queue>
#include <mutex>

#include "engine/renderer.h"
#include "engine/image.h"

#include "../scene/camera.h"
#include "../scene.h"
#include "../scenegraph.h"
#include "../rng.h"

namespace sunshine {
namespace engine{

/*!
    \brief Handles rendering of a single pixel
*/
class PathTracer
{
public:
    PathTracer(const SceneGraph* sceneGraph, const Scene* scene);

    glm::vec3 pixelColor(float x, float y, RNG &rng);

private:
    glm::vec3 rad(const Ray &r, const float t0, const float t1, RNG &rng) const;

    glm::vec3 computeRadiance(
        const HitRecord &recX,
        const glm::vec3 &theta,
        int bounces,
        RNG &rng
        ) const;

    glm::vec3 Phong_BRDF(
        const glm::vec3 &x,
        const glm::vec3 &Nx,
        const glm::vec3 &outDir,
        const glm::vec3 &inDir,
        const Material* surfaceMat
        ) const;

    glm::vec3 directIllumination(
        const HitRecord &recX,
        const glm::vec3 &theta,
        RNG &rng
        ) const;

    glm::vec3 indirectIllumination(
        const HitRecord &recX,
        const glm::vec3 &theta,
        int bounces,
        RNG &rng
        ) const;

    float radianceTransfer(const HitRecord &recX, const HitRecord &recY) const;

    const Camera mCamera;
    const SceneGraph *mSceneGraph;
    const Scene *mScene;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_PATH_TRACER_H_