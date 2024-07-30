#include "transferwindow.h"
#include "ui_transferwindow.h"
#include "processerror.h"

TransferWindow::TransferWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferWindow)
{
    ui->setupUi(this);
    process_finished_ok = false;
}

TransferWindow::~TransferWindow()
{
    delete ui;
}

void TransferWindow::get_params(double *dx, double *dy)
{
    *dx = this->dx;
    *dy = this->dy;
}

void TransferWindow::on_pushButton_clicked()
{
    QString dx_string = ui->lineEdit->text();
    QString dy_string = ui->lineEdit_2->text();

    if (dx_string.size() == 0 || dy_string.size() == 0)
        throw_error(ERR_UI_FORMS);
    else
    {
        bool ok_dx = false, ok_dy = false;
        this->dx = dx_string.toDouble(&ok_dx);
        if (!ok_dx)
            throw_error(ERR_UI_FORMS);

        this->dy = dy_string.toDouble(&ok_dy);
        if (!ok_dy)
            throw_error(ERR_UI_FORMS);

        if (ok_dy && ok_dx)
        {
            process_finished_ok = true;
            close();
        }
    }
}
