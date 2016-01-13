#include <math.h>
#include <iostream>

#include "io/tgafile.h"
#include "io/objfile.h"
#include "renderapplication.h"
#include "scenegraph.h"
#include "pathtracer.h"

namespace staal {

using namespace glm;

RenderApplication::RenderApplication()
    : mScene()
{}

RenderApplication::~RenderApplication()
{}

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

void RenderApplication::renderScene()
{
    PathTracer renderer(mImage, &mSceneGraph, &mScene);

    renderer.render();
}

void RenderApplication::saveImage()
{
    TgaFile tga;
    tga.save(mScene.outFile.c_str(), *mImage);
}


} // namespace staal