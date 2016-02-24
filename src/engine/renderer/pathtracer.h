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

struct Job {
    int start_x = 0;
    int start_y = 0;
    int end_x = 0;
    int end_y = 0;
};
using Jobs = std::queue<Job>;

class PathTracer : public Renderer
{
public:
    PathTracer(std::shared_ptr<Image> image,
        const SceneGraph* sceneGraph, const Scene* scene);
    ~PathTracer();


private:
    float progress() const override;
    bool rendering() const override;
    void doRenderStart() override;
    void doRenderStop() override;

    void render();

    std::vector<std::thread> threads;
    void createJobs(int w, int h);
    size_t numJobs;
    Jobs jobs;
    Jobs completedJobs;
    mutable std::mutex jobMutex, doneMutex;
    mutable bool mIsRendering;


    glm::vec3 pixelColor(float x, float y, int samples);
    glm::vec3 rad(const Ray &r, const float t0, const float t1);

    glm::vec3 computeRadiance(
        const HitRecord &recX,
        const glm::vec3 &theta,
        int bounces
        );

    glm::vec3 Phong_BRDF(
        const glm::vec3 &x,
        const glm::vec3 &Nx,
        const glm::vec3 &outDir,
        const glm::vec3 &inDir,
        const Material* surfaceMat
        ) const;

    glm::vec3 directIllumination(
        const HitRecord &recX,
        const glm::vec3 &theta
        );

    glm::vec3 indirectIllumination(
        const HitRecord &recX,
        const glm::vec3 &theta,
        int bounces
        );

    float radianceTransfer(const HitRecord &recX, const HitRecord &recY) const;

    RNG mRng;
    Camera mCamera;
    std::shared_ptr<Image> mImage;
    const SceneGraph *mSceneGraph;
    const Scene *mScene;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_PATH_TRACER_H_