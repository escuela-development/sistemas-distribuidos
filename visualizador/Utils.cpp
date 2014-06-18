#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "GL/glu.h"

#include "Utils.h"
#include "vertex2d.h"
#include "vertex3d.h"
#include "edge.h"

bool predicateCompareVertex2d(Vertex2d first, Vertex2d second)
{
    return (first.getX() == second.getX())
            && (first.getY() == second.getY());
}

std::string print(std::vector<Vertex3d> vertices)
{
    std::ostringstream out;
    std::copy(vertices.begin(), vertices.end(),
              std::ostream_iterator<Vertex3d>(out, "\n"));
    return out.str();
}

std::string print(std::vector<Edge> aristas)
{
    std::ostringstream out;
    std::copy(aristas.begin(), aristas.end(),
              std::ostream_iterator<Edge>(out, "\n"));
    return out.str();
}

void dibujarCilindro(double radio, double altura, int slices, int stacks)
{    
    gluCylinder(gluNewQuadric(), radio, radio, altura, slices, stacks);
}

void dibujarEsfera(double radio, int slices, int stacks)
{
    gluSphere(gluNewQuadric(), radio, slices, stacks);
}
