#ifndef ALGOSES_H
#define ALGOSES_H

#include <QVector>
#include <QColor>

void addPixels(QVector<QPair<int, int>> &pixels, double xcent, double ycent, int x, int y);

void canonicCircleDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double radius);

void canonicEllipsDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double a, double b);

void parametricCircleDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double radius);

void parametricEllipsDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double a, double b);

void brezenhemCircleDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double radius);

void brezenhemEllipsDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double a, double b);

void middleCircleDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double radius);

void middleEllipsDraw(QVector<QPair<int, int>> &pixels, double xcent, double ycent, double a, double b);

#endif // ALGOSES_H
