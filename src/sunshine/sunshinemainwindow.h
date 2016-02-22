#ifndef SUNSHINE_MAIN_WINDOW_H_
#define SUNSHINE_MAIN_WINDOW_H_

#include <QMainWindow>
#include "scenewidget.h"
#include "engine/sunshineengine.h"

namespace sunshine {

class RenderDialog;

class SunshineMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SunshineMainWindow();

    void loadScene(const QString &filename);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newScene();
    void open();
    bool save();
    bool saveAs();
    void about();
    void sceneModified();
    void render();

    /*! Display the render settings dialog. */
    void showRenderSettings();

private:
    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();

    /*! 
        Returns true if save was succesful or changes are 
        allowed to be discarded
    */
    bool promtSaveIfModified();
    bool saveScene(const QString &filename);
    void setCurrentFile(const QString &filename);

    sunshine::engine::SunshineEngine engine;
    SceneWidget *sceneWidget;
    QString currentFile;

    RenderDialog *renderDialog;
};


} // namespace sunshine
#endif // !SUNSHINE_MAIN_WINDOW_H_