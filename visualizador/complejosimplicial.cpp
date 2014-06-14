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
#include "mecanismos_comunicacion.h"
#include "Utils.h"

ComplejoSimplicial::ComplejoSimplicial(QWidget *parent)
    : QGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    setTipoComunicacion(STR_CONFIABLE_COLOREADA);

    anguloGiroX = 0;
    anguloGiroY = 0;

    QSize size = QSize(500, 500);
    setMinimumSize(size);

    grafica = new Grafica;
    graficaOriginal = new Grafica;
}

ComplejoSimplicial::~ComplejoSimplicial()
{
    delete grafica;
}

void ComplejoSimplicial::initializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void ComplejoSimplicial::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    GLfloat x = GLfloat(width) / height;
//    gluPerspective(65, x, 1, 20.0);
//    glMatrixMode(GL_MODELVIEW);
}

void ComplejoSimplicial::paintGL()
{
    GLfloat light_pos[] = {10, 20, 0, 0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    gluLookAt(30, -30, 0,
//              0.0, 0.0, 0,
//              0.0, 0.0, 1);

    dibujar();

}

void ComplejoSimplicial::dibujar()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    qDebug() << anguloGiroX;
    qDebug() << anguloGiroY;

    glRotated(anguloGiroX,1,0,0);
    glRotated(anguloGiroY,0,1,0);

    glColor3f(1, 0, 0);

    // draw graph conntents

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
    glPopMatrix();

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

        // guardar una copia de la grafica original
        graficaOriginal->addVertices(verticesLeidos);
        graficaOriginal->addAristas(aristasLeidas);
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


void ComplejoSimplicial::incrementarAnguloGiroY(int delta)
{
    if (anguloGiroY > 360)
        anguloGiroY = 0;

    anguloGiroY += delta;
}

void ComplejoSimplicial::incrementarAnguloGiroX(int delta)
{
    if (anguloGiroX > 360)
        anguloGiroX = 0;

    anguloGiroX += delta;
}

void ComplejoSimplicial::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "keyPressEvent";

    switch (event->key()) {
    case Qt::Key_A:
        incrementarAnguloGiroY(10);
        break;

    case Qt::Key_D:
        incrementarAnguloGiroY(-10);
        break;

    case Qt::Key_W:
        incrementarAnguloGiroX(10);
        break;

    case Qt::Key_S:
        incrementarAnguloGiroX(-10);
        break;

    default:
        QWidget::keyPressEvent(event);
        break;
    }

    updateGL();

}

void ComplejoSimplicial::comunicarConfiableColoreada()
{
    std::vector<Edge> aristasGeneradas;
    std::vector<Vertex3d> verticesGenerados;

    std::vector<Edge> aristas = grafica->getAristas();
    std::vector<Vertex3d> vertices = grafica->getVertices();

    for (unsigned i = 0; i < aristas.size(); i++) {
        int index_vertex_1;
        int index_vertex_2;

        index_vertex_1 = aristas[i].getVertex1();
        index_vertex_2 = aristas[i].getVertex2();

        std::vector<Vertex3d> result = comunicarNoConfiableColoreado(vertices[index_vertex_1],
                                                                     vertices[index_vertex_2]);
        std::copy(result.begin(), result.end(),
                  std::back_inserter(verticesGenerados));

        // generar las nuevas aristas
        // en una comunicacion confiable coloreada entre dos
        // procesos se generara solo una arista nueva y
        // cuatro vertices siempre
        std::vector<Vertex3d>::iterator iter = verticesGenerados.end();

        iter--;     // apuntar al ultimo elemento
        iter--;     // apuntar al penultimo elemento

        int indice_actual = iter - verticesGenerados.begin();
        Edge nueva_arista = Edge(indice_actual - 1, indice_actual);
        aristasGeneradas.push_back(nueva_arista);
    }

    grafica->limpiar();
    grafica->addVertices(verticesGenerados);
    grafica->addAristas(aristasGeneradas);

    qDebug() << "Vertices";
    qDebug() << print(grafica->getVertices()).c_str();
    qDebug() << "Aristas";
    qDebug() << print(grafica->getAristas()).c_str();


}


void ComplejoSimplicial::comunicarNoConfiableColoreada()
{
    std::vector<Edge> aristasGeneradas;
    std::vector<Vertex3d> verticesGenerados;

    std::vector<Edge> iter;
    std::vector<Edge> aristas = grafica->getAristas();
    std::vector<Vertex3d> vertices = grafica->getVertices();

    for (unsigned i = 0; i < aristas.size(); i++) {
        int index_vertex_1;
        int index_vertex_2;

        index_vertex_1 = aristas[i].getVertex1();
        index_vertex_2 = aristas[i].getVertex2();

        std::vector<Vertex3d> result = comunicarNoConfiableColoreado(vertices[index_vertex_1],
                                                                     vertices[index_vertex_2]);
        std::copy(result.begin(), result.end(),
                  std::back_inserter(verticesGenerados));

        // generar las nuevas aristas
        // en una comunicacion no segura coloreada entre dos
        // procesos se generaran tres aristas nuevas y
        // cuatro vertices siempre
        int NUM_VERTICES_GENERADO = result.size();
        int OFFSET = NUM_VERTICES_GENERADO * i;

        Edge arista_1 = Edge(0 + OFFSET, 1 + OFFSET);
        Edge arista_2 = Edge(1 + OFFSET, 2 + OFFSET);
        Edge arista_3 = Edge(2 + OFFSET, 3 + OFFSET);

        aristasGeneradas.push_back(arista_1);
        aristasGeneradas.push_back(arista_2);
        aristasGeneradas.push_back(arista_3);
    }

    grafica->limpiar();
    grafica->addVertices(verticesGenerados);
    grafica->addAristas(aristasGeneradas);
}

void ComplejoSimplicial::comunicarProcesos()
{
    qDebug() << tipoComunicacion.c_str();

    if (tipoComunicacion == STR_CONFIABLE_COLOREADA) {
        comunicarConfiableColoreada();
    }

    if (tipoComunicacion == STR_NO_CONFIABLE_COLOREADA) {
        comunicarNoConfiableColoreada();
    }

    updateGL();
}

void ComplejoSimplicial::setTipoComunicacion(const std::string tipoComunicacion)
{
    this->tipoComunicacion = tipoComunicacion;
}
