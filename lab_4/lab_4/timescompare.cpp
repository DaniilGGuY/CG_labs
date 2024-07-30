#include "timescompare.h"
#include "ui_timescompare.h"

TimesCompare::TimesCompare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimesCompare)
{
    ui->setupUi(this);
    this->setWindowTitle("Сравнение времени выполнения разных алгоритмов построения");
}

TimesCompare::~TimesCompare()
{
    delete ui;
}

void TimesCompare::setArray(QVector<QVector<double>> arr)
{
    for (int i = 0; i < arr[0].size(); ++i)
        this->arr.append(QVector<double> (arr.size(), 0));

    for (int i = 0; i < arr.size(); ++i)
        for (int j = 0; j < arr[i].size(); ++j)
            this->arr[j][i] = arr[i][j];
}

void TimesCompare::drawGraph(int radius, int step, int end_radius)
{
    customPlot = new QCustomPlot;
    ui->gridLayout->addWidget(customPlot, 1, 0, 1, 1);

    QVector<double> x;
    for (int i = radius; i <= end_radius; i += step)
        x.append(i);

    QVector<QString> names = { "Каноническое", "Параметрическое", "Брезенхем", "Средняя точка", "Стандартная ф-ия" };
    QVector<QColor> colors = { Qt::red, Qt::blue, Qt::black, Qt::green, Qt::magenta };

    customPlot->xAxis->setLabel("Радиус окружности");
    customPlot->yAxis->setLabel("Время работы, мс");
    customPlot->xAxis->setRange(radius, end_radius);
    customPlot->yAxis->setRange(-0.1, end_radius / 1000);
    for (int i = 0; i < 5; ++i)
    {
        customPlot->addGraph(customPlot->xAxis, customPlot->yAxis);
        customPlot->graph(i)->setName(names[i]);
        customPlot->graph(i)->setPen(QPen(colors[i]));
        customPlot->graph(i)->setData(x, arr[i]);
    }

    customPlot->legend->setVisible(true);
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));
    customPlot->replot();
}
