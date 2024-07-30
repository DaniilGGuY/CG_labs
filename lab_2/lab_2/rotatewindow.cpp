#include "rotatewindow.h"
#include "ui_rotatewindow.h"
#include "processerror.h"

RotateWindow::RotateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotateWindow)
{
    ui->setupUi(this);
    process_finished_ok = false;
}

RotateWindow::~RotateWindow()
{
    delete ui;
}

void RotateWindow::get_params(double *x_cent, double *y_cent, double *angle)
{
    *x_cent = this->x_cent;
    *y_cent = this->y_cent;
    *angle = this->rot_angle;
}

void RotateWindow::on_pushButton_clicked()
{
    QString x_cent_string = ui->lineEdit->text();
    QString y_cent_string = ui->lineEdit_2->text();
    QString rot_angle_string = ui->lineEdit_3->text();

    if (x_cent_string.size() == 0 || y_cent_string.size() == 0 || rot_angle_string.size() == 0)
        throw_error(ERR_UI_FORMS);
    else
    {
        bool ok_x_cent = false, ok_y_cent = false, ok_rot = false;
        this->x_cent = x_cent_string.toDouble(&ok_x_cent);
        if (!ok_x_cent)
            throw_error(ERR_UI_FORMS);

        this->y_cent = y_cent_string.toDouble(&ok_y_cent);
        if (!ok_y_cent)
            throw_error(ERR_UI_FORMS);

        this->rot_angle = rot_angle_string.toDouble(&ok_rot);
        if (!ok_rot)
            throw_error(ERR_UI_FORMS);

        if (ok_x_cent && ok_y_cent && ok_rot)
        {
            process_finished_ok = true;
            close();
        }
    }
}
