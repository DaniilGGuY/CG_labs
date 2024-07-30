#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "answerwindow.h"

#include <QMainWindow>

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
    void paintEvent(QPaintEvent *event);
    void drawAxis(QPainter *painter);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    AnswerWindow *answer_w;
};
#endif // MAINWINDOW_H
