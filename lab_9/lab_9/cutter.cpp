#include "cutter.h"

// Векторное произведение с помощью определителя
int vectMult(QPair<int, int> V1, QPair<int, int> V2)
{
    return V1.first * V2.second - V1.second * V2.first;
}

// Скалярное произведение векторов
int scalarMult(QPair<int, int> V1, QPair<int, int> V2)
{
    return V1.first * V2.first + V1.second * V2.second;
}

// Проверка на выпуклость
bool checkConvexity(QVector<QPair<int, int>> &polygon)
{
    if (polygon.size() < 3)
        return 1;

    polygon.push_back(polygon[0]);
    QPair<int, int> V1 = qMakePair(polygon[1].first - polygon[0].first, polygon[1].second - polygon[0].second);
    QPair<int, int> V2 = qMakePair(polygon[2].first - polygon[1].first, polygon[2].second - polygon[1].second);
    bool clockwise = vectMult(V1, V2) < 0;
    for (int i = 3; i < polygon.size(); ++i)
    {
        QPair<int, int> V1 = qMakePair(polygon[i - 1].first - polygon[i - 2].first, polygon[i - 1].second - polygon[i - 2].second);
        QPair<int, int> V2 = qMakePair(polygon[i].first - polygon[i - 1].first, polygon[i].second - polygon[i - 1].second);
        int vect = vectMult(V1, V2);
        if ((clockwise && vect >= 0) || (!clockwise && vect < 0))
            return 0;
    }

    if (clockwise) // Если направление задание по часовой, заменяем на направление против часовой (для удобства)
        for (int i = 0; i < polygon.size() / 2; ++i)
        {
            QPair<int, int> tmp = polygon[i];
            polygon[i] = polygon[polygon.size() - 1 - i];
            polygon[polygon.size() - 1 - i] = tmp;
        }

    return 1;
}

// Проверка видимости точки point относительно вектора P1P2 (с помощью векторного произведения)
int checkPointVisibility(QPair<int, int> point, QPair<int, int> P1, QPair<int, int> P2)
{
    QPair<int, int> V1 = qMakePair(P2.first - P1.first, P2.second - P1.second);
    QPair<int, int> V2 = qMakePair(point.first - P1.first, point.second - P1.second);
    return vectMult(V1, V2);
}

// Проверка того, что прямые P1P2 и W1W2 пересекаются
bool isCross(QPair<int, int> P1, QPair<int, int> P2, QPair<int, int> W1, QPair<int, int> W2)
{
    int P1_visibility = checkPointVisibility(P1, W1, W2);
    int P2_visibility = checkPointVisibility(P2, W1, W2);

    if ((P1_visibility < 0 && P2_visibility > 0) || (P1_visibility > 0 && P2_visibility < 0))
        return 1;
    return 0;
}

// Функция, вычисляющая точку пересечения двух прямых P1P2 и W1W2
QPair<int, int> calcCross(QPair<int, int> P1, QPair<int, int> P2, QPair<int, int> W1, QPair<int, int> W2)
{
    QPair<int, int> D = qMakePair(P2.first - P1.first, P2.second - P1.second);
    QPair<int, int> Pn = qMakePair(W2.second - W1.second, W1.first - W2.first);
    QPair<int, int> W = qMakePair(P1.first - W1.first, P1.second - W1.second);

    int Wsk = scalarMult(W, Pn);
    int Dsk = scalarMult(D, Pn);
    double t = -(double)Wsk / Dsk;

    return qMakePair(P1.first + (P2.first - P1.first) * t, P1.second + (P2.second - P1.second) * t);
}

QVector<QPair<int, int>> cutSazerlandHodgman(QVector<QPair<int, int>> cutter, QVector<QPair<int, int>> polygon)
{
    if (cutter.size() < 3 || polygon.size() < 2)
        return {};

    // Проерка на выпуклость
    if (!checkConvexity(cutter))
        return {};

    for (int i = 0; i < cutter.size() - 1; ++i)  // Цикл по ребрам отсекателя
    {
        QVector<QPair<int, int>> answer;   // Промежуточная фигура
        QPair<int, int> first, prev;  // Первая точка и точка, которая была на предыдущей итерации
        for (int j = 0; j < polygon.size(); ++j)  // Цикл по ребрам фигуры
        {
            if (j != 0)  // Если не первая вершина
            {
                if (isCross(prev, polygon[j], cutter[i], cutter[i + 1]))  // Если текущее ребро полигона и текущее ребро кона пересекаются
                    answer.append(calcCross(prev, polygon[j], cutter[i], cutter[i + 1]));  // То запоминаем точку пересечения
            }
            else
                first = polygon[j];  // Запоминаем первую вершину для отдельной обработки

            prev = polygon[j];  // Обновим значение предыдущей точки
            if (checkPointVisibility(prev, cutter[i], cutter[i + 1]) >= 0)  // Проверим, что предыдущая (и одновеременно нынешняя) точка видима
                answer.append(prev);  // Если так, то запомиинаем ее
        }

        if (answer.size() != 0)  // Условный оператор для отдельной обработки ребра PnP1
        {
            if (isCross(prev, first, cutter[i], cutter[i + 1]))
                answer.append(calcCross(prev, first, cutter[i], cutter[i + 1]));
        }

        polygon = answer;  // Обязательно сохраняем промежуточную фигуру в текущий полигон (отсекли относительно i-ой стороны)
    }

    return polygon;
}
