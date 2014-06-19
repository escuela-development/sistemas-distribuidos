#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "GL/glu.h"

#include "Utils.h"
#include "vertex2d.h"
#include "vertex3d.h"
#include "edge.h"
#include "mecanismos_comunicacion.h"

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

std::string getTituloAplicacion(std::string tipoComunicacion, int iteracion)
{
    std::stringstream stream;

    if (tipoComunicacion == STR_CONFIABLE_COLOREADA) {
        stream << "Tipo de comunicacion confiable coloreada"
               << "\n" << iteracion;
    }
    if (tipoComunicacion == STR_NO_CONFIABLE_COLOREADA) {
        stream << "Tipo de comunicacion no confiable coloreada"
               << "\n" << iteracion;
    }
    if (tipoComunicacion == STR_CONFIABLE_NO_COLOREADA) {
        stream << "Tipo de comunicacion confiable no coloreada"
               << "\n" << iteracion;
    }
    if (tipoComunicacion == STR_NO_CONFIABLE_NO_COLOREADA) {
        stream << "Tipo de comunicacion no confiable no coloreada"
               << "\n" << iteracion;
    }

    return stream.str();
}
