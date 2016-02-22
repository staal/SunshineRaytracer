#include <QtWidgets>

#include "sunshinemainwindow.h"
#include "sunshineversion.h"

namespace sunshine {


// *****************************************************************************
SunshineMainWindow::SunshineMainWindow()
    : sceneWidget(new SceneWidget(this))
{
    setCentralWidget(sceneWidget);

    createActions();
    createStatusBar();

    readSettings();

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
}


// *****************************************************************************
void SunshineMainWindow::closeEvent(QCloseEvent *event)
{
    if (promtSaveIfModified()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


// *****************************************************************************
void SunshineMainWindow::newScene()
{
    if (promtSaveIfModified()) {
        engine.newScene();
        setCurrentFile(QString());
    }
}


// *****************************************************************************
void SunshineMainWindow::open()
{
    if (promtSaveIfModified()) {
        QString filename = QFileDialog::getOpenFileName(this);
        if (!filename.isEmpty())
            loadScene(filename);
    }
}


// *****************************************************************************
bool SunshineMainWindow::save()
{
    if (currentFile.isEmpty()) {
        return saveAs();
    } else {
        return saveScene(currentFile);
    }
}


// *****************************************************************************
bool SunshineMainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveScene(dialog.selectedFiles().first());
}


// *****************************************************************************
void SunshineMainWindow::about()
{
    const QString appVersion = QString::fromStdString(sunshine::sunshineVersion);
    const QString engineVersion
        = QString::fromStdString(engine.getVersion());

    QMessageBox::about(this, tr("About Sunshine Raytracer"),
        tr("The Sunshine Raytracer, version %1.\n"
        "Running the Sunshine Raytracer Engine, version %1")
        .arg(appVersion)
        .arg(engineVersion));
}


// *****************************************************************************
void SunshineMainWindow::sceneModified()
{
    setWindowModified(true);
}


// *****************************************************************************
void SunshineMainWindow::createActions()
{
    //File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));


    QAction *newAct = fileMenu->addAction(tr("&New"), this,
        &SunshineMainWindow::newScene);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new scene"));


    QAction *openAct = fileMenu->addAction(tr("&Open"), this,
        &SunshineMainWindow::open);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing scene"));


    QAction *saveAct = fileMenu->addAction(tr("&Save"), this, 
        &SunshineMainWindow::save);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the scene"));    


    QAction *saveAsAct = fileMenu->addAction(tr("Save &As..."), this,
        &SunshineMainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the scene with a new name"));



    fileMenu->addSeparator();


    fileMenu->addAction(tr("&Import file"));


    fileMenu->addSeparator();



    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));



    //Render menu
    QMenu *renderMenu = menuBar()->addMenu(tr("&Render"));
    QAction *renderAct = renderMenu->addAction(tr("&Render Scene"), this,
        &SunshineMainWindow::render);
    renderAct->setShortcut(QKeySequence(Qt::Key_F5));
    renderAct->setStatusTip(tr("Render the current scene"));


    //Help menu
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct 
        = helpMenu->addAction(tr("&About"), this, &SunshineMainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));


    QAction *aboutQtAct 
        = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}


// *****************************************************************************
void SunshineMainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


// *****************************************************************************
void SunshineMainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), 
        QCoreApplication::applicationName());
    const QByteArray geometry 
        = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        //Default position is middle of screen, 1/3 screen width and 1/2 height.
        const QRect availableGeometry 
            = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
            (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}


// *****************************************************************************
void SunshineMainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), 
        QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}


// *****************************************************************************
bool SunshineMainWindow::promtSaveIfModified()
{
    if (!isWindowModified())
        return true;

    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Application"),
        tr("The document has been modified.\n"
        "Do you want to save your changes?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
        case QMessageBox::Save:
            return save();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
}


// *****************************************************************************
void SunshineMainWindow::loadScene(const QString &filename)
{
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    engine.loadScene(filename.toStdString());

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(filename);
    statusBar()->showMessage(tr("File loaded"), 2000);
}


// *****************************************************************************
bool SunshineMainWindow::saveScene(const QString &filename)
{
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    engine.saveScene(filename.toStdString());

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(filename);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}


// *****************************************************************************
void SunshineMainWindow::setCurrentFile(const QString &filename)
{
    currentFile = filename;
    setWindowModified(false);

    QString shownName = currentFile;
    if (currentFile.isEmpty())
        shownName = "untitled.scene";
    setWindowFilePath(shownName);
}


// *****************************************************************************
void SunshineMainWindow::render()
{
    engine.renderScene();

    engine.saveImage();

}


} // namespace sunshine