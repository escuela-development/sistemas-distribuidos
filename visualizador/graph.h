#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "vertex2d.h"

class Graph
{
public:
    Graph();

    const Graph &operator=(const Graph&);
    void add(const Vertex2d v);
    void addAll(const std::vector<Vertex2d> &vertices);
    std::vector<Vertex2d> getVertices() const;
    const char* c_str();

    void clear();
    Graph clone() const;

private:
    void copy(const Graph &from);

    std::vector<Vertex2d> theGraph;
};
#endif // GRAPH_H
