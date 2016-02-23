#ifndef SUNSHINE_ENGINE_SUNSHINE_ENGINE_H_
#define SUNSHINE_ENGINE_SUNSHINE_ENGINE_H_

#include <string>
#include <memory>

#include "engine/image.h"
#include "engine/renderer.h"

namespace sunshine {
namespace engine{

class Scene;
class SceneGraph;
class Image;

/*!
    \brief The main entrypoint into the Sunshine Render Library
*/
class SunshineEngine {
public:
    SunshineEngine();
    ~SunshineEngine();

    /*!
        Load the default scene
    */
    void newScene();

    /*!
        Get the build version of the engine
    */
    const std::string getVersion() const;

    /*!
        @param sceneFile the scene to load.
    */
    void loadScene(std::string sceneFile);

    /*!
        @param sceneFile the scene to save.        
    */
    void saveScene(std::string sceneFile);

    /*!
        Start rendering the current scene.
    */
    void renderScene();

    /*!
        Current progress on the rendering.

        \return A value between and inclusive of 0.0f and 100.0f
    */
    float renderProgress();

    /*!
        Returns the status of rendering.

        \return True if rendering, false for all other situations.
    */
    bool isRendering();

    /*!
        Save the rendered image

        @param outputFile If passed, will be the output path of the image.
    */
    void saveImage(std::string outputFile = std::string());


    /*!
        Get the current image being rendered / already rendered
    */
    std::shared_ptr<Image> getImage();

private:
    //! The image being rendered.
    std::shared_ptr<Image> mImage;

    //! The current loaded scene. Populate through @loadScene .
    std::unique_ptr<Scene> mScene;

    //! The current scenegraph, containing the geometry and materials.
    std::unique_ptr<SceneGraph> mSceneGraph;

    std::unique_ptr<Renderer> mRenderer;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_PATH_TRACER_H_