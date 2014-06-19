#include <vector>
#include <algorithm>

#include "triangle.h"
#include "edge.h"
#include "vertex3d.h"

Triangle::Triangle(Vertex3d vertex1, Vertex3d vertex2, Vertex3d vertex3)
{
    _vertices.push_back(vertex1);
    _vertices.push_back(vertex2);
    _vertices.push_back(vertex3);
}

std::vector<Vertex3d> Triangle::getVertices()
{
    std::vector<Vertex3d> copy;
    std::copy(_vertices.begin(), _vertices.end(),
              std::back_inserter(copy));
    return copy;
}

std::vector<Edge> Triangle::getAristas()
{
    Edge arista1 = Edge(0, 1);
    Edge arista2 = Edge(1, 2);
    Edge arista3 = Edge(2, 0);

    std::vector<Edge> result;
    result.push_back(arista1);
    result.push_back(arista2);
    result.push_back(arista3);

    return result;
}


