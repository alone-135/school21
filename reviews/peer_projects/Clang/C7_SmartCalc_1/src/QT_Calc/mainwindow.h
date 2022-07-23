#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>
#include <QTimer>
#include <QtMath>


#ifdef __cplusplus
extern "C"{
#endif
    #include "s21_calc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double xBegin, xEnd, h, X, xy_1, xy_2, result_1, result_2;
    int N;

    QVector<double> x, y;

private slots:
    void digits_numbers();
    void on_pushButton_dot_clicked();
    void operationsSum();
    void operationsMult();
    void helpLeftOperator();
    void helpRightOperator();
    void clearButton();
    void mathFunction();
    void on_pushButton_Graph_clicked();
    void on_pushButton_ravno_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_clicked();
    void on_pushButton_10_clicked();
};
#endif // MAINWINDOW_H
