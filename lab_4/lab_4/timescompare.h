#ifndef TIMESCOMPARE_H
#define TIMESCOMPARE_H

#include <QDialog>

#include "qcustomplot.h"

namespace Ui {
class TimesCompare;
}

class TimesCompare : public QDialog
{
    Q_OBJECT

public:
    explicit TimesCompare(QWidget *parent = nullptr);
    ~TimesCompare();
    void setArray(QVector<QVector<double>> arr);
    void drawGraph(int radius, int step, int end_radius);

private:
    Ui::TimesCompare *ui;
    QCustomPlot *customPlot;
    QVector<QVector<double>> arr;
};

#endif // TIMESCOMPARE_H
