#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->prevPartButton->hide();
    ui->nextPartButton->hide();
    pos = 0;
    figure_t figure = figure_init();
    (void)read_figure(figure, "D:/MyProject/universe/kg_labs/lab_2/lab_2/files/figure.txt");
    history.append(figure);
}

MainWindow::~MainWindow()
{
    while (history.size())
    {
        free_figure(history[history.size() - 1]);
        history.pop_back();
    }

    delete ui;
}

void MainWindow::drawAxis(QPainter *painter)
{
    painter->setPen(QPen(Qt::gray, 2));

    for (int i = STEP; i <= WIDTH; i += STEP) {
        for (int j = STEP; j <= HEIGHT; j += STEP / 5) {
            painter->drawPoint(QPoint(i, j));
            painter->drawPoint(QPoint(j, i));
        }
    }
}

void MainWindow::drawFigure(QPainter *painter)
{
    figure_t figure = figure_init();
    copy_figure(figure, history[pos]);
    painter->setPen(QPen(Qt::red, 2));
    for (int i = 0; i < figure.edges.size; ++i)
    {
        int v1 = figure.edges.data[i].vertex1, v2 = figure.edges.data[i].vertex2;
        painter->drawLine(figure.vertexes.data[v1].x, figure.vertexes.data[v1].y, figure.vertexes.data[v2].x, figure.vertexes.data[v2].y);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    drawAxis(&painter);
    drawFigure(&painter);
}

void MainWindow::addPart(figure_t figure)
{
    pos += 1;
    while (history.size() != pos)
    {
        free_figure(history[history.size() - 1]);
        history.pop_back();
    }

    ui->nextPartButton->hide();
    history.append(figure);
    if (ui->prevPartButton->isHidden())
        ui->prevPartButton->show();
}

void MainWindow::on_transferButton_clicked()
{
    this->setEnabled(false);
    transfer = new TransferWindow;
    transfer->exec();
    this->setEnabled(true);
    if (transfer->process_finished_ok)
    {
        transfer_t transfer_figure;
        transfer->get_params(&transfer_figure.dx, &transfer_figure.dy);
        figure_t figure = figure_init();
        proc_err_t rc = deep_copy_figure(figure, history[pos]);
        if (!rc)
            rc = figure_transfer(figure, transfer_figure);

        if (rc)
        {
            throw_error(rc);
            free_figure(figure);
        }
        else
            addPart(figure);
    }
}

void MainWindow::on_scaleButton_clicked()
{
    this->setEnabled(false);
    scale = new ScalingWindow;
    scale->exec();
    this->setEnabled(true);
    if (scale->process_finished_ok)
    {
        scale_t scale_figure;
        vertex_t center;
        scale->get_params(&center.x, &center.y, &scale_figure.kx, &scale_figure.ky);
        figure_t figure = figure_init();
        copy_figure(figure, history[pos]);
        proc_err_t rc = deep_copy_figure(figure, history[pos]);
        if (!rc)
            rc = figure_scale(figure, center, scale_figure);

        if (rc)
        {
            throw_error(rc);
            free_figure(figure);
        }
        else
            addPart(figure);
    }
}

void MainWindow::on_rotateButton_clicked()
{
    this->setEnabled(false);
    rotate = new RotateWindow;
    rotate->exec();
    this->setEnabled(true);
    if (rotate->process_finished_ok)
    {
        rotate_t rotate_figure;
        vertex_t center;
        rotate->get_params(&center.x, &center.y, &rotate_figure.z_rot);
        figure_t figure = figure_init();
        copy_figure(figure, history[pos]);
        proc_err_t rc = deep_copy_figure(figure, history[pos]);
        if (!rc)
            rc = figure_rotate(figure, center, rotate_figure);

        if (rc)
        {
            throw_error(rc);
            free_figure(figure);
        }
        else
            addPart(figure);
    }
}

void MainWindow::on_prevPartButton_clicked()
{
    --pos;
    if (pos == 0)
        ui->prevPartButton->hide();

    if (ui->nextPartButton->isHidden())
        ui->nextPartButton->show();

    repaint();
}

void MainWindow::on_nextPartButton_clicked()
{
    ++pos;
    if (pos == history.size() - 1)
        ui->nextPartButton->hide();

    if (ui->prevPartButton->isHidden())
        ui->prevPartButton->show();

    repaint();
}
