#ifndef GRAFICA_H
#define GRAFICA_H

#include <vector>
#include "vertex3d.h"
#include "edge.h"
#include "triangle.h"

class Grafica
{
public:
    Grafica();
    void addVertices(std::vector<Vertex3d> vertices);
    void addAristas(std::vector<Edge> aristas);
    void addTriangulos(std::vector<Triangle> triangulos);

    std::vector<Vertex3d> getVertices();
    std::vector<Edge> getAristas();
    std::vector<Triangle> getTriangulos();

    void limpiar();

private:
    std::vector<Vertex3d> _vertices;
    std::vector<Edge> _aristas;
    std::vector<Triangle> _triangulos;

};

#endif // GRAFICA_H
