#ifndef DIGITALDIFAN_H
#define DIGITALDIFAN_H

#include <QVector>

#define EPS     1e-9

int digitalDifAnalizer(QVector<QPair<int, int>> &pixels, double x_start, double y_start, double x_end, double y_end);

#endif // DIGITALDIFAN_H
