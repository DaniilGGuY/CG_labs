#include "draw.h"

void drawPixels(QGraphicsScene *scene, QVector<QPair<int, int>> pixels, QColor color)
{
    QPen pen(color, 1);
    for (int i = 0; i < pixels.size(); ++i)
    {
        int x = pixels[i].first;
        int y = pixels[i].second;
        scene->addLine(x, y, x, y, pen);
    }
}

void drawPixelsVector(QGraphicsScene *scene, QVector<QPair<int, int>> pixels, QVector<QColor> intense)
{
    for (int i = 0; i < pixels.size(); ++i)
    {
        int x = pixels[i].first;
        int y = pixels[i].second;
        scene->addLine(x, y, x, y, QPen(intense[i], 1));
    }
}
