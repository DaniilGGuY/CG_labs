#ifndef BREZENHEM_H
#define BREZENHEM_H

#include <QVector>
#include <QColor>

#define EPS     1e-9

int brezenhemFloat(QVector<QPair<int, int>> &pixels, double x_start, double y_start, double x_end, double y_end);

int brezenhemInt(QVector<QPair<int, int>> &pixels, double x_start, double y_start, double x_end, double y_end);

int brezenhemSmooth(QVector<QPair<int, int>> &pixels, QVector<QColor> &intense, double x_start, double y_start, double x_end, double y_end, \
                     double max_intense, QColor back, QColor fore);

#endif // BREZENHEM_H
