#include "draw.h"

void drawPixels(QGraphicsScene *scene, QImage *map, QVector<QPair<int, int>> pixels, QColor color)
{
    for (int i = 0; i < pixels.size(); ++i)
    {
        int x = pixels[i].first;
        int y = pixels[i].second;
        map->setPixelColor(x, y, color);
    }

    scene->addPixmap(QPixmap::fromImage(*map));
}
