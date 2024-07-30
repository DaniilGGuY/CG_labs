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

void PaintScene::readdPicture()
{
    clear();
    setBackgroundBrush(back);
    cutExecution();
}

void PaintScene::endInput()
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
        QVector<QPair<int, int>> polygon = cutter_vertex_vec;
        if (!checkConvexity(polygon))
            cutter_vertex_vec.pop_back();
    }
    else if (mode == DRAW_FIGURE)
    {
        if (!begin_input)
        {
            polynom_vertex_vec.clear();
            begin_input = true;
        }

        polynom_vertex_vec.append(qMakePair(x, y));
    }

    readdPicture();
}

void PaintScene::redrawFigure()
{
    QPolygon draw_pol;
    for (int i = 0; i < polynom_vertex_vec.size(); ++i)
        draw_pol << QPoint(polynom_vertex_vec[i].first, polynom_vertex_vec[i].second);
    addPolygon(draw_pol, draw);
}

void PaintScene::clearPointsVec()
{
    polynom_vertex_vec.clear();
    cutter_vertex_vec.clear();
}

void PaintScene::drawCutter()
{
    QPolygon pol;
    for (int i = 0; i < cutter_vertex_vec.size(); ++i)
        pol << QPoint(cutter_vertex_vec[i].first, cutter_vertex_vec[i].second);
    addPolygon(pol, cutter);
}

void PaintScene::cutExecution()
{
    redrawFigure();
    drawCutter();

    QPolygon pol1, pol2;
    QVector<QPair<int, int>> answer_vertex_vec = cutSazerlandHodgman(cutter_vertex_vec, polynom_vertex_vec);
    for (int i = 0; i < answer_vertex_vec.size(); ++i)
    {
        pol1 << QPoint(answer_vertex_vec[i].first, answer_vertex_vec[i].second);
        pol2 << QPoint(answer_vertex_vec[i].first + 1, answer_vertex_vec[i].second + 1);
    }
    addPolygon(pol1, back, back);
    addPolygon(pol2, back, back);
    addPolygon(pol1, answer);
}
