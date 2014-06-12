#include <QApplication>

#include <iostream>

#include "ventanaprincipal.h"
#include "complejosimplicial.h"

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
    VentanaPrincipal mainWin;
    mainWin.resize(300, 300);
    mainWin.show();

    return app.exec();
}
