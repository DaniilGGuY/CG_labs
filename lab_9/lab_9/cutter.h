#ifndef CUTTER_H
#define CUTTER_H

#include <QVector>
#include <cmath>

#define EPS       1e-3

int vectMult(QPair<int, int> V1, QPair<int, int> V2);

int scalarMult(QPair<int, int> V1, QPair<int, int> V2);

bool checkConvexity(QVector<QPair<int, int>> &polygon);

int checkPointVisibility(QPair<int, int> point, QPair<int, int> P1, QPair<int, int> P2);

bool isCross(QPair<int, int> P1, QPair<int, int> P2, QPair<int, int> W1, QPair<int, int> W2);

QVector<QPair<int, int>> cutSazerlandHodgman(QVector<QPair<int, int>> cutter, QVector<QPair<int, int>> polygon);

#endif // CUTTER_H
