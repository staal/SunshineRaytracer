#ifndef SUNSHINE_ENGINE_SUNSHINE_ENGINE_H_
#define SUNSHINE_ENGINE_SUNSHINE_ENGINE_H_

#include <string>
#include <memory>

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

    /*!
        Get the build version of the engine
    */
    const std::string getVersion() const;

    /*!
        @param sceneFile the scene to be rendered.
    */
    void loadScene(std::string sceneFile);

    /*!
        Render the loaded scene.
    */
    void renderScene();

    /*!
        Save the scene
    */
    void saveImage(std::string outputFile = std::string());


private:
    //! The image being rendered.
    std::unique_ptr<Image> mImage;

    //! The current loaded scene. Populate through @loadScene .
    std::unique_ptr<Scene> mScene;

    //! The current scenegraph, containing the geometry and materials.
    std::unique_ptr<SceneGraph> mSceneGraph;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_PATH_TRACER_H_