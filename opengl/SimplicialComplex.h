#ifndef SIMPLICIALCOMPLEX_H
#define SIMPLICIALCOMPLEX_H

#include<QGLWidget>

class SimplicialComplex : public QGLWidget
{
    Q_OBJECT

public:
    SimplicialComplex(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    void draw();
    int faceAtPosition(const QPoint &pos);

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[4];
    QPoint lastPos;
};

#endif // SIMPLICIALCOMPLEX_H
