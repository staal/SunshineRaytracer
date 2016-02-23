#include <chrono>
#include <iostream>
#include <thread>

#include "engine/sunshineengine.h"

#include "commandlinehandler.h"
#include "renderapplication.h"


namespace sunshine {
namespace cl {

using namespace sunshine::engine;

// *****************************************************************************
RenderApplication::RenderApplication(CommandlineHandler  handler)
    : mCommandlineHandler(std::move(handler))
{}


// *****************************************************************************
int RenderApplication::run()
{
    using sunshine::engine::SunshineEngine;
    std::unique_ptr<SunshineEngine> engine = std::make_unique<SunshineEngine>();

    int errorCode = 0;
    if (!mCommandlineHandler.validate(errorCode)) {
        return errorCode;
    }

    //Print the version number and exit 0.
    if (mCommandlineHandler.printVersion()) {
        std::cout << "Version: " << engine->getVersion() << std::endl;
        return 0;
    }

    std::cout << "Using Sunshine Ray Tracer(SRT) engine version " <<
        engine->getVersion() << std::endl;

    //Get commandline arguments
    std::string sceneFilename = mCommandlineHandler.getScene();
    if (sceneFilename.empty()) {
        std::cout << "Please supply a .scene file" << std::endl;
        return -1;
    }
    std::cout << "Input: " << sceneFilename << std::endl;

    std::string outFile = mCommandlineHandler.getOutputFile();
    if (!outFile.empty()) {
        std::cout << "Output: " << outFile << std::endl;
    }


    //Load Scene
    std::cout << "Loading scene: " << sceneFilename << std::endl;
    engine->loadScene(sceneFilename);

    //Ray tracing part
    std::cout << "Rendering using SunshineRaytracer engine" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    engine->renderScene();
    int nextReport = 0.0f;
    float progress = 0.0f;
    while (engine->isRendering()) {
        progress = engine->renderProgress();
        if (progress > nextReport) {
            nextReport += 10.0f;
            std::cout << "Render progress: " << engine->renderProgress() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto elapsedTime = 
        std::chrono::duration_cast<std::chrono::seconds>(end - start);

    auto elapsedTimeMS = 
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Render complete, time spent: " << 
        elapsedTime.count() << "s" << std::endl;

    std::cout << "Render complete, time spent: " << 
        elapsedTimeMS.count() << "ms" << std::endl;

    //Store image
    engine->saveImage(outFile);

    return 0;
}


} // namespace cl
} // namespace sunshine