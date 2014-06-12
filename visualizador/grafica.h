#ifndef GRAFICA_H
#define GRAFICA_H

#include <vector>
#include "vertex3d.h"
#include "edge.h"

class Grafica
{
public:
    Grafica();
    void addVertices(std::vector<Vertex3d> vertices);
    void addAristas(std::vector<Edge> aristas);

    std::vector<Vertex3d> getVertices();
    std::vector<Edge> getAristas();

private:
    std::vector<Vertex3d> _vertices;
    std::vector<Edge> _aristas;
};

#endif // GRAFICA_H
