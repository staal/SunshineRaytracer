#ifndef SUNSHINE_CL_RENDER_APPLICATION_H_
#define SUNSHINE_CL_RENDER_APPLICATION_H_

#include "engine/image.h"
#include "engine/scene.h"
#include "engine/scenegraph.h"

#include "commandlinehandler.h"

namespace sunshine {
namespace cl {

//! The command line application using the sunshine render engine.
class RenderApplication {
public:
    RenderApplication(int argc, char *argv[]);
    ~RenderApplication();


    /*!
        Processes the commandline and handle the response, including rendering
    */
    int run();


protected:
    /*!
        Load @param sceneFile, construction the scene to be rendered.
    */
    void loadScene(std::string sceneFile);

    /*!
        Render the loaded scene.
    */
    void renderScene();

    /*!
        Save the scene
    */
    void saveImage();


private:
    //!< Processes command line, including malformed formats
    CommandlineHandler mCommandlineHandler;

    //!< The image being rendered.
    std::shared_ptr<sunshine::engine::Image> mImage;

    //!< The current loaded scene. Populate through @loadScene .
    sunshine::engine::Scene mScene;

    //!< The current scenegraph, containing the geometry and materials.
    sunshine::engine::SceneGraph mSceneGraph;
};


} // namespace cl
} // namespace sunshine
#endif // !SUNSHINE_CL_RENDER_APPLICATION_H_