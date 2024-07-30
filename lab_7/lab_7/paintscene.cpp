#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent) { }

PaintScene::~PaintScene() {}

void PaintScene::setBack(QColor back) { this->back = back; }

void PaintScene::setDraw(QColor draw) { this->draw = draw; }

void PaintScene::setCutter(QColor cutter) { this->cutter = cutter; }

void PaintScene::setAnswer(QColor answer) { this->answer = answer; }

void PaintScene::setMode(Mode mode) { this->mode = mode; }

void PaintScene::deleteDraw()
{
    segments_vec.clear();
    readdSegments();
    begin_input = false;
}

void PaintScene::readdSegments()
{
    clear();
    setBackgroundBrush(back);
    redrawSegments();
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();

    if (mode == DRAW_RECT)
    {
        if (!begin_input)
        {
            cut.x0 = x;
            cut.y0 = y;
        }
        else
        {
            cut.x1 = x;
            cut.y1 = y;
            readdSegments();
            drawCutter();
            cutExecution();
        }
    }
    else if (mode == DRAW_FIGURE)
    {
        if (!begin_input)
        {
            Segment new_seg;
            new_seg.x0 = x;
            new_seg.y0 = y;
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
    }

    begin_input = 1 - begin_input;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();

    if (mode == DRAW_RECT)
    {
        cut.x1 = x;
        cut.y1 = y;
        readdSegments();
        drawCutter();
        cutExecution();
    }
    else if (mode == DRAW_FIGURE)
    {
        segments_vec[segments_vec.size() - 1].x1 = x;
        segments_vec[segments_vec.size() - 1].y1 = y;
        clear();
        redrawSegments();
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

void PaintScene::clearPointsVec() { segments_vec.clear(); }

void PaintScene::drawCutter()
{
    int x0 = std::min(cut.x0, cut.x1), y0 = std::min(cut.y0, cut.y1);
    int x1 = std::max(cut.x0, cut.x1), y1 = std::max(cut.y0, cut.y1);

    addRect(x0, y0, x1 - x0, y1 - y0, back, back);
    addLine(x0, y0, x0, y1, cutter);
    addLine(x0, y0, x1, y0, cutter);
    addLine(x1, y1, x0, y1, cutter);
    addLine(x1, y1, x1, y0, cutter);
}

void PaintScene::cutExecution()
{
    Cutter correct_cut = cut;
    if (correct_cut.x1 < correct_cut.x0)
        std::swap(correct_cut.x1, correct_cut.x0);

    if (correct_cut.y1 < correct_cut.y0)
        std::swap(correct_cut.y1, correct_cut.y0);

    for (int i = 0; i < segments_vec.size(); ++i)
    {
        Segment cutted_seg = cutByMiddlePoint(correct_cut, segments_vec[i]);
        if (cutted_seg.x0 != -1)
            addLine(cutted_seg.x0, cutted_seg.y0, cutted_seg.x1, cutted_seg.y1, answer);
    }
}
