#include <iostream>

#include "edge.h"

Edge::Edge(int v1, int v2)
{
    num_vertex_1 = v1;
    num_vertex_2 = v2;
}

int Edge::getVertex1()
{
    return num_vertex_1;
}

int Edge::getVertex2()
{
    return num_vertex_2;
}

std::ostream &operator<<(std::ostream &salida, const Edge &e)
{
    salida << "[" << e.num_vertex_1 << "," << e.num_vertex_2 << "]";
    return salida;
}

