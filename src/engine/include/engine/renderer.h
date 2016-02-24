#ifndef SUNSHINE_ENGINE_RENDERER_H_
#define SUNSHINE_ENGINE_RENDERER_H_

namespace sunshine {
namespace engine {

/*!
    \brief The base render class.
*/
class Renderer {
public:
    virtual ~Renderer() = default;

    /*! Nonblocking start of rendering */
    void renderStart();

    /*! Stop rendering if currently rendering */
    void renderStop();

    /*! Query if the renderer is currently rendering */
    bool isRendering() const;

    /*!
        Get the progress of the current rendering.
        Values are between 0.0f and 100.0f
    */
    float renderProgress() const;


private:
    virtual float progress() const = 0;
    virtual bool rendering() const = 0;
    virtual void doRenderStart() = 0;
    virtual void doRenderStop() = 0;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_RENDERER_H_