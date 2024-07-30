#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent) { }

PaintScene::~PaintScene() {}

void PaintScene::setBack(QColor back) { this->back = back; }

void PaintScene::setDraw(QColor draw) { this->draw = draw; }

void PaintScene::setCutter(QColor cutter) { this->cutter = cutter; }

void PaintScene::setAnswer(QColor answer) { this->answer = answer; }

void PaintScene::setMode(Mode mode)
{
    this->mode = mode;
    begin_input = false;
}

void PaintScene::deleteDraw()
{
    clear();
    clearPointsVec();
    begin_input = false;
}

void PaintScene::readdSegments()
{
    clear();
    setBackgroundBrush(back);
    redrawSegments();
    drawCutter();
}

void PaintScene::endCutterInput()
{
    begin_input = false;
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();

    if (mode == DRAW_CUTTER)
    {
        if (!begin_input)
        {
            cutter_vertex_vec.clear();
            begin_input = true;
        }

        cutter_vertex_vec.append(qMakePair(x, y));
        readdSegments();
    }
    else if (mode == DRAW_FIGURE)
    {
        if (!begin_input)
        {
            Segment new_seg;
            new_seg.x0 = x;
            new_seg.y0 = y;
            new_seg.x1 = x;
            new_seg.y1 = y;
            segments_vec.append(new_seg);
        }
        else
        {
            Segment now_seg = segments_vec[segments_vec.size() - 1];
            now_seg.x1 = x;
            now_seg.y1 = y;
            addLine(now_seg.x0, now_seg.y0, now_seg.x1, now_seg.y1, draw);
            segments_vec[segments_vec.size() - 1] = now_seg;
        }

        drawCutter();
        begin_input = 1 - begin_input;
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();

    if (mode == DRAW_FIGURE)
    {
        segments_vec[segments_vec.size() - 1].x1 = x;
        segments_vec[segments_vec.size() - 1].y1 = y;
        clear();
        redrawSegments();
        drawCutter();
    }

    begin_input = false;
}

void PaintScene::redrawSegments()
{
    for (int i = 0; i < segments_vec.size(); ++i)
    {
        Segment now_seg = segments_vec[i];
        addLine(now_seg.x0, now_seg.y0, now_seg.x1, now_seg.y1, draw);
    }
}

void PaintScene::clearPointsVec()
{
    segments_vec.clear();
    cutter_vertex_vec.clear();
}

void PaintScene::drawCutter()
{
    if (cutter_vertex_vec.size() > 1)
    {
        QPolygon pol;
        for (int i = 0; i < cutter_vertex_vec.size(); ++i)
            pol << QPoint(cutter_vertex_vec[i].first, cutter_vertex_vec[i].second);
        addPolygon(pol, back, back);

        for (int i = 1; i < cutter_vertex_vec.size(); ++i)
        {
            QPair<int, int> P1 = cutter_vertex_vec[i - 1];
            QPair<int, int> P2 = cutter_vertex_vec[i];
            addLine(P1.first, P1.second, P2.first, P2.second, cutter);
        }

        QPair<int, int> P1 = cutter_vertex_vec[0];
        QPair<int, int> P2 = cutter_vertex_vec[cutter_vertex_vec.size() - 1];
        addLine(P1.first, P1.second, P2.first, P2.second, cutter);
        cutExecution();
    }
}

void PaintScene::cutExecution()
{
    for (int i = 0; i < segments_vec.size(); ++i)
    {
        Segment cutted_seg = cutByCirusBek(cutter_vertex_vec, segments_vec[i]);
        if (cutted_seg.x0 != -1)
            addLine(cutted_seg.x0, cutted_seg.y0, cutted_seg.x1, cutted_seg.y1, answer);
    }
}
