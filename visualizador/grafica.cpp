#include <algorithm>
#include <iterator>

#include "grafica.h"

Grafica::Grafica()
{
}

void Grafica::addVertices(std::vector<Vertex3d> vertices)
{
    std::copy(vertices.begin(), vertices.end(),
            std::back_inserter(_vertices));
}

void Grafica::addAristas(std::vector<Edge> aristas)
{
    std::copy(aristas.begin(), aristas.end(),
              std::back_inserter(_aristas));
}

std::vector<Vertex3d> Grafica::getVertices()
{
    return _vertices;
}

std::vector<Edge> Grafica::getAristas()
{
    return _aristas;
}
