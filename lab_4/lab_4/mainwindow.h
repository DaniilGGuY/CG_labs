#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timescompare.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define REPS              50
#define STEP            2000
#define RADIUS          2000
#define END_RADIUS     10000

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawCircleByAlg(double x_cent, double y_cent, double radius, QColor back, QColor fore);
    void drawEllipsByAlg(double x_cent, double y_cent, double a, double b, QColor back, QColor fore);
    void drawCircleSpecterByAlg(double x_cent, double y_cent, double radius, double step, int count, QColor back, QColor fore);
    void drawEllipsSpecterByAlg(double x_cent, double y_cent, double a, double b, double step, int count, QColor back, QColor fore);
    void calcTimes(QVector<QVector<double>> &arr);

private slots:
    void on_DrawCircleButton_clicked();

    void on_DrawEllipsButton_clicked();

    void on_CleareSceneButton_clicked();

    void on_DrawSpectrCircleButton_clicked();

    void on_DrawSpectrEllipsButton_clicked();

    void on_CleareSceneButton_2_clicked();

private:
    Ui::MainWindow *ui;
    TimesCompare *times_comp;
    QImage *map;
};
#endif // MAINWINDOW_H
