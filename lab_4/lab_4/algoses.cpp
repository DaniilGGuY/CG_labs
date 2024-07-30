#include <cmath>
#include <QDebug>

#include "algoses.h"

void addPixels(QVector<QPair<int, int>> &pixels, double xcent, double ycent, int x, int y)
{
    pixels.append(qMakePair(round(xcent + x), round(ycent + y)));
    pixels.append(qMakePair(round(xcent - x), round(ycent + y)));
    pixels.append(qMakePair(round(xcent + x), round(ycent - y)));
    pixels.append(qMakePair(round(xcent - x), round(ycent - y)));
}

void canonicCircleDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double radius)
{
    double r_r = radius * radius;
    for (int x = 0; x < round(radius / sqrt(2)) + 1; ++x)
    {
        int y = round(sqrt(r_r - x * x));
        addPixels(pixels, xcent, ycent, x, y);
        addPixels(pixels, xcent, ycent, y, x);
    }
}

void canonicEllipsDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double a, double b)
{
    double a_a = a * a, b_b = b * b;
    for (int x = 0; x < round(a / sqrt(1 + b_b / a_a)) + 1; ++x)
    {
        int y = round(b / a * sqrt(a_a - x * x));
        addPixels(pixels, xcent, ycent, x, y);
    }

    for (int y = 0; y < round(b / sqrt(1 + a_a / b_b)) + 1; ++y)
    {
        int x = round(a / b * sqrt(b_b - y * y));
        addPixels(pixels, xcent, ycent, x, y);
    }
}

void parametricCircleDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double radius)
{
    double step = 1 / radius, t = 0;
    while (t <= M_PI / 4 + step)
    {
        int x = round(radius * cos(t)), y = round(radius * sin(t));
        addPixels(pixels, xcent, ycent, x, y);
        addPixels(pixels, xcent, ycent, y, x);
        t += step;
    }
}

void parametricEllipsDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double a, double b)
{
    double step = (a > b) ? 1 / a : 1 / b, t = 0;
    while (t <= M_PI / 2 + step)
    {
        int x = round(a * cos(t)), y = round(b * sin(t));
        addPixels(pixels, xcent, ycent, x, y);
        t += step;
    }
}

void brezenhemCircleDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double radius)
{
    int x = 0, y = round(radius);
    int delta = 2 * (1 - round(radius));
    addPixels(pixels, xcent, ycent, x, y);
    addPixels(pixels, xcent, ycent, y, x);
    while (y > x)
    {
        int d = 2 * (delta + y) - 1;
        x += 1;

        if (d > 0)
        {
            y -= 1;
            delta += 2 * (x - y + 1);
        }
        else
            delta += 2 * x + 1;

        addPixels(pixels, xcent, ycent, x, y);
        addPixels(pixels, xcent, ycent, y, x);
    }
}

void brezenhemEllipsDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double a, double b)
{
    int x = 0, y = round(b);
    int a_a = round(a * a), b_b = round(b * b);
    int delta = b_b - a_a * (2 * b + 1);
    addPixels(pixels, xcent, ycent, x, y);
    while (y > 0)
    {
        if (delta == 0)
        {
            y -= 1;
            x += 1;
            delta += b_b * (2 * x + 1) + a_a * (1 - 2 * y);
        }
        else if (delta < 0)
        {
            int d = 2 * delta + a_a * (2 * y + 2);
            x += 1;
            if (d > 0)
            {
                y -= 1;
                delta += b_b * (2 * x + 1) + a_a * (1 - 2 * y);
            }
            else
                delta += b_b * (2 * x + 1);
        }
        else
        {
            int d = 2 * delta + b_b * (2 - 2 * x);
            y -= 1;
            if (d > 0)
                delta += a_a * (1 - 2 * y);
            else
            {
                x += 1;
                delta += b_b * (2 * x + 1) + a_a * (1 - 2 * y);
            }
        }

        addPixels(pixels, xcent, ycent, x, y);
    }
}

void middleCircleDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double radius)
{
    int x = round(radius), y = 0;
    int delta = 1 - round(radius);
    addPixels(pixels, xcent, ycent, x, y);
    addPixels(pixels, xcent, ycent, y, x);
    while (x > y)
    {
        if (delta > 0)
        {
            x -= 1;
            y += 1;
            delta += 2 * y + 1 - 2 * x;
        }
        else
        {
            y += 1;
            delta += 2 * y + 1;
        }

        addPixels(pixels, xcent, ycent, x, y);
        addPixels(pixels, xcent, ycent, y, x);
    }
}

void middleEllipsDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double a, double b)
{
    double a_a = a * a, b_b = b * b, x = a, y = 0;
    double delta = a_a - round(b_b * (a - 1 / 4));
    addPixels(pixels, xcent, ycent, x, y);
    while (y <= round(b / sqrt(1 + a_a / b_b)))
    {
        if (delta < 0)
        {
            y += 1;
            delta += 2 * a_a * y + 1;
        }
        else
        {
            x -= 1;
            y += 1;
            delta += 2 * a_a * y - 2 * b_b * x + 1;
        }

        addPixels(pixels, xcent, ycent, x, y);
    }

    x = 0, y = b;
    delta = b_b - round(a_a * (b - 1 / 4));
    addPixels(pixels, xcent, ycent, x, y);
    while (x <= round(a / sqrt(1 + b_b / a_a)))
    {
        if (delta < 0)
        {
            x += 1;
            delta += 2 * b_b * x + 1;
        }
        else
        {
            x += 1;
            y -= 1;
            delta += 2 * b_b * x - 2 * a_a * y + 1;
        }

        addPixels(pixels, xcent, ycent, x, y);
    }
}
