#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QDialog>

namespace Ui {
class TransferWindow;
}

class TransferWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransferWindow(QWidget *parent = nullptr);
    ~TransferWindow();
    void get_params(double *dx, double *dy);
    bool process_finished_ok;

private slots:
    void on_pushButton_clicked();

private:
    Ui::TransferWindow *ui;
    double dx;
    double dy;
};

#endif // TRANSFERWINDOW_H
