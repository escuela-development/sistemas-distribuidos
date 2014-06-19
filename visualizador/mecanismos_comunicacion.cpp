#include <vector>
#include <iterator>

#include "mecanismos_comunicacion.h"
#include "vertex3d.h"
#include "edge.h"
#include "triangle.h"
#include "Utils.h"


std::vector<Vertex3d> comunicarDeFormaColoreada(Vertex3d v1, Vertex3d v2)
{
    double amount_division_x = (v2.getX() - v1.getX()) / (double) 3;
    double amount_division_y = (v2.getY() - v1.getY()) / (double) 3;
    double amount_division_z = (v2.getZ() - v1.getZ()) / (double) 3;

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

std::vector<Vertex3d> comunicarDeFormaNoColoreada(Vertex3d v1, Vertex3d v2)
{
    double midpoint_x = (v1.getX() + v2.getX()) / (double) 2;
    double midpoint_y = (v1.getY() + v2.getY()) / (double) 2;
    double midpoint_z = (v1.getZ() + v2.getZ()) / (double) 2;

    Vertex3d midpoint = Vertex3d(midpoint_x, midpoint_y, midpoint_z);

    std::vector<Vertex3d> result;
    result.push_back(v1);
    result.push_back(midpoint);
    result.push_back(v2);

    return result;
}

std::vector<Triangle> comunicar(TipoComunicacion comunicacion, Triangle triangulo)
{
    std::vector<Vertex3d> vertices = triangulo.getVertices();

    double baricentro_x = (vertices[0].getX()
            + vertices[1].getX()
            + vertices[2].getX()) / (double)3;

    double baricentro_y = (vertices[0].getY()
            + vertices[1].getY()
            + vertices[2].getY()) / (double)3;

    double baricentro_z = (vertices[0].getZ()
            + vertices[1].getZ()
            + vertices[2].getZ()) / (double)3;

    Vertex3d baricentro = Vertex3d(baricentro_x, baricentro_y, baricentro_z);
    std::vector<Vertex3d> verticesGenerados;
    std::vector<Triangle> triangulosGenerados;

    verticesGenerados.push_back(baricentro);

    if (comunicacion == NO_CONFIABLE_NO_COLOREADA) {

        std::vector<Vertex3d> resultado;
        std::vector<Edge> aristas = triangulo.getAristas();
        for (unsigned i = 0; i < aristas.size(); i++) {

            Edge edge = aristas[i];
            resultado = comunicarDeFormaNoColoreada(
                                vertices[edge.getVertex1()],
                                vertices[edge.getVertex2()]);
            std::copy(resultado.begin(), resultado.end(),
                      std::back_inserter(verticesGenerados));
        }

        std::cout << "vertices generados metodo comunicar antes eliminar duplicados \n"
                     << print(verticesGenerados) << std::endl;

        // debido a la forma de construccion, el vector
        // resultado contiene vertices repetidos en las posiciones
        // 4, 7 y 9.
        verticesGenerados.pop_back();   // eliminar elemento 9

        // eliminar 4 elemento, despues de esto el 7 elemento se
        // convierte en el sexto elemento
        verticesGenerados.erase(verticesGenerados.begin() + 3);

         // eliminar 6 elemento
        verticesGenerados.erase(verticesGenerados.begin() + 5);

        std::cout << "vertices generados metodo comunicar \n"
                     << print(verticesGenerados) << std::endl;

        // solo nos interesan los triangulos generados
        Triangle t = Triangle(
                    verticesGenerados[0],
                    verticesGenerados[1],
                    verticesGenerados[2]);
        triangulosGenerados.push_back(t);

        t = Triangle(
                    verticesGenerados[0],
                    verticesGenerados[2],
                    verticesGenerados[3]);
        triangulosGenerados.push_back(t);

        t = Triangle(
                    verticesGenerados[0],
                    verticesGenerados[3],
                    verticesGenerados[4]);
        triangulosGenerados.push_back(t);

        t = Triangle(
                    verticesGenerados[0],
                    verticesGenerados[4],
                    verticesGenerados[5]);
        triangulosGenerados.push_back(t);

        t = Triangle(
                    verticesGenerados[0],
                    verticesGenerados[5],
                    verticesGenerados[6]);
        triangulosGenerados.push_back(t);

        t = Triangle(
                    verticesGenerados[0],
                    verticesGenerados[6],
                    verticesGenerados[1]);
        triangulosGenerados.push_back(t);
    }

    return triangulosGenerados;
}

