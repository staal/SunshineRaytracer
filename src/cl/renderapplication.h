/*!
    The command line application using the sunshine render engine.
*/

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

    /*!
        Load @param sceneFile, construction the scene to be rendered.
    */
    void loadScene(std::string sceneFile);
    
    /*!
        Render the loaded scene.
    */
    void renderScene();
    void saveImage();
private:
    //!< The image being rendered.
    std::shared_ptr<Image> mImage;

    //!< The current loaded scene. Populate through @loadScene .
    Scene mScene;

    //!< The current scenegraph, containing the geometry and materials.
    SceneGraph mSceneGraph;
};


} // namespace sunshine
#endif // !RENDER_APPLICATION_H_