#ifndef SIMPLICIALCOMPLEX_H
#define SIMPLICIALCOMPLEX_H

#include<QGLWidget>

#include "graph.h"

class SimplicialComplex : public QGLWidget
{
    Q_OBJECT

public:
    SimplicialComplex(QWidget *parent = 0);
    ~SimplicialComplex();

    bool readFile(const QString &fileName);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    void draw();
    int faceAtPosition(const QPoint &pos);
    void processline(std::string line);
    void printGraphData();

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[4];
    QPoint lastPos;

    Graph *graph;

};

#endif // SIMPLICIALCOMPLEX_H
