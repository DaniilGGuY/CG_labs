#include <QMessageBox>
#include <QVector>
#include <QGraphicsScene>
#include <ctime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "digitaldifan.h"
#include "brezenhem.h"
#include "vu.h"
#include "draw.h"
#include "specfuncs.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Алгоритмы построения отрезков");
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 550, 550);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLineByAlg(double x_start, double y_start, double x_end, double y_end, double max_intense, QColor back, QColor fore)
{
    QVector<QPair<int, int>> pixels;
    QVector<QColor> intense;

    QColor old = ui->graphicsView->backgroundBrush().color();
    if (old != back)
        ui->graphicsView->setBackgroundBrush(back);

    if (ui->DDAButton->isChecked())
    {
        digitalDifAnalizer(pixels, x_start, y_start, x_end, y_end);
        drawPixels(ui->graphicsView->scene(), pixels, fore);
    }
    else if (ui->BrezenhemFloatButton->isChecked())
    {
        brezenhemFloat(pixels, x_start, y_start, x_end, y_end);
        drawPixels(ui->graphicsView->scene(), pixels, fore);
    }
    else if (ui->BrezenhemIntButton->isChecked())
    {
        brezenhemInt(pixels, x_start, y_start, x_end, y_end);
        drawPixels(ui->graphicsView->scene(), pixels, fore);
    }
    else if (ui->BrezenhemSmoothButton->isChecked())
    {
        brezenhemSmooth(pixels, intense, x_start, y_start, x_end, y_end, max_intense, back, fore);
        drawPixelsVector(ui->graphicsView->scene(), pixels, intense);
    }
    else if (ui->VUAlgButton->isChecked())
    {
        vuAlgorithm(pixels, intense, x_start, y_start, x_end, y_end, max_intense, back, fore);
        drawPixelsVector(ui->graphicsView->scene(), pixels, intense);
    }
    else
        ui->graphicsView->scene()->addLine(x_start, y_start, x_end, y_end, QPen(fore, 1));
}

void MainWindow::drawSpectrByAlg(double angle, double max_intense, QColor back, QColor fore)
{
    double x_start = 275, y_start = 275;
    double x_end = 500, y_end = 275;
    double i = 0;
    while (i < 360)
    {
        drawLineByAlg(x_start, y_start, x_end , y_end, max_intense, back, fore);
        turnPoint(x_end, y_end, x_start, y_start, angle);
        i += angle;
    }
}

void MainWindow::on_SegmentDrawButton_clicked()
{
    QString x_start_string = ui->StartXInput->text();
    QString y_start_string = ui->StartYInput->text();
    QString x_end_string = ui->EndXInput->text();
    QString y_end_string = ui->EndYInput->text();
    QString max_intense_string = ui->IntenseMaxInput->text();

    if (!ui->BrezenhemSmoothButton->isChecked() && !ui->VUAlgButton->isChecked() && !ui->BrezenhemFloatButton->isChecked() \
            && !ui->BrezenhemIntButton->isChecked() && !ui->DDAButton->isChecked() && !ui->StandartFunctionButton->isChecked())
        QMessageBox::critical(this, "Ошибка", "Выберите алгоритм построения отрезка");
    else
    {
        if (!x_start_string.size() || !y_start_string.size() || !x_end_string.size() || !y_end_string.size() \
                || ((ui->BrezenhemSmoothButton->isChecked() || ui->VUAlgButton->isChecked()) && !max_intense_string.size()))
            QMessageBox::critical(this, "Ошибка", "Введите все необходимые исходные данные");
        else
        {
            bool ok = false;
            double x_start = x_start_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение начальной x-координаты отрезка");

            double y_start = y_start_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение начальной y-координаты отрезка");

            double x_end = x_end_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение конечной x-координаты отрезка");

            double y_end = y_end_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение конечной y-координаты отрезка");

            double max_intense = 0;
            if (ui->BrezenhemSmoothButton->isChecked() || ui->VUAlgButton->isChecked())
            {
                max_intense = max_intense_string.toDouble(&ok);
                if (!ok)
                    QMessageBox::critical(this, "Ошибка", "Введено некорректное значение максимальной интенсивности");
            }

            QColor back(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value());
            QColor fore(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value());

            if (ok)
                drawLineByAlg(x_start, y_start, x_end, y_end, max_intense, back, fore);
        }
    }
}

void MainWindow::on_SpectrDrawButton_clicked()
{
    QString angle_step_string = ui->DeltaAngleInput->text();
    QString max_intense_string = ui->IntenseMaxInput->text();

    if (!ui->BrezenhemSmoothButton->isChecked() && !ui->VUAlgButton->isChecked() && !ui->BrezenhemFloatButton->isChecked() \
            && !ui->BrezenhemIntButton->isChecked() && !ui->DDAButton->isChecked() && !ui->StandartFunctionButton->isChecked())
        QMessageBox::critical(this, "Ошибка", "Выберите алгоритм построения отрезка");
    else
    {
        if (!angle_step_string.size() || ((ui->BrezenhemSmoothButton->isChecked() || ui->VUAlgButton->isChecked()) && !max_intense_string.size()))
            QMessageBox::critical(this, "Ошибка", "Введите все необходимые исходные данные");
        else
        {
            bool ok = false;
            double max_intense = 0;
            if (ui->BrezenhemSmoothButton->isChecked() || ui->VUAlgButton->isChecked())
            {
                max_intense = max_intense_string.toDouble(&ok);
                if (!ok)
                    QMessageBox::critical(this, "Ошибка", "Введено некорректное значение начальной x-координаты отрезка");
            }

            double angle_step = angle_step_string.toDouble(&ok);
            if (!ok)
                QMessageBox::critical(this, "Ошибка", "Введено некорректное значение начальной y-координаты отрезка");

            QColor back(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value());
            QColor fore(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value());

            if (ok)
                drawSpectrByAlg(angle_step, max_intense, back, fore);
        }
    }
}

void MainWindow::on_CleareSceneButton_clicked()
{
    ui->graphicsView->scene()->clear();
    ui->graphicsView->setBackgroundBrush(Qt::white);
    ui->RedBack->setValue(255);
    ui->GreenBack->setValue(255);
    ui->BlueBack->setValue(255);
    ui->RedFore->setValue(0);
    ui->GreenFore->setValue(0);
    ui->BlueFore->setValue(0);
}

void MainWindow::calcTimes(QVector<double> &arr)
{
    clock_t beg = clock();
    for (int  i = 0; i < REPS; ++i)
    {
        QVector<QPair<int, int>> pixels;
        digitalDifAnalizer(pixels, 0, 0, TIME_POINT, TIME_POINT);
    }
    clock_t end = clock();
    arr.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);

    beg = clock();
    for (int  i = 0; i < REPS; ++i)
    {
        QVector<QPair<int, int>> pixels;
        brezenhemFloat(pixels, 0, 0, TIME_POINT, TIME_POINT);
    }
    end = clock();
    arr.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);

    beg = clock();
    for (int  i = 0; i < REPS; ++i)
    {
        QVector<QPair<int, int>> pixels;
        brezenhemInt(pixels, 0, 0, TIME_POINT, TIME_POINT);
    }
    end = clock();
    arr.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);

    beg = clock();
    for (int  i = 0; i < REPS; ++i)
    {
        QVector<QPair<int, int>> pixels;
        QVector<QColor> intense;
        brezenhemSmooth(pixels, intense, 0, 0, TIME_POINT, TIME_POINT, 100, Qt::white, Qt::black);
    }
    end = clock();
    arr.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);

    beg = clock();
    for (int  i = 0; i < REPS; ++i)
    {
        QVector<QPair<int, int>> pixels;
        QVector<QColor> intense;
        vuAlgorithm(pixels, intense, 0, 0, TIME_POINT, TIME_POINT, 100, Qt::white, Qt::black);
    }
    end = clock();
    arr.append(double(end - beg) / CLOCKS_PER_SEC * 1000.0 / REPS);
}

void MainWindow::calcSteps(QVector<int> &arr)
{
    for (int i = 0; i < 180; i += 5)
    {
        double x_end = 500, y_end = 250;
        turnPoint(x_end, y_end, 250, 250, i);
        QVector<QPair<int, int>> pixels;
        QVector<QColor> intense;
        if (ui->DDAButton->isChecked())
            arr.append(digitalDifAnalizer(pixels, 250, 250, x_end, y_end));
        else if (ui->BrezenhemFloatButton->isChecked())
            arr.append(brezenhemFloat(pixels, 250, 250, x_end, y_end));
        else if (ui->BrezenhemIntButton->isChecked())
            arr.append(brezenhemInt(pixels, 250, 250, x_end, y_end));
        else if (ui->BrezenhemSmoothButton->isChecked())
            arr.append(brezenhemSmooth(pixels, intense, 250, 250, x_end, y_end, 100, Qt::white, Qt::black));
        else
            arr.append(vuAlgorithm(pixels, intense, 250, 250, x_end, y_end, 100, Qt::white, Qt::black));
    }
}

void MainWindow::on_CompareTimeButton_clicked()
{
    QVector<double> times;

    calcTimes(times);

    this->setEnabled(false);
    times_comp = new TimesCompare;
    times_comp->setArray(times);
    times_comp->drawHist();
    times_comp->exec();
    this->setEnabled(true);
}

void MainWindow::on_CompareSmoothButton_clicked()
{
    if (ui->StandartFunctionButton->isChecked())
        QMessageBox::critical(this, "Ошибка", "Выберите другой алгоритм построения отрезка");
    else if (!ui->BrezenhemSmoothButton->isChecked() && !ui->VUAlgButton->isChecked() && !ui->BrezenhemFloatButton->isChecked() \
            && !ui->BrezenhemIntButton->isChecked() && !ui->DDAButton->isChecked())
        QMessageBox::critical(this, "Ошибка", "Выберите алгоритм построения отрезка");
    else
    {
        QVector<int> steps;

        calcSteps(steps);
        step_comp = new StepCompare;
        step_comp->setArray(steps);

        if (ui->DDAButton->isChecked())
            step_comp->drawGraph("Цифровой дифференциальный анализатор");
        else if (ui->BrezenhemFloatButton->isChecked())
            step_comp->drawGraph("Брезенхем для вещественных");
        else if (ui->BrezenhemIntButton->isChecked())
            step_comp->drawGraph("Брезенхем для целых");
        else if (ui->BrezenhemSmoothButton->isChecked())
            step_comp->drawGraph("Брезенхем с устранением ступенчатости");
        else
            step_comp->drawGraph("Ву алгоритм");

        step_comp->show();
    }
}
