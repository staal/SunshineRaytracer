#ifndef SUNSHINE_SCENE_WIDGET_H_
#define SUNSHINE_SCENE_WIDGET_H_

#include <QOpenGLWidget>
#include <QOpenglFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include <QElapsedTimer>

namespace sunshine {

class SceneWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    SceneWidget(QWidget *parent = nullptr);
    ~SceneWidget();

    //Delete copy and move operations
    SceneWidget(const SceneWidget& w) = delete;
    SceneWidget(SceneWidget&& w) = delete;
    SceneWidget& operator=(const SceneWidget& w) = delete;
    SceneWidget& operator=(SceneWidget&& w) = delete;

protected:
    void initializeGL() override;

    void paintGL() override;

    void resizeGL(int w, int h) override;

private:
    QOpenGLVertexArrayObject mVao;
    QOpenGLBuffer mVbo;
    QOpenGLShaderProgram *mProgram;

    float rot;
    QVector3D mLightPosition;


    QElapsedTimer *mTimer;
    quint64 last;
};


} // namespace sunshine
#endif // !SUNSHINE_SCENE_WIDGET_H_