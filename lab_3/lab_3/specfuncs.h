#ifndef SPECFUNCS_H
#define SPECFUNCS_H

#include <QColor>

QColor calcIntense(QColor back, QColor fore, double intense, double max_intense);

void turnPoint(double &x_end, double &y_end, double x_start, double y_start, double angle);

#endif // SPECFUNCS_H
