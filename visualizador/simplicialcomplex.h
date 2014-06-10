#ifndef SIMPLICIALCOMPLEX_H
#define SIMPLICIALCOMPLEX_H

#include<QGLWidget>
#include<vector>

#include "graph.h"
#include "vertex2d.h"


class SimplicialComplex : public QGLWidget
{
    Q_OBJECT

public:
    SimplicialComplex(QWidget *parent = 0);
    ~SimplicialComplex();

    bool readFile(const QString &fileName);

public slots:
    void animate();
    void reset();
    void setCommunicationType(const QString& text);

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
    void alternateColor(int index);
    void printGraphData();
    void tick(int amount);
    void communicateProcesses();
    std::vector<Vertex2d> communicateWithFails(Vertex2d &process1, Vertex2d &process2);
    std::vector<Vertex2d> communicate(Vertex2d &process1, Vertex2d &process2);


    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[4];
    QPoint lastPos;

    Graph *graph;
    Graph originalGraph;

    bool toggleColor;
    int elapsedTime;
    int communicationType;
    const int TICK_AMOUNT;
    const int CONFIABLE;
    const int NO_CONFIABLE;

};

#endif // SIMPLICIALCOMPLEX_H
