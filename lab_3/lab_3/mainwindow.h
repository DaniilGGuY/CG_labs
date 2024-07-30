#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "timescompare.h"
#include "stepcompare.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define REPS          1000
#define TIME_POINT    1000

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawLineByAlg(double x_start, double y_start, double x_end, double y_end, double max_intense, QColor back, QColor fore);
    void drawSpectrByAlg(double angle, double max_intense, QColor back, QColor fore);
    void calcTimes(QVector<double> &arr);
    void calcSteps(QVector<int> &arr);

private slots:
    void on_SegmentDrawButton_clicked();

    void on_SpectrDrawButton_clicked();

    void on_CleareSceneButton_clicked();

    void on_CompareTimeButton_clicked();

    void on_CompareSmoothButton_clicked();

private:
    Ui::MainWindow *ui;
    TimesCompare *times_comp;
    StepCompare *step_comp;
};
#endif // MAINWINDOW_H
