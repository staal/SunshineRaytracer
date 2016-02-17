
#include "sunshineengine.h"
#include "engineversion.h"

#include "geometry/objfile.h"
#include "image/tgafile.h"
#include "image.h"
#include "pathtracer.h"
#include "scene.h"
#include "scenegraph.h"

namespace sunshine {
namespace engine{


// *****************************************************************************
SunshineEngine::SunshineEngine() 
    : mScene(std::make_unique<Scene>()), 
    mImage(std::make_unique<Image>(800,600,false)),
    mSceneGraph(std::make_unique<SceneGraph>())
{
}



// *****************************************************************************
const std::string SunshineEngine::getVersion() const
{
    return engineVersion;
}


// *****************************************************************************
void SunshineEngine::loadScene(std::string sceneName)
{
    mScene->loadScene(sceneName);

    mImage = std::make_unique<Image>(mScene->width, mScene->height, false);

    //Load scene
    //Todo load own geometry, not obj format
    ObjFile objFile(mScene->objFile);
    objFile.load();

    auto surfaces = objFile.getSurfaces();
    auto mats = objFile.getMaterials();

    mSceneGraph->setEpsilon(mScene->epsilon);
    mSceneGraph->addMesh(std::move(surfaces), std::move(mats));
}


// *****************************************************************************
void SunshineEngine::renderScene()
{
    //PathTracer renderer(mImage, &mSceneGraph, &mScene);
    //renderer.render();
}


// *****************************************************************************
void SunshineEngine::saveImage(std::string outputFile)
{
    TgaFile tga;
    tga.save(mScene->outFile.c_str(), *mImage);
}

} // namespace engine
} // namespace sunshine