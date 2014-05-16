#include <QtGui>
#include <QtOpenGL>
#include <QDebug>
#include "GL/glu.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <fstream>
#include <string>

#include "simplicialcomplex.h"
#include "vertex2d.h"

SimplicialComplex::SimplicialComplex(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    rotationX = -21.0;
    rotationY = -57.0;
    rotationZ = 0.0;
    faceColors[0] = Qt::red;
    faceColors[1] = Qt::green;
    faceColors[2] = Qt::blue;
    faceColors[3] = Qt::yellow;

    graph = new Graph();
}

SimplicialComplex::~SimplicialComplex()
{
    delete graph;
}

void SimplicialComplex::initializeGL()
{
    qglClearColor(Qt::white);
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

    // draw graph conntents
    glLineWidth(2.5f);
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_LINE_LOOP);
    {
        std::vector<Vertex2d> vertices = graph->getVertices();

        for (unsigned i = 0; i < vertices.size(); i++) {
//            std::cout << vertices.at(i).getX() << " "
//                      << vertices.at(i).getY() << std::endl;
            glVertex2d(vertices.at(i).getX(),
                       vertices.at(i).getY());
        }
    }
    glEnd();

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
//    QFile file(fileName);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        QMessageBox::warning(this, tr("Visualizador"),
//                             tr("Cannot read file %1: \n%2.")
//                             .arg(file.fileName())
//                             .arg(file.errorString()));
//        return false;
//    }

//    QTextStream in(&file);

//    QApplication::setOverrideCursor(Qt::WaitCursor);
//    while(!in.atEnd()) {
//        QString line = in.readLine();
//        processline(line);
//    }
//    printGraphData();
    std::ifstream file(fileName.toStdString().c_str(), std::ios::in);
    if (!file) {
        std::cerr << "No fue posible leer el archivo " << fileName.toStdString() << std::endl;
        return false;
    }

    std::string line;
    while(std::getline(file, line)) {
        processline(line);
    }

    printGraphData();
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
    graph->addVertex(v);
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
