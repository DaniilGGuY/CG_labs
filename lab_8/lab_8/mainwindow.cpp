#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Алгоритм Кируса-Бека");

    scene_back = new QGraphicsScene;
    ui->backColorView->setScene(scene_back);
    ui->backColorView->setBackgroundBrush(Qt::white);
    this->setMouseTracking(false);

    scene_draw = new QGraphicsScene;
    ui->drawColorView->setScene(scene_draw);
    ui->drawColorView->setBackgroundBrush(Qt::black);

    scene_cutter = new QGraphicsScene;
    ui->cutterColorView->setScene(scene_cutter);
    ui->cutterColorView->setBackgroundBrush(Qt::blue);

    scene_answer = new QGraphicsScene;
    ui->answerColorView->setScene(scene_answer);
    ui->answerColorView->setBackgroundBrush(Qt::red);

    scene = new PaintScene();
    scene->setSceneRect(0, 0, XSIZE, YSIZE);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearSceneButton_clicked()
{
    scene->deleteDraw();
}

void MainWindow::on_answerColorButton_clicked()
{
    QColor newCol = QColorDialog::getColor();
    ui->answerColorView->setBackgroundBrush(newCol);
    scene->setAnswer(newCol);
}

void MainWindow::on_cutterColorButton_clicked()
{
    QColor newCol = QColorDialog::getColor();
    ui->cutterColorView->setBackgroundBrush(newCol);
    scene->setCutter(newCol);
}

void MainWindow::on_drawColorButton_clicked()
{
    QColor newCol = QColorDialog::getColor();
    ui->drawColorView->setBackgroundBrush(newCol);
    scene->setDraw(newCol);
}

void MainWindow::on_backColorButton_clicked()
{
    QColor newCol = QColorDialog::getColor();
    ui->backColorView->setBackgroundBrush(newCol);
    scene->setBack(newCol);
    scene->readdSegments();
}

void MainWindow::on_inputFigureRadio_clicked()
{
    scene->setMode(DRAW_FIGURE);
}

void MainWindow::on_inputCutterRadio_clicked()
{
    scene->setMode(DRAW_CUTTER);
}

void MainWindow::on_endInputCutterButton_clicked()
{
    scene->endCutterInput();
}
