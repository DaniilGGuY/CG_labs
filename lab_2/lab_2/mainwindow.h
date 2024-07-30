#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "transferwindow.h"
#include "rotatewindow.h"
#include "scalingwindow.h"
#include "figure.h"

#define STEP       20
#define HEIGHT    600
#define WIDTH     600

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addPart(figure_t figure);

protected:
    void paintEvent(QPaintEvent *event);
    void drawAxis(QPainter *painter);
    void drawFigure(QPainter *painter);

private slots:
    void on_transferButton_clicked();

    void on_scaleButton_clicked();

    void on_rotateButton_clicked();

    void on_prevPartButton_clicked();

    void on_nextPartButton_clicked();

private:
    Ui::MainWindow *ui;
    TransferWindow *transfer;
    RotateWindow *rotate;
    ScalingWindow *scale;
    QVector<figure_t> history;
    int pos;
};
#endif // MAINWINDOW_H
