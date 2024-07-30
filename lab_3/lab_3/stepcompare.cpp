#include "stepcompare.h"
#include "ui_stepcompare.h"

StepCompare::StepCompare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StepCompare)
{
    ui->setupUi(this);
}

StepCompare::~StepCompare()
{
    delete ui;
}

void StepCompare::setArray(QVector<int> arr)
{
    for (int i = 0; i < arr.size(); ++i)
        this->arr.append(arr[i]);
}

void StepCompare::drawGraph(QString name_alg)
{
    this->setWindowTitle(name_alg);
    customPlot = new QCustomPlot;
    ui->gridLayout->addWidget(customPlot, 1, 0, 1, 1);
    QVector<double> x;
    for (int i = 0; i < 180; i += 5)
      x.append(i);

    customPlot->addGraph();
    customPlot->graph(0)->setData(x, arr);
    customPlot->xAxis->setLabel("Угол в градусах");
    customPlot->yAxis->setLabel("Количество ступенек при длине 250");
    customPlot->xAxis->setRange(0, 181);
    customPlot->yAxis->setRange(0, 251);
    customPlot->replot();
}
