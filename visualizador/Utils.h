#ifndef UTILS_H
#define UTILS_H

#include "vertex2d.h"

bool predicateCompareVertex2d(Vertex2d first, Vertex2d second)
{
    return (first.getX() == second.getX())
            && (first.getY() == second.getY());
}

#endif // UTILS_H
