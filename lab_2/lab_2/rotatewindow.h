#ifndef ROTATEWINDOW_H
#define ROTATEWINDOW_H

#include <QDialog>

namespace Ui {
class RotateWindow;
}

class RotateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RotateWindow(QWidget *parent = nullptr);
    ~RotateWindow();
    void get_params(double *x_cent, double *y_cent, double *angle);
    bool process_finished_ok;

private slots:
    void on_pushButton_clicked();

private:
    Ui::RotateWindow *ui;
    double x_cent;
    double y_cent;
    double rot_angle;
};

#endif // ROTATEWINDOW_H
