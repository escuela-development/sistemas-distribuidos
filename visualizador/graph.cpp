#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include "graph.h"
#include "vertex2d.h"


Graph::Graph()
{
}

const Graph &Graph::operator=(const Graph &derecha)
{
    if (&derecha != this) {
        copy(derecha);
    }
    else
        std::cout << "Intento de una grafica de asignarse a si misma\'n";

    return *this;
}

void Graph::clear()
{
    theGraph.clear();
}

void Graph::add(const Vertex2d v)
{
    theGraph.push_back(v);
}

void Graph::addAll(const std::vector<Vertex2d> &vertices)
{
    std::copy(vertices.begin(), vertices.end(),
              std::back_inserter(theGraph));
}

std::vector<Vertex2d> Graph::getVertices() const
{
    std::cout << "Graph - size " << theGraph.size();

    std::vector<Vertex2d> copy = std::vector<Vertex2d>(theGraph);
    return copy;
}

Graph Graph::clone() const
{
    Graph clone;
    clone.addAll(this->getVertices());

    return clone;
}

void Graph::copy(const Graph &from)
{
    theGraph.clear();
    this->addAll(from.getVertices());
}

const char* Graph::c_str()
{
    std::ostringstream out;
    std::copy(theGraph.begin(), theGraph.end(), std::ostream_iterator<Vertex2d>(out, "\n"));

    return out.str().c_str();
}
