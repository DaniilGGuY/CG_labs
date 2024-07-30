#ifndef VU_H
#define VU_H

#include <QVector>
#include <QColor>

#define EPS     1e-9

int vuAlgorithm(QVector<QPair<int, int>> &pixels, QVector<QColor> &intense, double x_start, double y_start, double x_end, double y_end, \
                     double max_intense, QColor back, QColor fore);

#endif // VU_H
