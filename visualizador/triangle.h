#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "vertex3d.h"
#include "edge.h"

class Triangle
{
public:
    Triangle(Vertex3d vertex1, Vertex3d vertex2, Vertex3d vertex3);
    std::vector<Vertex3d> getVertices();
    std::vector<Edge> getAristas();

private:
    std::vector<Vertex3d> _vertices;
};

#endif // TRIANGLE_H
