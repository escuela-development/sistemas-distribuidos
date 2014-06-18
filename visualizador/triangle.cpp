#include <vector>
#include <algorithm>

#include "triangle.h"
#include "edge.h"

Triangle::Triangle(Edge arista1, Edge arista2, Edge arista3)
{
    aristas.push_back(arista1);
    aristas.push_back(arista2);
    aristas.push_back(arista3);
}

std::vector<Edge> Triangle::getAristas()
{
    std::vector<Edge> copy;
    std::copy(aristas.begin(), aristas.end(),
              std::back_inserter(copy));
    return copy;
}


