#ifndef CUTTER_H
#define CUTTER_H

#include <QVector>
#include <cmath>

#include "special_utility.h"

#define EPS       1e-3

enum Direction
{
    ERR = 0,
    CLOCKWISE = 1,
    COUNTERCLOCKWISE = 2,
};

Direction checkDirection(QVector<QPair<int, int>> polygon);

int scalarMult(QPair<int, int> a, QPair<int, int> b);

Segment cutByCirusBek(QVector<QPair<int, int>> cutter, Segment seg);

#endif // CUTTER_H
