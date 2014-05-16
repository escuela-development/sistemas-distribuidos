#include <QApplication>
#include <iostream>

#include "mainwindow.h"
#include "simplicialcomplex.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!QGLFormat::hasOpenGL()) {
        std::cerr << "This system has no OpenGL support" << std::endl;
        return 1;
    }

//    SimplicialComplex graph;
//    graph.setWindowTitle(QObject::tr("SimplicialComplex"));
//    graph.resize(300, 300);
//    graph.show();
    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
