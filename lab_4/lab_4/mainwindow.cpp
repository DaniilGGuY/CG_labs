#include <QMessageBox>
#include <QVector>
#include <QGraphicsScene>
#include <ctime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algoses.h"
#include "draw.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Алгоритмы построения окружностей и эллипсов");
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 550, 550);
    map = new QImage(550, 550, QImage::Format_ARGB32);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawCircleByAlg(double x_cent, double y_cent, double radius, QColor back, QColor fore)
{
    QVector<QPair<int, int>> pixels;

    QColor old = ui->graphicsView->backgroundBrush().color();
    if (old != back)
        ui->graphicsView->setBackgroundBrush(back);

    if (ui->CanonicButton->isChecked())
    {
        canonicCircleDraw(pixels, x_cent, y_cent, radius);
        drawPixels(ui->graphicsView->scene(), map, pixels, fore);
    }
    else if (ui->ParametricButton->isChecked())
    {
        parametricCircleDraw(pixels, x_cent, y_cent, radius);
        drawPixels(ui->graphicsView->scene(), map, pixels, fore);
    }
    else if (ui->BrezenhemButton->isChecked())
    {
        brezenhemCircleDraw(pixels, x_cent, y_cent, radius);
        drawPixels(ui->graphicsView->scene(), map, pixels, fore);
    }
    else if (ui->MiddlePointButton->isChecked())
    {
        middleCircleDraw(pixels, x_cent, y_cent, radius);
        drawPixels(ui->graphicsView->scene(), map, pixels, fore);
    }
    else
        ui->graphicsView->scene()->addEllipse(x_cent - radius, y_cent - radius, radius * 2, radius * 2, QPen(fore, 1));
}

void MainWindow::drawEllipsByAlg(double x_cent, double y_cent, double a, double b, QColor back, QColor fore)
{
    QVector<QPair<int, int>> pixels;

    QColor old = ui->graphicsView->backgroundBrush().color();
    if (old != back)
        ui->graphicsView->setBackgroundBrush(back);

    if (ui->CanonicButton->isChecked())
    {
        canonicEllipsDraw(pixels, x_cent, y_cent, a, b);
        drawPixels(ui->graphicsView->scene(), map, pixels, fore);
    }
    else if (ui->ParametricButton->isChecked())
    {
        parametricEllipsDraw(pixels, x_cent, y_cent, a, b);
        drawPixels(ui->graphicsView->scene(), map, pixels, fore);
    }
    else if (ui->BrezenhemButton->isChecked())
    {
        brezenhemEllipsDraw(pixels, x_cent, y_cent, a, b);
        drawPixels(ui->graphicsView->scene(), map, pixels, fore);
    }
    else if (ui->MiddlePointButton->isChecked())
    {
        middleEllipsDraw(pixels, x_cent, y_cent, a, b);
        drawPixels(ui->graphicsView->scene(), map, pixels, fore);
    }
    else
        ui->graphicsView->scene()->addEllipse(x_cent - a, y_cent - b, a * 2, b * 2, QPen(fore, 1));
}

void MainWindow::drawCircleSpecterByAlg(double x_cent, double y_cent, double radius, double step, int count, QColor back, QColor fore)
{
    for (int i = 0; i < count; ++i)
        drawCircleByAlg(x_cent, y_cent, radius + i * step, back, fore);
}

void MainWindow::drawEllipsSpecterByAlg(double x_cent, double y_cent, double a, double b, double step, int count, QColor back, QColor fore)
{
    for (int i = 0; i < count; ++i)
        drawEllipsByAlg(x_cent, y_cent, a + i * step, b + i * step, back, fore);
}

void MainWindow::on_DrawCircleButton_clicked()
{
    QString x_center_string = ui->XCenter->text();
    QString y_center_string = ui->YCenter->text();
    QString radius_string = ui->Radius->text();

    if (!ui->CanonicButton->isChecked() && !ui->ParametricButton->isChecked() && !ui->BrezenhemButton->isChecked() \
            && !ui->MiddlePointButton->isChecked() && !ui->StandartFunctionButton->isChecked())
        QMessageBox::critical(this, "Ошибка", "Выберите алгоритм построения");
    else
    {
        if (!x_center_string.size() || !y_center_string.size() || !radius_string.size())
            QMessageBox::critical(this, "Ошибка", "Введите все необходимые исходные данные");
        else
        {
            bool ok = false;
            double x_cent = x_center_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение x-координаты центра окружности");

            double y_cent = y_center_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение y-координаты центра окружности");

            double radius = radius_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение радиуса");

            QColor back(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value());
            QColor fore(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value());

            if (ok)
                drawCircleByAlg(x_cent, y_cent, radius, back, fore);
        }
    }
}

void MainWindow::on_DrawEllipsButton_clicked()
{
    QString x_center_string = ui->XCenter->text();
    QString y_center_string = ui->YCenter->text();
    QString a_string = ui->XAxelShaft->text();
    QString b_string = ui->YAxelShaft->text();

    if (!ui->CanonicButton->isChecked() && !ui->ParametricButton->isChecked() && !ui->BrezenhemButton->isChecked() \
            && !ui->MiddlePointButton->isChecked() && !ui->StandartFunctionButton->isChecked())
        QMessageBox::critical(this, "Ошибка", "Выберите алгоритм построения");
    else
    {
        if (!x_center_string.size() || !y_center_string.size() || !a_string.size() || !b_string.size())
            QMessageBox::critical(this, "Ошибка", "Введите все необходимые исходные данные");
        else
        {
            bool ok = false;
            double x_cent = x_center_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение x-координаты центра эллипса");

            double y_cent = y_center_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение y-координаты центра эллипса");

            double a = a_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение полуоси a (OX)");

            double b = b_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение полуоси b (OY)");

            QColor back(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value());
            QColor fore(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value());

            if (ok)
                drawEllipsByAlg(x_cent, y_cent, a, b, back, fore);
        }
    }
}

void MainWindow::on_CleareSceneButton_clicked()
{
    ui->graphicsView->scene()->clear();
    ui->graphicsView->setBackgroundBrush(Qt::white);
    for (int i = 0; i < map->height(); ++i)
        for (int j = 0; j < map->width(); ++j)
            map->setPixelColor(i, j, Qt::transparent);
}

void MainWindow::on_DrawSpectrCircleButton_clicked()
{
    QString radius_string = ui->Radius->text();
    QString step_string = ui->Step->text();
    QString count_string = ui->CountSteps->text();
    if (!ui->CanonicButton->isChecked() && !ui->ParametricButton->isChecked() && !ui->BrezenhemButton->isChecked() \
            && !ui->MiddlePointButton->isChecked() && !ui->StandartFunctionButton->isChecked())
        QMessageBox::critical(this, "Ошибка", "Выберите алгоритм построения");
    else
    {
        if (!radius_string.size() || !step_string.size() || !count_string.size())
            QMessageBox::critical(this, "Ошибка", "Введите все необходимые исходные данные");
        else
        {
            bool ok = false;

            double radius = radius_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение начального радиуса");

            double step = step_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение шага");

            int count = count_string.toInt(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение количества фигур");

            QColor back(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value());
            QColor fore(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value());

            if (ok)
                drawCircleSpecterByAlg(ui->graphicsView->geometry().height() / 2, ui->graphicsView->geometry().width() / 2, radius, step, count, back, fore);
        }
    }
}

void MainWindow::on_DrawSpectrEllipsButton_clicked()
{
    QString a_string = ui->XAxelShaft->text();
    QString b_string = ui->YAxelShaft->text();
    QString step_string = ui->Step->text();
    QString count_string = ui->CountSteps->text();
    if (!ui->CanonicButton->isChecked() && !ui->ParametricButton->isChecked() && !ui->BrezenhemButton->isChecked() \
            && !ui->MiddlePointButton->isChecked() && !ui->StandartFunctionButton->isChecked())
        QMessageBox::critical(this, "Ошибка", "Выберите алгоритм построения");
    else
    {
        if (!a_string.size() || !b_string.size() || !step_string.size() || !count_string.size())
            QMessageBox::critical(this, "Ошибка", "Введите все необходимые исходные данные");
        else
        {
            bool ok = false;

            double a = a_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение полуоси a (OX)");

            double b = b_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение полуоси b (OY)");

            double step = step_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение шага");

            int count = count_string.toInt(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение количества фигур");

            QColor back(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value());
            QColor fore(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value());

            if (ok)
                drawEllipsSpecterByAlg(ui->graphicsView->geometry().height() / 2, ui->graphicsView->geometry().width() / 2, a, b, step, count, back, fore);
        }
    }
}

void MainWindow::calcTimes(QVector<QVector<double>> &arr)
{
    for (int j = RADIUS, index = 0; j <= END_RADIUS; j += STEP, index += 1)
    {
        QVector<double> tmp;
        clock_t beg = clock();
        for (int i = 0; i < REPS; ++i)
        {
            QVector<QPair<int, int>> pixels;
            canonicCircleDraw(pixels, 300, 300, j);
        }
        clock_t end = clock();
        tmp.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);

        beg = clock();
        for (int  i = 0; i < REPS; ++i)
        {
            QVector<QPair<int, int>> pixels;
            parametricCircleDraw(pixels, 300, 300, j);
        }
        end = clock();
        tmp.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);

        beg = clock();
        for (int  i = 0; i < REPS; ++i)
        {
            QVector<QPair<int, int>> pixels;
            brezenhemCircleDraw(pixels, 300, 300, j);
        }
        end = clock();
        tmp.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);

        beg = clock();
        for (int  i = 0; i < REPS; ++i)
        {
            QVector<QPair<int, int>> pixels;
            middleCircleDraw(pixels, 300, 300, j);
        }
        end = clock();
        tmp.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);

        beg = clock();
        for (int  i = 0; i < REPS; ++i)
            ui->graphicsView->scene()->addEllipse(300 - j, 300 - j, j * 2, j * 2, QPen(Qt::transparent, 1));
        end = clock();
        tmp.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);

        arr.append(tmp);
    }
}

void MainWindow::on_CleareSceneButton_2_clicked()
{
    QVector<QVector<double>> times;

    calcTimes(times);
    this->setEnabled(false);
    times_comp = new TimesCompare;
    times_comp->setArray(times);
    times_comp->drawGraph(RADIUS, STEP, END_RADIUS);
    times_comp->exec();
    this->setEnabled(true);
}
