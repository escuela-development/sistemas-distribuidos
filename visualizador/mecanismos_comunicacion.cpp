#include <vector>

#include "mecanismos_comunicacion.h"
#include "vertex3d.h"
#include "edge.h"


std::vector<Vertex3d> comunicarDeFormaColoreada(Vertex3d v1, Vertex3d v2)
{
    double amount_division_x = (v2.getX() - v1.getX()) / (double) 4;
    double amount_division_y = (v2.getY() - v1.getY()) / (double) 4;
    double amount_division_z = (v2.getZ() - v1.getZ()) / (double) 4;

    Vertex3d vertex_1 = Vertex3d(v1.getX() + amount_division_x,
                                 v1.getY() + amount_division_y,
                                 v1.getZ() + amount_division_z);

    Vertex3d vertex_2 = Vertex3d(v1.getX() + 2 * amount_division_x,
                                 v1.getY() + 2 * amount_division_y,
                                 v1.getZ() + 2 * amount_division_z);

    std::vector<Vertex3d> result;
    result.push_back(v1);
    result.push_back(vertex_1);
    result.push_back(vertex_2);
    result.push_back(v2);

    return result;
}
