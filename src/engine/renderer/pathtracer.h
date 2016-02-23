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
        SceneGraph* sceneGraph, Scene* scene);
    ~PathTracer();


private:
    float renderProgress() const override;
    bool rendering() const override;
    void renderStart() override;
    void renderStop() override;

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


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_PATH_TRACER_H_