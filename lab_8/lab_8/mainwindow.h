#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

#include "paintscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clearSceneButton_clicked();

    void on_answerColorButton_clicked();

    void on_cutterColorButton_clicked();

    void on_drawColorButton_clicked();

    void on_backColorButton_clicked();

    void on_inputFigureRadio_clicked();

    void on_inputCutterRadio_clicked();

    void on_endInputCutterButton_clicked();

private:
    Ui::MainWindow *ui;
    PaintScene *scene;
    QGraphicsScene *scene_back;
    QGraphicsScene *scene_draw;
    QGraphicsScene *scene_cutter;
    QGraphicsScene *scene_answer;
};
#endif // MAINWINDOW_H
