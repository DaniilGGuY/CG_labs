#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QStack>
#include <QTime>
#include <QCoreApplication>

#include "cutter.h"

#define XSIZE         600
#define YSIZE         600
#define OFFSET         10

enum Mode
{
    DRAW_FIGURE = 1,
    DRAW_CUTTER
};

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();
    void setBack(QColor back);
    void setDraw(QColor draw);
    void setCutter(QColor cutter);
    void setAnswer(QColor answer);
    void setMode(Mode mode);
    void deleteDraw();
    void readdPicture();
    void endInput();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void redrawFigure();
    void clearPointsVec();
    void drawCutter();
    void cutExecution();

private:
    QVector<QPair<int, int>> polynom_vertex_vec;
    QVector<QPair<int, int>> cutter_vertex_vec;
    QColor back = Qt::white;
    QColor draw = Qt::black;
    QColor cutter = Qt::blue;
    QColor answer = Qt::red;
    Mode mode = DRAW_FIGURE;
    bool begin_input = false;
};

#endif // PAINTSCENE_H
