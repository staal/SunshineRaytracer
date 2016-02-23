
#include "engine/sunshineengine.h"
#include "engineversion.h"

#include "geometry/objfile.h"
#include "image/tgafile.h"
#include "renderer/pathtracer.h"
#include "scene.h"
#include "scenegraph.h"

namespace sunshine {
namespace engine {


// *****************************************************************************
SunshineEngine::SunshineEngine()
    : mScene(std::make_unique<Scene>()),
    mImage(std::make_shared<Image>(800, 600, false)),
    mSceneGraph(std::make_unique<SceneGraph>()),
    mRenderer(nullptr)
{
}


// *****************************************************************************
SunshineEngine::~SunshineEngine() = default;


// *****************************************************************************
const std::string SunshineEngine::getVersion() const
{
    return engineVersion;
}


// *****************************************************************************
void SunshineEngine::newScene()
{
    mImage = std::make_shared<Image>(800,600, false);
    mScene = std::make_unique<Scene>();

    mSceneGraph->clear();
}


// *****************************************************************************
void SunshineEngine::loadScene(std::string sceneName)
{
    mScene = std::make_unique<Scene>();
    mSceneGraph->clear();

    mScene->loadScene(sceneName);

    mImage = std::make_shared<Image>(mScene->width, mScene->height, false);

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
void SunshineEngine::saveScene(std::string sceneName)
{
    //TODO Implement
}


// *****************************************************************************
void SunshineEngine::renderScene()
{
    mRenderer = std::make_unique<PathTracer>(mImage, mSceneGraph.get(), mScene.get());
    mRenderer->start();
}


// *****************************************************************************
float SunshineEngine::renderProgress()
{
    return mRenderer->progress();
}


// *****************************************************************************
bool SunshineEngine::isRendering()
{
    return mRenderer->isRendering();
}


// *****************************************************************************
void SunshineEngine::saveImage(std::string outputFile)
{
    //Argument takes precedence over scene file
    if (outputFile.empty()) {
        outputFile = mScene->outFile;
    }

    TgaFile tga;
    tga.save(outputFile, *mImage);
}


// *****************************************************************************
std::shared_ptr<Image> SunshineEngine::getImage()
{
    return mImage;
}

} // namespace engine
} // namespace sunshine