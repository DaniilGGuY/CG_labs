#include <cmath>
#include <QDebug>

#include "brezenhem.h"
#include "specfuncs.h"

static int sign(double x)
{
    if (fabs(x) < EPS)
        return 0;
    else if (x > 0)
        return 1;

    return -1;
}

int brezenhemFloat(QVector<QPair<int, int>> &pixels, double x_start, double y_start, double x_end, double y_end)
{
    int steps = 0;

    if (fabs(x_start - x_end) < EPS && fabs(y_start - y_end) < EPS)
        pixels.append(qMakePair(round(x_start), round(y_start)));
    else
    {
        int dx = round(x_end - x_start), dy = round(y_end - y_start);
        int x = round(x_start), y = round(y_start);
        int xb = x, yb = y;
        int sx = sign(dx), sy = sign(dy);
        bool exchange = 0;
        dx = abs(dx), dy = abs(dy);
        if (dy > dx)
        {
            int tmp = dx;
            dx = dy;
            dy = tmp;
            exchange = 1;
        }

        double tan = (double)dy / dx;
        double err = tan - 0.5;
        for (int i = 0; i < dx; ++i)
        {
            pixels.append(qMakePair(x, y));
            if (err >= 0)
            {
                if (exchange)
                    x += sx;
                else
                    y += sy;

                err -= 1;
            }

            if (err <= 0)
            {
                if (exchange)
                    y += sy;
                else
                    x += sx;

                err += tan;
            }

            if (xb != x && yb != y)
                steps += 1;

            xb = x;
            yb = y;
        }
    }

    return steps;
}

int brezenhemInt(QVector<QPair<int, int>> &pixels, double x_start, double y_start, double x_end, double y_end)
{
    int steps = 0;

    if (fabs(x_start - x_end) < EPS && fabs(y_start - y_end) < EPS)
        pixels.append(qMakePair(x_start, y_start));
    else
    {
        int dx = round(x_end - x_start), dy = round(y_end - y_start);
        int x = round(x_start), y = round(y_start);
        int xb = x, yb = y;
        int sx = sign(dx), sy = sign(dy);
        bool exchange = 0;
        dx = abs(dx), dy = abs(dy);
        if (dy > dx)
        {
            int tmp = dx;
            dx = dy;
            dy = tmp;
            exchange = 1;
        }

        int err = 2 * dy - dx;
        for (int i = 0; i < dx; ++i)
        {
            pixels.append(qMakePair(x, y));
            if (err >= 0)
            {
                if (exchange)
                    x += sx;
                else
                    y += sy;

                err -= 2 * dx;
            }

            if (err <= 0)
            {
                if (exchange)
                    y += sy;
                else
                    x += sx;

                err += 2 * dy;
            }

            if (xb != x && yb != y)
                steps += 1;

            xb = x;
            yb = y;
        }
    }

    return steps;
}

int brezenhemSmooth(QVector<QPair<int, int>> &pixels, QVector<QColor> &intense, double x_start, double y_start, double x_end, double y_end, \
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
        int dx = round(x_end - x_start), dy = round(y_end - y_start);
        int x = round(x_start), y = round(y_start);
        int xb = x, yb = y;
        int sx = sign(dx), sy = sign(dy);
        bool exchange = 0;
        dx = abs(dx), dy = abs(dy);
        if (dy > dx)
        {
            int tmp = dx;
            dx = dy;
            dy = tmp;
            exchange = 1;
        }

        double tan = (double)dy / dx * max_intense;
        double err = max_intense / 2;
        double w = max_intense - tan;
        while (x != round(x_end) || y != round(y_end))
        {
            pixels.append(qMakePair(x, y));
            intense.append(calcIntense(back, fore, err, max_intense));
            if (err < w)
            {
                if (!exchange)
                    x += sx;
                else
                    y += sy;

                err += tan;
            }
            else
            {
                x += sx;
                y += sy;
                err -= w;
            }

            if (xb != x && yb != y)
                steps += 1;

            xb = x;
            yb = y;
        }
    }

    return steps;
}
