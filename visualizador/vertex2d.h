#ifndef VERTEX2D_H
#define VERTEX2D_H

#include <iostream>

class Vertex2d
{
    friend std::ostream &operator<<(std::ostream &, const Vertex2d &);

public:
    Vertex2d(double x, double y);
    Vertex2d();        
    double getX();
    void setX(double x);
    double getY();
    void setY(double y);
    const char* c_str();

private:
    double x;
    double y;
};

#endif // VERTEX2D_H
