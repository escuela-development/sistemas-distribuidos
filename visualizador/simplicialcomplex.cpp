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

#include "simplicialcomplex.h"
#include "vertex2d.h"


SimplicialComplex::SimplicialComplex(QWidget *parent)
    : QGLWidget(parent),
      TICK_AMOUNT(5),
      CONFIABLE(0),
      NO_CONFIABLE(1)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    toggleColor = false;
    communicationType = 0;

    rotationX = -21.0;
    rotationY = -57.0;
    rotationZ = 0.0;
    faceColors[0] = Qt::red;
    faceColors[1] = Qt::green;
    faceColors[2] = Qt::blue;
    faceColors[3] = Qt::yellow;

    QSize size = QSize(500, 500);
    setMinimumSize(size);

    elapsedTime = 0;
    graph = new Graph();        
}

SimplicialComplex::~SimplicialComplex()
{
    delete graph;
}

void SimplicialComplex::initializeGL()
{
    qglClearColor(Qt::gray);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void SimplicialComplex::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SimplicialComplex::paintGL()
{
//    qDebug() << "paintGL()";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

//void SimplicialComplex::mousePressEvent(QMouseEvent *event)
//{
//    lastPos = event->pos();
//}

//void SimplicialComplex::mouseMoveEvent(QMouseEvent *event)
//{
//    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
//    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

//    if (event->buttons() & Qt::LeftButton) {
//        rotationX += 180 * dy;
//        rotationY += 180 * dx;
//        updateGL();
//    } else if (event->buttons() & Qt::RightButton) {
//        rotationX += 180 * dy;
//        rotationZ += 180 * dx;
//        updateGL();
//    }
//    lastPos = event->pos();
//}

//void SimplicialComplex::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    int face = faceAtPosition(event->pos());
//    if (face != -1) {
//        QColor color = QColorDialog::getColor(faceColors[face], this);
//        if (color.isValid()) {
//            faceColors[face] = color;
//            updateGL();
//        }
//    }
//}

void SimplicialComplex::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    glRotatef(elapsedTime, 0, 0, 1);

    // draw graph conntents
    glLineWidth(2.5f);   
    glBegin(GL_LINES);
    {
        std::vector<Vertex2d> vertices = graph->getVertices();

        for (unsigned i = 1; i < vertices.size(); i += 2) {
            alternateColor(i);

            glVertex2d(vertices[i-1].getX(),
                       vertices[i-1].getY());
            glVertex2d(vertices[i].getX(),
                       vertices[i].getY());
        }
    }

    glEnd();

}

void SimplicialComplex::alternateColor(int index)
{
    toggleColor = !toggleColor;

    if (toggleColor)
        glColor3f(1.0f, 1.0f, 1.0f);
    else
        glColor3f(0.0f, 0.0f, 0.0f);
}

void SimplicialComplex::communicateProcesses()
{
    std::vector<Vertex2d> vertices = graph->getVertices();    

    graph->clear();
    std::vector<Vertex2d> newVertexSet;

    for (unsigned i = 1; i < vertices.size(); i++) {

        if (communicationType == CONFIABLE) {
            newVertexSet = communicate(vertices[i - 1], vertices[i]);
        }
        if (communicationType == NO_CONFIABLE) {
            newVertexSet = communicateWithFails(vertices[i - 1], vertices[i]);
        }

        graph->addAll(newVertexSet);
    }

    // remove adjacents copys with the same value
    vertices = graph->getVertices();

    std::vector<Vertex2d>::iterator it;
//    it = std::unique(vertices.begin(),
//                     vertices.end(),
//                     predicateCompareVertex2d);
    vertices.resize(std::distance(vertices.begin(), it));
    graph->clear();
    graph->addAll(vertices);

}

std::vector<Vertex2d> SimplicialComplex::communicate(Vertex2d &process1, Vertex2d &process2)
{
    double amountDivisionX = (process2.getX() - process1.getX()) / (double) 4;
    double amountDivisionY = (process2.getY() - process1.getY()) / (double) 4;

    Vertex2d vertex_1 = Vertex2d(process1.getX() + amountDivisionX,
                                  process1.getY() + amountDivisionY);
    Vertex2d vertex_2 = Vertex2d(process1.getX() + 2*amountDivisionX,
                                  process1.getY() + 2*amountDivisionY);

    std::vector<Vertex2d> vertices;

    qDebug() << "communicate - vertices generados";
    qDebug() << vertex_1.c_str();
    qDebug() << vertex_2.c_str();

    vertices.push_back(vertex_1);
    vertices.push_back(vertex_2);

    return vertices;
}

std::vector<Vertex2d> SimplicialComplex::communicateWithFails(Vertex2d &process1, Vertex2d &process2)
{
    double amountDivisionX = (process2.getX() - process1.getX()) / (double) 4;
    double amountDivisionY = (process2.getY() - process1.getY()) / (double) 4;


    Vertex2d vertex_1 = Vertex2d(process1.getX() + amountDivisionX,
                                  process1.getY() + amountDivisionY);
    Vertex2d vertex_2 = Vertex2d(process1.getX() + 2*amountDivisionX,
                                  process1.getY() + 2*amountDivisionY);

    std::vector<Vertex2d> vertices;

    qDebug() << "communicateWithFails - vertices generados";
    qDebug() << process1.c_str();
    qDebug() << vertex_1.c_str();
    qDebug() << vertex_2.c_str();
    qDebug() << process2.c_str();


    vertices.push_back(process1);
    vertices.push_back(vertex_1);
    vertices.push_back(vertex_2);
    vertices.push_back(process2);

    return vertices;

}

void SimplicialComplex::animate()
{
    tick(TICK_AMOUNT);
    communicateProcesses();

    qDebug() << "Graph vertex";
    qDebug() << graph->c_str();

    updateGL();
}

void SimplicialComplex::reset()
{
    elapsedTime = 0;
    *graph = originalGraph;
    updateGL();
}

void SimplicialComplex::tick(int amount)
{
    if (elapsedTime > 360)
        elapsedTime = 0;
    elapsedTime += amount;
}

int SimplicialComplex::faceAtPosition(const QPoint &pos)
{
    const int MaxSize = 512;
    GLuint buffer[MaxSize];
    GLint viewport[4];

    makeCurrent();

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(MaxSize, buffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluPickMatrix(GLdouble(pos.x()), GLdouble(viewport[3] - pos.y()),5.0, 5.0, viewport);
    GLfloat x = GLfloat(width()) / height();
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    draw();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    if (!glRenderMode(GL_RENDER))
        return -1;
    return buffer[3];
}


bool SimplicialComplex::readFile(const QString &fileName)
{
    std::ifstream file(fileName.toStdString().c_str(), std::ios::in);
    if (!file) {
        std::cerr << "No fue posible leer el archivo " << fileName.toStdString() << std::endl;
        return false;
    }

    std::string line;
    while(std::getline(file, line)) {
        processline(line);
    }

//    printGraphData();

    // save original graph data
    originalGraph = graph->clone();

    draw();

    // update opengl
    updateGL();

    QApplication::restoreOverrideCursor();

    return true;
}

void SimplicialComplex::processline(std::string line)
{
    if (line.size() == 0)
        return;

    int x, y;
    std::istringstream iss(line);

    iss >> x;
    iss >> y;

    Vertex2d v = Vertex2d(x, y);
    graph->add(v);
}

void SimplicialComplex::printGraphData()
{
    qDebug() << "printGraphData()";
    std::vector<Vertex2d> vertices = graph->getVertices();
    qDebug() << "Vertices size " << vertices.size();

    for (unsigned i = 0; i < vertices.size(); i++) {
        qDebug() << vertices.at(i).getX() << ", " << vertices.at(i).getY();
    }

}

void SimplicialComplex::setCommunicationType(const QString &text)
{
    qDebug() << "setCommunicationType";
    qDebug() << text;

    if (text == "confiable")
        communicationType = 0;
    else
        communicationType = 1;
}
