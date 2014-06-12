#include <QtGui>
#include <QtOpenGL>
#include <QDebug>
#include <QTimer>
#include "GL/glu.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

#include <cstdlib>
#include <cstring>

#include "complejosimplicial.h"
#include "vertex3d.h"
#include "edge.h"

ComplejoSimplicial::ComplejoSimplicial(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    QSize size = QSize(500, 500);
    setMinimumSize(size);

    grafica = new Grafica;
}

ComplejoSimplicial::~ComplejoSimplicial()
{
    delete grafica;
}

void ComplejoSimplicial::initializeGL()
{
    qglClearColor(Qt::gray);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void ComplejoSimplicial::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ComplejoSimplicial::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    dibujar();
}

void ComplejoSimplicial::dibujar()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 0, 0);

    // draw graph conntents
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    {
        std::vector<Vertex3d> vertices = grafica->getVertices();
        std::vector<Edge> aristas = grafica->getAristas();

        for (unsigned i = 0; i < aristas.size(); i++) {
            Edge a = aristas[i];
            Vertex3d v1 = vertices[a.getVertex1()];
            Vertex3d v2 = vertices[a.getVertex2()];

            glVertex3d(v1.getX(), v1.getY(), v1.getZ());
            glVertex3d(v2.getX(), v2.getY(), v2.getZ());

        }
    }

    glEnd();

}

bool ComplejoSimplicial::leerArchivo(const QString &fileName)
{
    std::ifstream file(fileName.toStdString().c_str(), std::ios::in);
    if (!file) {
        std::cerr << "No fue posible leer el archivo " << fileName.toStdString() << std::endl;
        return false;
    }


    QApplication::setOverrideCursor(Qt::WaitCursor);

    int numero_vertices;
    int numero_aristas;
    std::string line;

    while(std::getline(file, line)) {

        std::istringstream iss_num_vertices(line);
        iss_num_vertices >> numero_vertices;

        std::vector<Vertex3d> verticesLeidos;
        for (int i = 0; i < numero_vertices; i++) {
            std::getline(file, line);
            Vertex3d v = leerVertice(line);
            verticesLeidos.push_back(v);
        }

        std::getline(file, line);
        std::istringstream iss_num_edges(line);
        iss_num_edges >> numero_aristas;

        std::vector<Edge> aristasLeidas;
        for (int i = 0; i < numero_aristas; i++) {
            std::getline(file, line);
            Edge a = leerArista(line);
            aristasLeidas.push_back(a);
        }

        grafica->addVertices(verticesLeidos);
        grafica->addAristas(aristasLeidas);
    }

    QApplication::restoreOverrideCursor();

    // update opengl
    updateGL();    

    return true;
}

Vertex3d ComplejoSimplicial::leerVertice(std::string cadena)
{
    double valores[4];
    char *ptrToken;

    char *ptrCadena = new char[cadena.size()+1];
    strcpy(ptrCadena, cadena.c_str());

    int contador = 0;
    ptrToken = strtok(ptrCadena, " (),");
    while (ptrToken != NULL) {
        valores[contador++] = atof(ptrToken);
        ptrToken = strtok(NULL, " (),");
    }

    Vertex3d vertex = Vertex3d(valores[1],
            valores[2], valores[3]);

    return vertex;
}

Edge ComplejoSimplicial::leerArista(std::string cadena)
{
    char *ptrCadena = new char[cadena.size() + 1];
    strcpy(ptrCadena, cadena.c_str());

    int contador = 0;
    double valores[2];

    char *ptrToken = strtok(ptrCadena, ",");
    while (ptrToken != NULL) {
        valores[contador++] = atof(ptrToken);
        ptrToken = strtok(NULL, ",");
    }

    Edge edge = Edge(valores[0], valores[1]);
    return edge;
}
