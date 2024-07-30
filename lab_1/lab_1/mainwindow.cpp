#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawAxis(QPainter *painter)
{
    painter->setPen(QPen(Qt::gray, 2));

    for (int i = 20, t = 20; i <= 580; i += t) {
        for (int j = 20; j <= 580; j += 4) {
            painter->drawPoint(QPoint(i, j));
            painter->drawPoint(QPoint(j, i));
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    drawAxis(&painter);

    if (ui->tableWidget->rowCount() > 0)
    {
        double max_x = ui->tableWidget->item(0, 0)->text().toFloat();
        double min_x = ui->tableWidget->item(0, 0)->text().toFloat();
        double max_y = ui->tableWidget->item(0, 1)->text().toFloat();
        double min_y = ui->tableWidget->item(0, 1)->text().toFloat();
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
            double cur_x = ui->tableWidget->item(i, 0)->text().toFloat();
            double cur_y = ui->tableWidget->item(i, 1)->text().toFloat();
            if (cur_x > max_x)
                max_x = cur_x;
            if (cur_x < min_x)
                min_x = cur_x;
            if (cur_y < min_y)
                min_y = cur_y;
            if (cur_y > max_y)
                max_y = cur_y;
        }

        double top_right = (max_x > max_y ? max_x : max_y);
        double bottom_left = (min_x < min_y ? min_x : min_y);
        double masht = (qAbs(top_right - bottom_left) < EPS) ? 0 : 560 / (top_right - bottom_left);
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
            double cur_x = ui->tableWidget->item(i, 0)->text().toFloat();
            double cur_y = ui->tableWidget->item(i, 1)->text().toFloat();
            painter.setPen(QPen(Qt::red, 4));
            painter.drawPoint(QPoint((cur_x - (top_right + bottom_left) / 2) * masht + 300, \
                                     (600 - ((cur_y  - (top_right + bottom_left) / 2) * masht + 300))));
            painter.setFont(QFont("Times", 10));
            painter.setPen(QPen(Qt::black));
            painter.drawText(QPoint((cur_x - (top_right + bottom_left) / 2) * masht + 302, \
                                   (600 - ((cur_y  - (top_right + bottom_left) / 2) * masht + 302))), \
                            "(" + QString::number(cur_x) + ";" + QString::number(cur_y) + ")");
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setDown(true);
    QString x_coord_string = ui->lineEdit->text();
    QString y_coord_string = ui->lineEdit_2->text();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    if (x_coord_string.size() == 0 || y_coord_string.size() == 0)
        QMessageBox::warning(this, "Предупреждение", "Нечего добавлять. Введите вещественные числа");
    else
    {
        bool ok_x = false, ok_y = false;
        double x_coord = x_coord_string.toDouble(&ok_x);
        if (!ok_x)
            QMessageBox::warning(this, "Предупреждение", "Введенная X-координата не является вещественным числом");

        double y_coord = y_coord_string.toDouble(&ok_y);
        if (!ok_y)
            QMessageBox::warning(this, "Предупреждение", "Введенная Y-координата не является вещественным числом");

        if (ok_y && ok_x)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::number(x_coord)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(y_coord)));
            qDebug() << "Added point (" << QString::number(x_coord) << ":" << QString::number(y_coord) << ")";
            repaint();
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->pushButton_4->setDown(true);
    QString x_coord_string = ui->lineEdit_4->text();
    QString y_coord_string = ui->lineEdit_3->text();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();

    if (x_coord_string.size() == 0 || y_coord_string.size() == 0)
        QMessageBox::warning(this, "Предупреждение", "Нечего добавлять. Введите вещественные числа");
    else
    {
        bool ok_x = false, ok_y = false;
        double x_coord = x_coord_string.toDouble(&ok_x);
        if (!ok_x)
            QMessageBox::warning(this, "Предупреждение", "Введенная X-координата не является вещественным числом");

        double y_coord = y_coord_string.toDouble(&ok_y);
        if (!ok_y)
            QMessageBox::warning(this, "Предупреждение", "Введенная Y-координата не является вещественным числом");

        if (ok_y && ok_x)
        {
            for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
            {
                if (ui->tableWidget->item(i, 0)->text() == x_coord_string && ui->tableWidget->item(i, 1)->text() == y_coord_string)
                {
                    ui->tableWidget->removeRow(i);
                    qDebug() << "Removed point (" << QString::number(x_coord) << ":" << QString::number(y_coord) << ")";
                    repaint();
                    break;
                }
            }
        }
    }
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    if (ui->pushButton->isDown() || ui->pushButton_4->isDown())
    {
        ui->pushButton->setDown(false);
        ui->pushButton_4->setDown(false);
    }
    else
        repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->tableWidget->rowCount() < 3)
        QMessageBox::warning(this, "Предупреждение", "Для получения ответа необходимо ввести минимум три точки");
    else
    {
        answer_w = new AnswerWindow;
        answer_w->show();
        answer_w->set_table(ui->tableWidget);
        answer_w->find_ans();
    }
}
