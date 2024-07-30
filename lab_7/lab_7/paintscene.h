#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QStack>
#include <QTime>
#include <QCoreApplication>

#include "special_utility.h"
#include "cutter.h"

#define XSIZE         600
#define YSIZE         600
#define OFFSET         10

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
    void readdSegments();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void redrawSegments();
    void clearPointsVec();
    void drawCutter();
    void cutExecution();

private:
    QVector<Segment> segments_vec;
    Cutter cut;
    QColor back = Qt::white;
    QColor draw = Qt::black;
    QColor cutter = Qt::blue;
    QColor answer = Qt::red;
    Mode mode = DRAW_FIGURE;
    bool begin_input = false;
};

#endif // PAINTSCENE_H
