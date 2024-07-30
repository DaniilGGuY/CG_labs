#include <chrono>

#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent) { map = new QImage(XSIZE, YSIZE, QImage::Format_ARGB32); }

PaintScene::~PaintScene() {}

void PaintScene::set_back(QColor back) { this->back = back; }

void PaintScene::set_draw(QColor draw) { this->draw = draw; }

void PaintScene::set_mode(Mode mode) { this->mode = mode; }

void PaintScene::add_point_handle(int x, int y)
{
    points_vec.append(qMakePair(x, y));
    qDebug() << "Added point (" << QString::number(x) << ":" << QString::number(y) << ")";
}

void PaintScene::clear_points_vec() { points_vec.clear(); }

void PaintScene::delete_draw()
{
    points_vec.clear();

    for (int i = 0; i < map->width(); ++i)
        for (int j = 0; j < map->height(); ++j)
        {
            if (i == 0 || i == map->width() - 1 || j == 0 || j == map->height() - 1)
                map->setPixelColor(i, j, draw);
            else
                map->setPixelColor(i, j, back);
        }

    this->addPixmap(QPixmap::fromImage(*map));
}

void PaintScene::end_figure()
{
    if (points_vec.size() < 3)
        return;

    QPair<int, int> point_a = points_vec[points_vec.size() - 1];
    QPair<int, int> point_b = points_vec[0];
    draw_line(point_a.first, point_a.second, point_b.first, point_b.second);
    add_on_scene();
    points_vec.clear();
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    if (x < OFFSET || y < OFFSET || x > XSIZE + OFFSET || y > YSIZE + OFFSET)
        return;

    if (mode == DRAW_RECT)
    {
        points_vec.append(qMakePair(x, y));
        qDebug() << "Added point (" << QString::number(x) << ":" << QString::number(y) << ")";
        draw_edge();
    }
    else if (mode == DRAW_CURVE)
    {
        points_vec.append(qMakePair(x, y));
        qDebug() << "Added point (" << QString::number(x) << ":" << QString::number(y) << ")";
    }
    else
    {
        auto start = std::chrono::high_resolution_clock::now();
        algo_fill(x, y);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (mode == FILL)
            qDebug() << "Time of work is " << QString::number(duration.count()) << " ms";
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mode == DRAW_CURVE)
    {
        int x = event->scenePos().x();
        int y = event->scenePos().y();
        if (x < OFFSET || y < OFFSET || x > XSIZE + OFFSET || y > YSIZE + OFFSET)
            return;
        points_vec.append(qMakePair(x, y));
        qDebug() << "Added point (" << QString::number(x) << ":" << QString::number(y) << ")";
        draw_edge();
    }
}

void PaintScene::draw_edge()
{
    if (points_vec.size() > 1)
    {
        QPair<int, int> point_a = points_vec[points_vec.size() - 1];
        QPair<int, int> point_b = points_vec[points_vec.size() - 2];
        draw_line(point_a.first, point_a.second, point_b.first, point_b.second);
        add_on_scene();
    }
}

void PaintScene::draw_line(double x_start, double y_start, double x_end, double y_end)
{
    if (fabs(x_start - x_end) < EPS && fabs(y_start - y_end) < EPS)
        map->setPixelColor(round(x_start), round(y_start), draw);
    else
    {
        double dx = fabs(x_start - x_end), dy = fabs(y_start - y_end), x = x_start, y = y_start;
        double b = (dx >= dy) ? dx : dy;
        dx = (x_end - x_start) / b;
        dy = (y_end - y_start) / b;
        for (int i = 0; i < ceil(b); ++i)
        {
            map->setPixelColor(int(round(x)), int(round(y)), draw);
            x += dx;
            y += dy;
        }
    }
}

void PaintScene::add_on_scene()
{
    this->addPixmap(QPixmap::fromImage(*map));
}

void PaintScene::delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(DELAY);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void PaintScene::algo_fill(int x, int y)
{
    QStack<QPair<int, int>> stack;
    stack.push(qMakePair(x, y));
    while (!stack.empty())
    {
        QPair<int, int> pixel = stack.pop();
        x = pixel.first, y = pixel.second;
        map->setPixelColor(x, y, draw);
        int tmp_x = x, tmp_y = y;
        x += 1;
        while (map->pixelColor(x, y) == back)
        {
            map->setPixelColor(x, y, draw);
            ++x;
        }
        int right_x = x - 1;
        x = tmp_x - 1;
        while (map->pixelColor(x, y) == back)
        {
            map->setPixelColor(x, y, draw);
            --x;
        }
        int left_x = x + 1;
        x = left_x;
        y = tmp_y + 1;
        while (x <= right_x)
        {
            bool flag = 0;
            while (map->pixelColor(x, y) == back && x < right_x)
            {
                if (!flag)
                    flag = 1;
                x += 1;
            }

            if (flag)
            {
                if (x == right_x && map->pixelColor(x, y) == back)
                    stack.push(qMakePair(x, y));
                else
                    stack.push(qMakePair(x - 1, y));
            }

            int x_in = x;
            while (map->pixelColor(x, y) != back && x < right_x)
                x += 1;
            if (x == x_in)
                x += 1;
        }

        x = left_x;
        y = tmp_y - 1;
        while (x <= right_x)
        {
            bool flag = 0;
            while (map->pixelColor(x, y) == back && x < right_x)
            {
                if (!flag)
                    flag = 1;
                x += 1;
            }

            if (flag)
            {
                if (x == right_x && map->pixelColor(x, y) == back)
                    stack.push(qMakePair(x, y));
                else
                    stack.push(qMakePair(x - 1, y));
            }

            int x_in = x;
            while (map->pixelColor(x, y) != back && x < right_x)
                x += 1;
            if (x == x_in)
                x += 1;
        }

        if (mode == FILL_DELAY)
        {
            delay();
            add_on_scene();
        }
    }

    add_on_scene();
}

