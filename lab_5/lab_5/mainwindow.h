#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QColor>
#include <QVector>
#include <QTime>

#define XSIZE         610
#define YSIZE         570
#define OFFSET         10
#define DELAY           3
#define WITHDELAY       1
#define WITHOUTDELAY    0

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);

    void drawPolygon();

    void calcMatPixels(int x1, int y1, int x2, int y2, QColor fore, QColor back, bool mode);

    void delay();

    void drawer(bool mode);

    void nullMapPixels();

    void calcTime(double time);

private slots:
    void on_appendButton_clicked();

    void on_deleteButton_clicked();

    void on_fillButton_clicked();

    void on_fillDelayButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QPair<int, int>> points_vec;
    QGraphicsScene *scene;
    int map_pixels[XSIZE + 1][YSIZE + 1] = { { 0 } };
};
#endif // MAINWINDOW_H
