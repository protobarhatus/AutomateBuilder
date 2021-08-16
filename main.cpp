#include <QApplication>
#include<iostream>
#include "controller.h"
#include "somedataworks.h"

#include <ctime>
#include <QDebug>

#include <thread>

#include <random>
#include <time.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

        QStringList paths = QCoreApplication::libraryPaths();
        paths.append(".");
        paths.append("imageformats");
        paths.append("platforms");
        paths.append("sqldrivers");
        QCoreApplication::setLibraryPaths(paths);
        QCoreApplication::addLibraryPath("./");
    srand(time(0));
    QApplication a(argc, argv);
    Controller controller;
    controller.start();

    return a.exec();
}
