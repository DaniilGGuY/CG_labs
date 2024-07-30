#ifndef ANSWERWINDOW_H
#define ANSWERWINDOW_H

#include <QDialog>
#include <QTableWidget>

#define PI     3.14159
#define EPS    0.00001

namespace Ui {
class AnswerWindow;
}

class AnswerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnswerWindow(QWidget *parent = nullptr);
    ~AnswerWindow();
    void set_table(QTableWidget *table);
    void find_ans();

protected:
    void paintEvent(QPaintEvent *event);
    void drawAxis(QPainter *painter);

private:
    Ui::AnswerWindow *ui;
    QVector<QPair<double, double>> table_points;
    QVector<QPair<double, double>> answer_points;
    QPair<double, double> calc_center_circle();
};

#endif // ANSWERWINDOW_H
