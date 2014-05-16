#ifndef VERTEX2D_H
#define VERTEX2D_H

class Vertex2d
{
public:
    Vertex2d(double x, double y);
    Vertex2d();
    double getX();
    void setX(double x);
    double getY();
    void setY(double y);

private:
    double x;
    double y;
};

#endif // VERTEX2D_H
