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
    void setArray(QVector<double> arr);
    void drawHist();

private:
    Ui::TimesCompare *ui;
    QCustomPlot *customPlot;
    QVector<double> arr;
};

#endif // TIMESCOMPARE_H
