#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "vertex2d.h"

class Graph
{
public:
    Graph();
    void addVertex(const Vertex2d v);
    std::vector<Vertex2d> getVertices();

private:
    std::vector<Vertex2d> theGraph;
};
#endif // GRAPH_H
