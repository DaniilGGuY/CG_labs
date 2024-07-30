#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

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
    void on_appendButton_clicked();

    void on_saveColorButton_clicked();

    void on_endInputButton_clicked();

    void on_clearButton_clicked();

    void on_saveDrawButton_clicked();

    void on_inputCurveRadioButton_clicked();

    void on_fillRadioButton_clicked();

    void on_FillDelayRadioButton_clicked();

    void on_inputRadioButton_clicked();

private:
    Ui::MainWindow *ui;
    PaintScene *scene;
};
#endif // MAINWINDOW_H
