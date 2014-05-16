#include "vertex2d.h"

Vertex2d::Vertex2d()
{
    x = 0.0;
    y = 0.0;
}

Vertex2d::Vertex2d(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Vertex2d::getX()
{
    return x;
}

void Vertex2d::setX(double x)
{
    this->x = x;
}

double Vertex2d::getY()
{
    return y;
}

void Vertex2d::setY(double y)
{
    this->y = y;
}
