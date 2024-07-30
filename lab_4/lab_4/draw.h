#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

void drawPixels(QGraphicsScene *scene, QImage *map, QVector<QPair<int, int>> pixels, QColor color);

#endif // DRAW_H
