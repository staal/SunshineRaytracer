#include <math.h>
#include <iostream>

#include "pathtracerrenderer.h"

namespace sunshine {
namespace engine{

#define DEBUG 1
#define NUM_SHADOW_RAYS 1
#define NUM_INDIRE_RAYS 1

using namespace glm;


// *****************************************************************************
PathTracerRenderer::PathTracerRenderer(std::shared_ptr<Image> image, 
    const SceneGraph* sceneGraph,
    const Scene* scene) 
    : mImage{ image }, pathTracer{ sceneGraph,scene }, mIsRendering(false), 
    renderSeed(scene->seed)
{
    
}

PathTracerRenderer::~PathTracerRenderer()
{
    for (auto &t : threads) {
        t.join();
    }
}


// *****************************************************************************
float PathTracerRenderer::progress() const
{
    std::lock_guard<std::mutex> guard(doneMutex);

    float progress = static_cast<float>(completedJobs.size()) /
        static_cast<float>(numJobs) * 100.0f;
    return progress;
}


// *****************************************************************************
bool PathTracerRenderer::rendering() const
{
    return mIsRendering;
}


// *****************************************************************************
void PathTracerRenderer::doRenderStart()
{
    const int numThreads = 4;
    createJobs(mImage->getWidth(), mImage->getHeight());
    mIsRendering = true;
    for (int i = 0; i < numThreads; i++) {
        threads.push_back(std::thread(&PathTracerRenderer::render, this));
    }
}


// *****************************************************************************
void PathTracerRenderer::doRenderStop()
{
}


// *****************************************************************************
void PathTracerRenderer::createJobs(int w, int h)
{
    completedJobs = Jobs();
    jobs = Jobs();
    const int size = 10;
    for (int x = 0; x < w; x += size) {
        for (int y = 0; y < h; y += size) {
            Job j;
            j.start_x = x;
            j.start_y = y;
            if (x + size >= w) {
                j.end_x = w;
            } else {
                j.end_x = j.start_x + size;
            }
            if (y + size >= h) {
                j.end_y = w;
            } else {
                j.end_y = j.start_y + size;
            }
            jobs.push(j);
        }
    }
    numJobs = jobs.size();
}


// *****************************************************************************
/*
Compute the entire image,
samples : Number of samples per pixel
*/
void PathTracerRenderer::render()
{
    RNG rng(renderSeed);
    while(true) //quit out?
    {
        //Fetch next job
        jobMutex.lock();
        if (jobs.empty()) {
            jobMutex.unlock();
            return; //Exit rendering
        }
        Job job = jobs.front();
        jobs.pop();
        jobMutex.unlock();

        rng.seed(renderSeed + renderSeed * job.start_x * job.start_y);
        for (int y = job.start_y; y < job.end_y; y++) {
            for (int x = job.start_x; x < job.end_x; x++) {
                //For each pixel
                vec3 color = pathTracer.pixelColor((float)x, (float)y, rng);

                //Clamp the color
                color = glm::clamp(color, 0.0f, 1.0f);
                mImage->setPixel(x, y, color.r, color.g, color.b);
            }
        }
        //Push back completed job
        {
            std::lock_guard<std::mutex> guard(doneMutex);
            completedJobs.push(job);
            if (completedJobs.size() == numJobs) {
                mIsRendering = false;
            }
        }
    }
}



} // namespace engine
} // namespace sunshine