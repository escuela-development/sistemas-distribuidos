#include "graph.h"
#include <iostream>

Graph::Graph()
{
}

void Graph::addVertex(const Vertex2d v)
{
    theGraph.push_back(v);
}

std::vector<Vertex2d> Graph::getVertices()
{
    std::cout << "Graph - size " << theGraph.size();

    std::vector<Vertex2d> copy = std::vector<Vertex2d>(theGraph);
    return copy;
}
