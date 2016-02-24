#ifndef SUNSHINE_ENGINE_PATH_TRACER_RENDERER_H_
#define SUNSHINE_ENGINE_PATH_TRACER_RENDERER_H_

#include <memory>

#include <thread>
#include <queue>
#include <mutex>

#include "engine/renderer.h"
#include "engine/image.h"

#include "pathtracer.h"
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

class PathTracerRenderer : public Renderer
{
public:
    PathTracerRenderer(std::shared_ptr<Image> image,
        const SceneGraph* sceneGraph, const Scene* scene);
    ~PathTracerRenderer();


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


    PathTracer pathTracer;
    std::shared_ptr<Image> mImage;
    const unsigned int renderSeed;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_PATH_TRACER_RENDERER_H_