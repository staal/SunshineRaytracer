#include <QApplication>

#include "sunshinemainwindow.h"
#include "sunshineversion.h"


int main(int argv, char **args)
{
    Q_INIT_RESOURCE(shaders);
    Q_INIT_RESOURCE(images);

    const QString version = QString::fromStdString(sunshine::sunshineVersion);

    QApplication app(argv, args);
    QCoreApplication::setOrganizationName("Staal");
    QCoreApplication::setApplicationName("Sunshine Raytracer");
    QCoreApplication::setApplicationVersion(version);
    QGuiApplication::setApplicationDisplayName("Sunshine Raytracer");

    //The primary window to be shown
    sunshine::SunshineMainWindow window;
    window.setWindowIcon(QIcon(":/images/sun_icon.png"));

    //Let Qt handle the show from here!
    window.show();
    return app.exec();
}