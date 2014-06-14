#include <iostream>
#include "vertex3d.h"

Vertex3d::Vertex3d(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vertex3d::getX()
{
    return x;
}

void Vertex3d::setX(double x)
{
    this->x = x;
}

double Vertex3d::getY()
{
    return y;
}

void Vertex3d::setY(double y)
{
    this->y = y;
}

double Vertex3d::getZ()
{
    return z;
}

void Vertex3d::setZ(double z)
{
    this->z = z;
}

std::ostream &operator<<(std::ostream &salida, const Vertex3d &v)
{
    salida << "[" << v.x << "," << v.y
           << "," << v.z << "]";
    return salida;
}
