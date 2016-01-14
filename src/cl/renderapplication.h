#ifndef RENDER_APPLICATION_H_
#define RENDER_APPLICATION_H_

#include "engine/image.h"
#include "engine/scene.h"
#include "engine/scenegraph.h"

namespace sunshine {

class RenderApplication {
public:
    RenderApplication();
    ~RenderApplication();

    void loadScene(std::string sceneFile);
    void renderScene();
    void saveImage();
private:
    //current image
    std::shared_ptr<Image> mImage;

    Scene mScene;
    SceneGraph mSceneGraph;
};


} // namespace sunshine
#endif // !RENDER_APPLICATION_H_