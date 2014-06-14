#ifndef MECANISMOS_COMUNICACION_H
#define MECANISMOS_COMUNICACION_H

#include <vector>
#include <string>

#include "vertex3d.h"
#include "edge.h"


const std::string STR_CONFIABLE_COLOREADA = "confiable_coloreada";
const std::string STR_NO_CONFIABLE_COLOREADA = "no_confiable_coloreada";

std::vector<Vertex3d> comunicarNoConfiableColoreado(Vertex3d v1, Vertex3d v2);


#endif // MECANISMOS_COMUNICACION_H
