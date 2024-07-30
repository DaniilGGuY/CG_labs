#include "scalingwindow.h"
#include "ui_scalingwindow.h"
#include "processerror.h"

ScalingWindow::ScalingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScalingWindow)
{
    ui->setupUi(this);
    process_finished_ok = false;
}

ScalingWindow::~ScalingWindow()
{
    delete ui;
}

void ScalingWindow::get_params(double *x_cent, double *y_cent, double *kx, double *ky)
{
    *x_cent = this->x_cent;
    *y_cent = this->y_cent;
    *kx = this->kx;
    *ky = this->ky;
}

void ScalingWindow::on_pushButton_clicked()
{
    QString x_cent_string = ui->lineEdit->text();
    QString y_cent_string = ui->lineEdit_2->text();
    QString kx_string = ui->lineEdit_4->text();
    QString ky_string = ui->lineEdit_3->text();

    if (x_cent_string.size() == 0 || y_cent_string.size() == 0 || kx_string.size() == 0 || ky_string.size() == 0)
        throw_error(ERR_UI_FORMS);
    else
    {
        bool ok_x_cent = false, ok_y_cent = false, ok_kx = false, ok_ky = false;
        this->x_cent = x_cent_string.toDouble(&ok_x_cent);
        if (!ok_x_cent)
            throw_error(ERR_UI_FORMS);

        this->y_cent = y_cent_string.toDouble(&ok_y_cent);
        if (!ok_y_cent)
            throw_error(ERR_UI_FORMS);

        this->kx = kx_string.toDouble(&ok_kx);
        if (!ok_kx)
            throw_error(ERR_UI_FORMS);

        this->ky = ky_string.toDouble(&ok_ky);
        if (!ok_ky)
            throw_error(ERR_UI_FORMS);

        if (ok_x_cent && ok_y_cent && ok_kx && ok_ky)
        {
            process_finished_ok = true;
            close();
        }
    }
}
