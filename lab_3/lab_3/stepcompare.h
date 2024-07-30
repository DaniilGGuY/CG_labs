#ifndef STEPCOMPARE_H
#define STEPCOMPARE_H

#include <QDialog>

#include "qcustomplot.h"

namespace Ui {
class StepCompare;
}

class StepCompare : public QDialog
{
    Q_OBJECT

public:
    explicit StepCompare(QWidget *parent = nullptr);
    ~StepCompare();
    void setArray(QVector<int> arr);
    void drawGraph(QString name_alg);

private:
    Ui::StepCompare *ui;
    QCustomPlot *customPlot;
    QVector<double> arr;
};

#endif // STEPCOMPARE_H
