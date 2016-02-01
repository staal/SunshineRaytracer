
#include <chrono>
#include <iostream>

#include "engine/image/tgafile.h"
#include "engine/geometry/obj/objfile.h"
#include "engine/pathtracer.h"

#include "renderapplication.h"
#include "commandlinehandler.h"


namespace sunshine {
namespace cl {

using namespace sunshine::engine;

// *****************************************************************************
RenderApplication::RenderApplication(int argc, char * argv[])
    : mCommandlineHandler(argc, argv)
{}

// *****************************************************************************
RenderApplication::~RenderApplication()
{}


// *****************************************************************************
int RenderApplication::run()
{
    int errorCode = 0;
    if (!mCommandlineHandler.validate(errorCode)) {
        return errorCode;
    }

    //Print the version number and exit 0.
    if (mCommandlineHandler.printVersion()) {
        std::cout << "Version: " << PathTracer::getVersion() << std::endl;
        return 0;
    }

    //Get commandline arguments
    std::string configFileName = mCommandlineHandler.getScene();
    std::cout << "Input: " << configFileName << std::endl;

    std::string outFile = mCommandlineHandler.getOutputFile();
    if (!outFile.empty()) {
        std::cout << "Output: " << outFile << std::endl;
    } else {
        std::cout << "Output: " << "unspecified, using out.tga" << std::endl;
    }





    //Load Scene
    std::cout << "Loading scene: " << configFileName << std::endl;
    loadScene(configFileName);

    //Ray tracing part
    std::cout << "Rendering using SunshineRaytracer engine" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    renderScene();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    auto elapsedTimeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Render complete, time spent: " << elapsedTime.count() << "s" << std::endl;
    std::cout << "Render complete, time spent: " << elapsedTimeMS.count() << "ms" << std::endl;

    //Store image
    saveImage();

    return 0;
}


// *****************************************************************************
void RenderApplication::loadScene(std::string sceneFile)
{
    mScene.loadScene(sceneFile);

    mImage = std::make_shared<Image>(mScene.width, mScene.height, false);

    //Load scene
    ObjFile objFile;
    objFile.load(mScene.objFile);

    auto surfaces = objFile.getSurfaces();
    auto mats = objFile.getMaterials();

    mSceneGraph.setEpsilon(mScene.epsilon);
    mSceneGraph.addMesh(std::move(surfaces), std::move(mats));
}


// *****************************************************************************
void RenderApplication::renderScene()
{
    PathTracer renderer(mImage, &mSceneGraph, &mScene);
    std::cout << "Using Sunshine Ray Tracer(SRT) engine version " << renderer.getVersion() << std::endl;
    renderer.render();
}


// *****************************************************************************
void RenderApplication::saveImage()
{
    TgaFile tga;
    tga.save(mScene.outFile.c_str(), *mImage);
}


} // namespace cl
} // namespace sunshine