#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "GL/glu.h"

#include "vertex2d.h"
#include "vertex3d.h"
#include "edge.h"

bool predicateCompareVertex2d(Vertex2d first, Vertex2d second);
std::string print(std::vector<Vertex3d> vertices);
std::string print(std::vector<Edge> aristas);

void dibujarCilindro(double radio, double altura, int slices, int stacks);
void dibujarEsfera(double radio, int slices, int stacks);

#endif // UTILS_H
