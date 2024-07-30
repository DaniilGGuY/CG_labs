#include <cmath>
#include <chrono>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Алгоритм заполнения по ребрам");
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, XSIZE, YSIZE);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->position().x();
    int y = event->position().y();
    if (x < OFFSET || y < OFFSET || x > XSIZE + OFFSET || y > YSIZE + OFFSET)
        return;

    ui->pointsTable->insertRow(ui->pointsTable->rowCount());
    ui->pointsTable->setItem(ui->pointsTable->rowCount() - 1, 0, new QTableWidgetItem(QString::number(x)));
    ui->pointsTable->setItem(ui->pointsTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(y)));
    points_vec.append(qMakePair(x, y));
    qDebug() << "Added point (" << QString::number(x) << ":" << QString::number(y) << ")";
    drawPolygon();
}

void MainWindow::drawPolygon()
{
    QColor back(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value());
    QColor fore(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value());

    scene->clear();
    ui->graphicsView->setBackgroundBrush(back);
    for (int i = 1; i < points_vec.size(); ++i)
    {
        int x1 = points_vec[i - 1].first;
        int y1 = points_vec[i - 1].second;
        int x2 = points_vec[i].first;
        int y2 = points_vec[i].second;
        scene->addLine(x1, y1, x2, y2, QPen(fore, 1));
    }

    if (points_vec.size() > 2)
    {
        int x1 = points_vec[0].first;
        int y1 = points_vec[0].second;
        int x2 = points_vec[points_vec.size() - 1].first;
        int y2 = points_vec[points_vec.size() - 1].second;
        scene->addLine(x1, y1, x2, y2, QPen(fore, 1));
    }
}

void MainWindow::on_appendButton_clicked()
{
    QString x_coord_string = ui->appendX->text();
    QString y_coord_string = ui->appendY->text();
    ui->appendX->clear();
    ui->appendY->clear();

    if (x_coord_string.size() == 0 || y_coord_string.size() == 0)
        QMessageBox::critical(this, "Ошибка", "Нечего добавлять. Введите вещественные числа");
    else
    {
        bool ok_x = false, ok_y = false;
        int x_coord = x_coord_string.toInt(&ok_x);
        if (!ok_x)
            QMessageBox::critical(this, "Ошибка", "Введенная X-координата не является вещественным числом");

        int y_coord = y_coord_string.toInt(&ok_y);
        if (!ok_y)
            QMessageBox::critical(this, "Ошибка", "Введенная Y-координата не является вещественным числом");

        if (ok_y && ok_x)
        {
            points_vec.append(qMakePair(x_coord, y_coord));
            ui->pointsTable->insertRow(ui->pointsTable->rowCount());
            ui->pointsTable->setItem(ui->pointsTable->rowCount() - 1, 0, new QTableWidgetItem(QString::number(x_coord)));
            ui->pointsTable->setItem(ui->pointsTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(y_coord)));
            qDebug() << "Added point (" << QString::number(x_coord) << ":" << QString::number(y_coord) << ")";
            drawPolygon();
        }
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QString num_string = ui->deleteNum->text();
    ui->deleteNum->clear();

    if (num_string.size() == 0)
        QMessageBox::critical(this, "Ошибка", "Введите номер токи, которую хотите удалить");
    else
    {
        bool ok_x = false;
        int num = num_string.toInt(&ok_x);
        if (!ok_x)
            QMessageBox::critical(this, "Ошибка", "Номер должен быть целым положительным числом");

        if (num <= 0 || num > ui->pointsTable->rowCount())
            QMessageBox::critical(this, "Ошибка", "Точки с таким номером не существует");
        else if (ok_x)
        {
            points_vec.remove(num - 1);
            ui->pointsTable->removeRow(num - 1);
            qDebug() << "Removed point number: " << num;
            drawPolygon();
        }
    }
}

void MainWindow::delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(DELAY);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::calcMatPixels(int x1, int y1, int x2, int y2, QColor fore, QColor back, bool mode)
{
    if (y1 == y2)
        return;

    if (y1 > y2)
    {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
        tmp = x2;
        x2 = x1;
        x1 = tmp;
    }

    double dx = x2 - x1, dy = y2 - y1;
    double tan = dx / dy;
    double x_real = x1;
    for (int y = y1; y < y2; ++y)
    {
        int x = round(x_real);
        while (x <= XSIZE)
        {
            map_pixels[x][y] = 1 - map_pixels[x][y];
            if (map_pixels[x][y] == 1)
                scene->addLine(x, y, x, y, QPen(fore, 1));
            else
                scene->addLine(x, y, x, y, QPen(back, 1));

            ++x;
        }

        if (mode == WITHDELAY)
            delay();

        x_real += tan;
    }
}

void MainWindow::drawer(bool mode)
{
    if (points_vec.size() < 3)
    {
        QMessageBox::critical(this, "Ошибка", "Введите больше точек");
        return;
    }

    QColor back(ui->RedBack->value(), ui->GreenBack->value(), ui->BlueBack->value());
    QColor fore(ui->RedFore->value(), ui->GreenFore->value(), ui->BlueFore->value());
    scene->clear();
    ui->graphicsView->setBackgroundBrush(back);

    int x1, y1, x2, y2;
    for (int i = 1; i < points_vec.size(); ++i)
    {
        x1 = points_vec[i - 1].first;
        y1 = points_vec[i - 1].second;
        x2 = points_vec[i].first;
        y2 = points_vec[i].second;
        calcMatPixels(x1, y1, x2, y2, fore, back, mode);
    }

    x1 = points_vec[points_vec.size() - 1].first;
    y1 = points_vec[points_vec.size() - 1].second;
    x2 = points_vec[0].first;
    y2 = points_vec[0].second;
    calcMatPixels(x1, y1, x2, y2, fore, back, mode);
}

void MainWindow::nullMapPixels()
{
    for (int x = 0; x <= XSIZE; ++x)
        for (int y = 0; y <= YSIZE; ++y)
            map_pixels[x][y] = 0;
}

void MainWindow::calcTime(double time)
{
    QMessageBox::information(this, "Время работы", QString::number(time) + " мс");
}

void MainWindow::on_fillButton_clicked()
{
    nullMapPixels();
    auto start = std::chrono::high_resolution_clock::now();
    drawer(WITHOUTDELAY);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    calcTime(std::chrono::duration<double>(duration).count());
}

void MainWindow::on_fillDelayButton_clicked()
{
    nullMapPixels();
    drawer(WITHDELAY);
}
