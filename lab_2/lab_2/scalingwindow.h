#ifndef SCALINGWINDOW_H
#define SCALINGWINDOW_H

#include <QDialog>

namespace Ui {
class ScalingWindow;
}

class ScalingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ScalingWindow(QWidget *parent = nullptr);
    ~ScalingWindow();
    void get_params(double *x_cent, double *y_cent, double *kx, double *ky);
    bool process_finished_ok;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ScalingWindow *ui;
    double x_cent;
    double y_cent;
    double kx;
    double ky;
};

#endif // SCALINGWINDOW_H
