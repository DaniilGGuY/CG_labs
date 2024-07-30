#include <cmath>

#include "vu.h"
#include "specfuncs.h"

int vuAlgorithm(QVector<QPair<int, int>> &pixels, QVector<QColor> &intense, double x_start, double y_start, double x_end, double y_end, \
                     double max_intense, QColor back, QColor fore)
{
    int steps = 0;

    if (fabs(x_start - x_end) < EPS && fabs(y_start - y_end) < EPS)
    {
        pixels.append(qMakePair(x_start, y_start));
        intense.append(calcIntense(back, fore, max_intense, max_intense));
    }
    else
    {
        bool exchange = fabs(y_end - y_start) > fabs(x_end - x_start);
        if (exchange)
        {
            double tmp = x_start;
            x_start = y_start;
            y_start = tmp;
            tmp = x_end;
            x_end = y_end;
            y_end = tmp;
        }
        if (x_start > x_end)
        {
            double tmp = x_start;
            x_start = x_end;
            x_end = tmp;
            tmp = y_start;
            y_start = y_end;
            y_end = tmp;
        }

        double dx = x_end - x_start, dy = y_end - y_start;
        double tan = (fabs(dx) < EPS) ? 1 : dy / dx;

        int cur_point_x = round(x_start);
        double cur_point_y = y_start + tan * (cur_point_x - x_start);
        int xpxl1 = cur_point_x;
        cur_point_x = round(x_end);
        int xpxl2 = cur_point_x;

        if (exchange)
        {
            for (int x = xpxl1; x < xpxl2; ++x)
            {
                pixels.append(qMakePair(floor(cur_point_y), x + 1));
                pixels.append(qMakePair(floor(cur_point_y) + 1, x + 1));
                intense.append(calcIntense(back, fore, floor((max_intense - 1) * fabs(1 - cur_point_y + floor(cur_point_y))), max_intense));
                intense.append(calcIntense(back, fore, floor((max_intense - 1) * fabs(cur_point_y - floor(cur_point_y))), max_intense));
                if (x < round(x_end) && floor(cur_point_y) != floor(cur_point_y + tan))
                    steps += 1;

                cur_point_y += tan;
            }
        }
        else
        {
            for (int x = xpxl1; x < xpxl2; ++x)
            {
                pixels.append(qMakePair(x + 1, floor(cur_point_y)));
                pixels.append(qMakePair(x + 1, floor(cur_point_y) + 1));
                intense.append(calcIntense(back, fore, floor((max_intense - 1) * fabs(1 - cur_point_y + floor(cur_point_y))), max_intense));
                intense.append(calcIntense(back, fore, floor((max_intense - 1) * fabs(cur_point_y - floor(cur_point_y))), max_intense));
                if (x < round(x_end) && floor(cur_point_y) != floor(cur_point_y + tan))
                    steps += 1;

                cur_point_y += tan;
            }
        }
    }

    return steps;
}
