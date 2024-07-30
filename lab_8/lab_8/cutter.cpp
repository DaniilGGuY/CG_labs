#include "cutter.h"

Direction checkDirection(QVector<QPair<int, int>> polygon)
{
    if (polygon.size() < 3)
        return ERR;

    // Берем три точки
    QPair<int, int> P1 = polygon[0];
    QPair<int, int> P2 = polygon[1];
    QPair<int, int> P3 = polygon[2];
    // Строим вектора P1P2, P2P3
    QPair<int, int> V1 = qMakePair(P2.first - P1.first, P2.second - P1.second);
    QPair<int, int> V2 = qMakePair(P3.first - P2.first, P3.second - P2.second);
    // Если векторное произведение векторов меньше нуля, то многоугольник задается по часовой стрелке
    if (V1.first * V2.second - V1.second * V2.first < 0)
        return CLOCKWISE;
    return COUNTERCLOCKWISE;
}

int scalarMult(QPair<int, int> a, QPair<int, int> b)
{
    return a.first * b.first + a.second * b.second;
}

Segment cutByCirusBek(QVector<QPair<int, int>> cutter, Segment seg)
{
    QPair<int, int> P1 = qMakePair(seg.x0, seg.y0);
    QPair<int, int> P2 = qMakePair(seg.x1, seg.y1);
    // Направляющий вектор нашего отрезка
    QPair<int, int> D = qMakePair(P2.first - P1.first, P2.second - P1.second);
    // Переменные, которые отвечают за точку пересечения отрезка с коном (из параметрического уравнения)
    // Изначально считаем, что отрезок P1P2 полностью видимый и точки лежит на границах кона, поэтому t0 = 0, t1 = 1
    double t0 = 0, t1 = 1, t;
    // Определяем направление задания выпуклого многоугольника (по часовой или против часовой)
    Direction dir = checkDirection(cutter);
    for (int i = 0; i < cutter.size(); ++i)
    {
        // Вычисляем вектор нормали в зависимости от направления задания выпуклого многоугольника
        QPair<int, int> Pn;
        if (i == cutter.size() - 1)
        {
            if (dir == COUNTERCLOCKWISE)
                Pn = qMakePair(cutter[i].second - cutter[0].second, cutter[0].first - cutter[i].first);
            else
                Pn = qMakePair(cutter[0].second - cutter[i].second, cutter[i].first - cutter[0].first);
        }
        else
        {
            if (dir == COUNTERCLOCKWISE)
                Pn = qMakePair(cutter[i].second - cutter[i + 1].second, cutter[i + 1].first - cutter[i].first);
            else
                Pn = qMakePair(cutter[i + 1].second - cutter[i].second, cutter[i].first - cutter[i + 1].first);
        }

        // W - вектор, который исходит из точки на текущем ребре и заканчивается в произвольной точке отрезка
        // для вектора W возьмем одну точку P1, как точку на отрезке и первую точку ребра многоугольника
        QPair<int, int> W = qMakePair(P1.first - cutter[i].first, P1.second - cutter[i].second);
        // Wsk и Dsk - скалярные произведения векторов W и D с вектором нормали
        // Скалярные произведения позволят определить расположение отрезка относительно очередного ребра отсекателя
        int Wsk = scalarMult(W, Pn), Dsk = scalarMult(D, Pn);
        // Если Dsk == 0, то наш отрезок либо вырожден (точка), либо параллелен ребру
        if (Dsk == 0)
        {
            // Если Wsk меньше нуля, то угол между вектором нормали и вектором W больше 90 градусов
            // а поскольку наш отсекатель - выпуклый многоугольник, это значит, что точка P1 лежит вне кона
            // то есть и весь отрезок лежит вне кона
            if (Wsk < 0)
                return { -1, -1, -1, -1 };
            else
                continue;
        }

        // Обновляем переменную t из параметрического уравнения
        // Эта переменная поможет определить точку пересечения отрезка с текущим ребром кона
        t = -(double)Wsk / Dsk;

        // Два случая, когда направляющий вектор направлен от точки пересечения ребра и отрезка и когда наоборот
        if (Dsk > 0) // От точки пересечения
        {
            // Если t больше единицы, значит наш отрезок невидим, ибо точка пересечения отрезка с ребром находится за точкой P2,
            // а в силу того, что отсекатель выпуклый получается, что и весь отрезок лежит вне отсекателя
            if (t > 1)
                return { -1, -1, -1, -1 };
            else
                t0 = std::max(t0, t); // Вычисляем значение параметра t0 - нижняя граница
        }
        else  // К точке пересечения
        {
            // Если t меньше нуля, значит наш отрезок невидим, ибо точка пересечения с ребром лежит перед точкой P1, а в силу
            // того, что отсекатель выпуклый получается, что и весь отрезок лежит вне отсекателя
            if (t < 0)
                return { -1, -1, -1, -1 };
            else
                t1 = std::min(t1, t); // Вычисляем новое значение параметра t1 - верхняя граница
        }
    }

    // Отрезок частично видим или видим полностью, если t0 <= t1
    if (t0 <= t1)
        return { int(std::round(P1.first + (P2.first - P1.first) * t1)),
                 int(std::round(P1.second + (P2.second - P1.second) * t1)),
                 int(std::round(P1.first + (P2.first - P1.first) * t0)),
                 int(std::round(P1.second + (P2.second - P1.second) * t0)) };

    return { -1, -1, -1, -1 };
}
