#include <QApplication>
#include <QTextEdit>

#include "mainscenewidget.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    
    sunshine::MainSceneWidget m;

    
    return app.exec();
}