#include <cmath>

#include "specfuncs.h"

QColor calcIntense(QColor back, QColor fore, double intense, double max_intense)
{
    QColor res;

    res.setRed(fore.red() + double(back.red() - fore.red()) / max_intense * (max_intense - intense));
    res.setGreen(fore.green() + double(back.green() - fore.green()) / max_intense * (max_intense - intense));
    res.setBlue(fore.blue() + double(back.blue() - fore.blue()) / max_intense * (max_intense - intense));

    return res;
}

void turnPoint(double &x_end, double &y_end, double x_start, double y_start, double angle)
{
    double radians = angle * M_PI / 180;
    double sin_angle = sin(radians);
    double cos_angle = cos(radians);

    x_end -= x_start;
    y_end -= y_start;

    double tmp = x_end;
    x_end = x_end * cos_angle - y_end * sin_angle;
    y_end = y_end * cos_angle + tmp * sin_angle;

    x_end += x_start;
    y_end += y_start;
}
