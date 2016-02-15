#ifndef SUNSHINE_MAIN_SCENE_WIDGET_H_
#define SUNSHINE_MAIN_SCENE_WIDGET_H_

#include <QOpenGLWidget>

namespace sunshine {

class MainSceneWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    MainSceneWidget(QWidget *parent = nullptr);
    ~MainSceneWidget();

};

} // namespace sunshine
#endif // !SUNSHINE_MAIN_SCENE_WIDGET_H_