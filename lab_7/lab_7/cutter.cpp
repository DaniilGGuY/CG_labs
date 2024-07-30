#include "cutter.h"

int calcTCode(Cutter cut, QPair<int, int> point)
{
    int code = (point.second < cut.y0);
    code = (code << 1) + (point.second > cut.y1);
    code = (code << 1) + (point.first > cut.x1);
    code = (code << 1) + (point.first < cut.x0);
    return code;
}

Segment segByPoints(QPair<double, double> P1, QPair<double, double> P2)
{
    Segment seg;
    seg.x0 = round(P1.first);
    seg.y0 = round(P1.second);
    seg.x1 = round(P2.first);
    seg.y1 = round(P2.second);
    return seg;
}

Segment cutByMiddlePoint(Cutter cut, Segment seg)
{
    QPair<double, double> P1 = qMakePair(seg.x0, seg.y0);
    QPair<double, double> P2 = qMakePair(seg.x1, seg.y1);
    int i = 1;
    while (true)
    {
        // Вычисление T кодов для точек (4-битный код, отвечающий за расположение точки относительно отсекателя)
        int T1 = calcTCode(cut, P1), T2 = calcTCode(cut, P2);
        // Если точка полностью видима, возвращаем исходный отрезок
        if (T1 == 0 && T2 == 0)
            return seg;

        // Если точко тривиально не видима, возвращаем некорректное значение
        if ((T1 & T2) != 0)
            return { -1, -1, -1, -1 };

        // Запоминаем точку P1, она нам еще пригодится
        QPair<double, double> R = P1;
        // Условие, если мы 2 раза выполнили бинарный поиск, то есть нашли два пересечения отрезка с отсекателем
        // или два раза отрезок выродился в точку
        if (i > 2)
        {
            if ((T1 & T2) != 0)
                return { -1, -1, -1, -1 };
            return segByPoints(P1, P2);
        }

        // Если вторая точка видима или если мы нашли первое пересечение с коном, меняем точки местами и ищем второе пересечение
        if (T2 == 0)
        {
            P1 = P2;
            P2 = R;
            ++i;
            continue;
        }
        // Бинарный поиск, который ищет наиболее удаленную видимую точку, считая от точки P1
        while (fabs(P1.first - P2.first) > EPS || fabs(P1.second - P2.second) > EPS)
        {
            QPair<double, double> Pm;
            Pm.first = (P1.first + P2.first) / 2;
            Pm.second = (P1.second + P2.second) / 2;

            QPair<double, double> P = P1;
            P1 = Pm;
            T1 = calcTCode(cut, P1);
            if ((T1 & T2) != 0)
            {
                P1 = P;
                P2 = Pm;
            }
        }

        // Меняем P1 и P2 местами, потому что для точки P1 мы нашли наиболее удаленную видимую точку
        P1 = P2;
        P2 = R;
        ++i;
    }

    return { -1, -1, -1, -1 };
}
