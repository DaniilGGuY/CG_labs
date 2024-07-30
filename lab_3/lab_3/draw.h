#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

void drawPixels(QGraphicsScene *scene, QVector<QPair<int, int>> pixels, QColor color);

void drawPixelsVector(QGraphicsScene *scene, QVector<QPair<int, int>> pixels, QVector<QColor> intense);

#endif // DRAW_H
