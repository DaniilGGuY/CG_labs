#ifndef CUTTER_H
#define CUTTER_H

#include <QPair>
#include <cmath>

#include "special_utility.h"

#define EPS       1e-3

int calcTCode(Cutter cut, QPair<int, int> point);

Segment segByPoints(QPair<int, int> P1, QPair<int, int> P2);

Segment cutByMiddlePoint(Cutter cut, Segment seg);

#endif // CUTTER_H
