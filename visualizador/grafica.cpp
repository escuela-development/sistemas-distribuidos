#include<vector>
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

void Grafica::addTriangulos(std::vector<Triangle> triangulos)
{
    std::copy(triangulos.begin(), triangulos.end(),
              std::back_inserter(_triangulos));
}

std::vector<Vertex3d> Grafica::getVertices()
{
    return _vertices;
}

std::vector<Edge> Grafica::getAristas()
{
    return _aristas;
}

std::vector<Triangle> Grafica::getTriangulos()
{
    return _triangulos;
}

void Grafica::limpiar()
{
    _vertices.clear();
    _aristas.clear();
    _triangulos.clear();
}
