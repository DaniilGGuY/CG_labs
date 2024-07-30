#include <cmath>

#include "digitaldifan.h"

int digitalDifAnalizer(QVector<QPair<int, int>> &pixels, double x_start, double y_start, double x_end, double y_end)
{
    int steps = 0;

    if (fabs(x_start - x_end) < EPS && fabs(y_start - y_end) < EPS)
        pixels.append(qMakePair(round(x_start), round(y_start)));
    else
    {
        double dx = fabs(x_start - x_end), dy = fabs(y_start - y_end), x = x_start, y = y_start;
        double b = (dx >= dy) ? dx : dy;
        dx = (x_end - x_start) / b;
        dy = (y_end - y_start) / b;
        for (int i = 0; i < ceil(b); ++i)
        {
            pixels.append(qMakePair(round(x), round(y)));
            if (round(x + dx) != round(x) && round(y + dy) != round(y))
                steps += 1;
            x += dx;
            y += dy;
        }
    }

    return steps;
}
