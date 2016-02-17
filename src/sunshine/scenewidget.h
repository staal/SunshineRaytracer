#ifndef SUNSHINE_SCENE_WIDGET_H_
#define SUNSHINE_SCENE_WIDGET_H_

#include <QOpenGLWidget>

namespace sunshine {

class SceneWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    SceneWidget(QWidget *parent = nullptr);

};


} // namespace sunshine
#endif // !SUNSHINE_SCENE_WIDGET_H_