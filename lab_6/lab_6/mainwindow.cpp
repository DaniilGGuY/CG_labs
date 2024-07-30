#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Алгоритм построчного затравочного заполнения");

    scene = new PaintScene();
    scene->set_back(QColor(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value()));
    scene->set_draw(QColor(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value()));
    scene->setSceneRect(0, 0, XSIZE, YSIZE);
    scene->delete_draw();
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_appendButton_clicked()
{
    QString x_coord_string = ui->appendX->text();
    QString y_coord_string = ui->appendY->text();
    ui->appendX->clear();
    ui->appendY->clear();

    if (x_coord_string.size() == 0 || y_coord_string.size() == 0)
        QMessageBox::critical(this, "Ошибка", "Нечего добавлять. Введите целые числа");
    else
    {
        bool ok_x = false, ok_y = false;
        int x_coord = x_coord_string.toInt(&ok_x);
        if (!ok_x)
            QMessageBox::critical(this, "Ошибка", "Введенная X-координата не является целым числом");

        int y_coord = y_coord_string.toInt(&ok_y);
        if (!ok_y)
            QMessageBox::critical(this, "Ошибка", "Введенная Y-координата не является целым числом");

        if (ok_y && ok_x)
            scene->add_point_handle(x_coord, y_coord);
    }
}

void MainWindow::on_saveColorButton_clicked()
{
    scene->set_back(QColor(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value()));
    scene->set_draw(QColor(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value()));
    scene->delete_draw();
}

void MainWindow::on_endInputButton_clicked()
{
    scene->end_figure();
}

void MainWindow::on_clearButton_clicked()
{
    scene->delete_draw();
}

void MainWindow::on_saveDrawButton_clicked()
{
    scene->set_draw(QColor(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value()));
}

void MainWindow::on_inputCurveRadioButton_clicked()
{
    scene->set_mode(DRAW_CURVE);
}

void MainWindow::on_fillRadioButton_clicked()
{
    scene->set_mode(FILL);
}

void MainWindow::on_FillDelayRadioButton_clicked()
{
    scene->set_mode(FILL_DELAY);
}

void MainWindow::on_inputRadioButton_clicked()
{
    scene->set_mode(DRAW_RECT);
}
