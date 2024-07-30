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

void TimesCompare::setArray(QVector<double> arr)
{
    for (int i = 0; i < arr.size(); ++i)
        this->arr.append(arr[i]);
}

void TimesCompare::drawHist()
{
    customPlot = new QCustomPlot;
    ui->gridLayout->addWidget(customPlot, 1, 0, 1, 1);
    QCPAxis *keyAxis = customPlot->xAxis;
    QCPAxis *valueAxis = customPlot->yAxis;
    QCPBars *hist = new QCPBars(keyAxis, valueAxis);

    hist->setAntialiased(false);
    hist->setName("Исследование времени работы для 1000 пикселей (мс)");
    hist->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    hist->setBrush (QColor(0, 168, 140));

    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5;
    labels << "ДДА" << "Брезенхем (float)" << "Брезенхем (int)" << "Брезенхем (smooth)" << "Ву";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);

    keyAxis->setTicker(textTicker);
    keyAxis->setTickLabelRotation(60);
    keyAxis->setSubTicks(false);
    keyAxis->setRange(0, 6);

    valueAxis->setRange(0, this->arr[4] * 1.1);
    valueAxis->setLabel("Время");

    hist->setData(ticks, this->arr);
    customPlot->replot();
}
