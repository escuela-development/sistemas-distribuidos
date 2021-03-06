#ifndef VERTEX3D_H
#define VERTEX3D_H

#include <iostream>

class Vertex3d
{
    friend std::ostream &operator<<(std::ostream &, const Vertex3d &);

public:
    Vertex3d(double x, double y, double z);
    double getX();
    double getY();
    double getZ();
    void setX(double x);
    void setY(double y);
    void setZ(double z);


private:
    double x;
    double y;
    double z;
};

#endif // VERTEX3D_H
