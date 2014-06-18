#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "edge.h"

class Triangle
{
public:
    Triangle(Edge arista1, Edge arista2, Edge arista3);
    std::vector<Edge> getAristas();


private:
    std::vector<Edge> aristas;
};

#endif // TRIANGLE_H
