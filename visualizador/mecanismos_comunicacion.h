#ifndef MECANISMOS_COMUNICACION_H
#define MECANISMOS_COMUNICACION_H

#include <vector>
#include <string>

#include "vertex3d.h"
#include "edge.h"
#include "triangle.h"
#include "grafica.h"


const std::string STR_CONFIABLE_COLOREADA = "confiable_coloreada";
const std::string STR_NO_CONFIABLE_COLOREADA = "no_confiable_coloreada";
const std::string STR_CONFIABLE_NO_COLOREADA = "confiable_no_coloreada";
const std::string STR_NO_CONFIABLE_NO_COLOREADA = "no_confiable_no_coloreada";

enum TipoComunicacion{CONFIABLE_COLOREADA,
                     NO_CONFIABLE_COLOREADA,
                     CONFIABLE_NO_COLOREADA,
                     NO_CONFIABLE_NO_COLOREADA};

std::vector<Vertex3d> comunicarDeFormaColoreada(Vertex3d v1, Vertex3d v2);
std::vector<Vertex3d> comunicarDeFormaNoColoreada(Vertex3d v1, Vertex3d v2);

std::vector<Triangle> comunicar(TipoComunicacion comunicacion, Triangle triangulo);



#endif // MECANISMOS_COMUNICACION_H
