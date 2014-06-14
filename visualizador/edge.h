#ifndef EDGE_H
#define EDGE_H

#include <iostream>

class Edge
{
    friend std::ostream &operator<<(std::ostream &, const Edge &);

public:
    Edge(int v1, int v2);
    int getVertex1();
    int getVertex2();

private:
    int num_vertex_1;
    int num_vertex_2;
};

#endif // EDGE_H
