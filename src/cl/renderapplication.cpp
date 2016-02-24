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
    std::cout << "Render progress:" << std::endl; 
    auto start = std::chrono::high_resolution_clock::now();

    auto renderer = engine->getRenderer();
    renderer->renderStart();
    int stars = 80;
    float percentInterval = 100.0f/stars; //Print stars - 1
    float progress = 0.0f;
    float reportedPercent = 0.0f;
    while (renderer->isRendering()) {
        progress = renderer->renderProgress();

        //Print stars
        while (progress - reportedPercent >= percentInterval) {
            reportedPercent += percentInterval;
             std::cout << "*";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }    
    auto end = std::chrono::high_resolution_clock::now();

    //Print remaining stars
    while (100.0f - reportedPercent >= percentInterval) {
        reportedPercent += percentInterval;
        std::cout << "*";
    }
    std::cout << std::endl; //Finish star! ^^ 

    auto elapsedTimeMS = 
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    auto timeMS = elapsedTimeMS.count();
    auto timeSec = timeMS / 1000.0f;
    std::cout << "Render complete, time spent: " << timeSec << "s, "
        << timeMS << "ms." << std::endl;

    //Store image
    engine->saveImage(outFile);

    return 0;
}


} // namespace cl
} // namespace sunshine