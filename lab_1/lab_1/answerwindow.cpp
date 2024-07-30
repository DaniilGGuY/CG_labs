#include "answerwindow.h"
#include "ui_answerwindow.h"

#include <QPainter>
#include <QtMath>
#include <QMessageBox>
#include <QDebug>

AnswerWindow::AnswerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnswerWindow)
{
    ui->setupUi(this);
}

AnswerWindow::~AnswerWindow()
{
    delete ui;
}

void AnswerWindow::set_table(QTableWidget *table)
{
    for (int i = 0; i < table->rowCount(); ++i)
    {
        double cur_x = table->item(i, 0)->text().toFloat();
        double cur_y = table->item(i, 1)->text().toFloat();
        table_points.append(qMakePair(cur_x, cur_y));
    }
}

void AnswerWindow::find_ans()
{
    int n = table_points.size();
    double ab = 0.0, bc = 0.0, ac = 0.0, half_p = 0.0, s_triangle = 0.0, s_circle = 0.0, max_delta = 0.0, radius = 0.0;
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            for (int k = j + 1; k < n; ++k)
            {
                ab = sqrt(pow((table_points[i].first - table_points[j].first), 2) + \
                          pow((table_points[i].second - table_points[j].second), 2));

                bc = sqrt(pow((table_points[k].first - table_points[j].first), 2) + \
                          pow((table_points[k].second - table_points[j].second), 2));

                ac = sqrt(pow((table_points[i].first - table_points[k].first), 2) + \
                          pow((table_points[i].second - table_points[k].second), 2));

                if (abs(ac - ab - bc) < EPS || abs(bc - ac - ab) < EPS || abs(ab - ac - bc) < EPS)
                    continue;

                half_p = (ab + bc + ac) / 2;

                s_triangle = sqrt(half_p * (half_p - ab) * (half_p - bc) * (half_p - ac));

                radius = (ab * bc * ac) / (4 * s_triangle);

                s_circle = PI * radius * radius;

                if (max_delta < abs(s_circle - s_triangle))
                {
                    max_delta = abs(s_circle - s_triangle);
                    a = i, b = j, c = k;
                }
            }
        }
    }

    if (a != b && b != a && c != b)
    {
        answer_points.append(table_points[a]);
        answer_points.append(table_points[b]);
        answer_points.append(table_points[c]);
        ui->label->setText("Площадь круга: " + QString::number(s_circle) + \
                           "\nПлощадь треугольника: " + QString::number(s_triangle) + \
                           "\nРазность площадей равна: " + QString::number(s_circle - s_triangle));
    }
    else
    {
        close();
        QMessageBox::warning(this, "Предупреждение", "Вырожденный случай");
    }
}

QPair<double, double> AnswerWindow::calc_center_circle()
{
    double x1_ = (answer_points[0].first + answer_points[1].first) / 2;
    double y1_ = (answer_points[0].second + answer_points[1].second) / 2;
    double a1 = answer_points[1].first - answer_points[0].first;
    double b1 = answer_points[1].second - answer_points[0].second;
    double c1 = x1_ * (-a1) + y1_ * (-b1);

    double x2_ = (answer_points[2].first + answer_points[1].first) / 2;
    double y2_ = (answer_points[2].second + answer_points[1].second) / 2;
    double a2 = answer_points[2].first - answer_points[1].first;
    double b2 = answer_points[2].second - answer_points[1].second;
    double c2 = x2_ * (-a2) + y2_ * (-b2);

    double x_res, y_res;

    if (a1 == 0)
    {
        y_res = (-c1) / b1;
        x_res = (c1 * b2 / b1 - c2) / a2;
    }
    else if (a2 == 0)
    {
        y_res = (-c2) / b2;
        x_res = (c2 * b1 / b2 - c1) / a1;
    }
    else
    {
        y_res = (c2 / a2 - c1 / a1) / (b1 / a1 - b2 / a2);
        x_res = (-c1 - b1 * y_res) / a1;
    }

    return qMakePair(x_res, y_res);
}

void AnswerWindow::drawAxis(QPainter *painter)
{
    painter->setPen(QPen(Qt::gray, 2));

    for (int i = 40, t = 20; i <= 600; i += t) {
        for (int j = 40; j <= 600; j += 4) {
            painter->drawPoint(QPoint(i, j));
            painter->drawPoint(QPoint(j, i));
        }
    }
}

void AnswerWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    drawAxis(&painter);

    QPair<double, double> centr = calc_center_circle();
    double x_cent = centr.first, y_cent = centr.second;
    double radius = sqrt(pow(x_cent - answer_points[0].first, 2) + pow(y_cent - answer_points[0].second, 2));
    double top_right = (x_cent > y_cent ? x_cent : y_cent) + radius;
    double bottom_left = (x_cent > y_cent ? y_cent : x_cent) - radius;

    double x_1 = answer_points[0].first, y_1 = answer_points[0].second;
    double x_2 = answer_points[1].first, y_2 = answer_points[1].second;
    double x_3 = answer_points[2].first, y_3 = answer_points[2].second;
    double masht = 560 / (top_right - bottom_left);
    painter.setPen(QPen(Qt::blue, 2));
    painter.drawEllipse(QPointF((x_cent - (top_right + bottom_left) / 2) * masht + 320, \
                               (640 - ((y_cent  - (top_right + bottom_left) / 2) * masht + 320))), \
                        radius * masht, radius * masht);
    QPolygon pol;
    pol << QPoint((x_1 - (top_right + bottom_left) / 2) * masht + 320, \
                  (640 - ((y_1  - (top_right + bottom_left) / 2) * masht + 320))) << \
           QPoint((x_2 - (top_right + bottom_left) / 2) * masht + 320, \
                  (640 - ((y_2  - (top_right + bottom_left) / 2) * masht + 320))) << \
           QPoint((x_3 - (top_right + bottom_left) / 2) * masht + 320, \
                  (640 - ((y_3  - (top_right + bottom_left) / 2) * masht + 320)));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawPolygon(pol);

    for (int i = 0; i < answer_points.size(); ++i)
    {
        double cur_x = answer_points[i].first;
        double cur_y = answer_points[i].second;
        painter.setPen(QPen(Qt::red, 4));
        painter.drawPoint(QPoint((cur_x - (top_right + bottom_left) / 2) * masht + 320, \
                                 (640 - ((cur_y  - (top_right + bottom_left) / 2) * masht + 320))));
        painter.setFont(QFont("Times", 10));
        painter.setPen(QPen(Qt::black));
        painter.drawText(QPoint((cur_x - (top_right + bottom_left) / 2) * masht + 322, \
                               (640 - ((cur_y  - (top_right + bottom_left) / 2) * masht + 322))), \
                        "(" + QString::number(cur_x) + ";" + QString::number(cur_y) + ")");
    }
}
