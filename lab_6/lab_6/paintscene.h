#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QStack>
#include <QTime>
#include <QCoreApplication>

#define EPS   1e-8

#define XSIZE         620
#define YSIZE         580
#define OFFSET         10
#define DELAY          10

enum Mode
{
    DRAW_RECT = 1,
    DRAW_CURVE,
    FILL,
    FILL_DELAY,
};

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();
    void set_back(QColor back);
    void set_draw(QColor draw);
    void set_mode(Mode mode);
    void add_point_handle(int x, int y);
    void clear_points_vec();
    void delete_draw();
    void end_figure();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void draw_edge();
    void draw_line(double x_start, double y_start, double x_end, double y_end);
    void add_on_scene();
    void algo_fill(int x, int y);
    void fill();
    void delay();

private:
    QVector<QPair<int, int>> points_vec;
    QImage *map;
    QColor back;
    QColor draw;
    Mode mode = DRAW_RECT;
};

#endif // PAINTSCENE_H
