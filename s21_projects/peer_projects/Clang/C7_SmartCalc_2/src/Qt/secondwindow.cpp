#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <iostream>
#include <QInputDialog>
#include <qmath.h>

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    setWindowTitle("Graphics by Bail Agda");
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::set_str(QString str) {
    ui->label_expresion->setText(str);
}

void SecondWindow::make_graph() {
    double X = 0.0;
    double Y = 0.0;
    double x_min = ui->x_min->value();
    double x_max = ui->x_max->value();
    double y_min = 0;
    double y_max = 0;
    double h = 0.005 * (qFabs(x_min) + qFabs(x_max));
    QString str = ui->label_expresion->text();

    X = x_min;
    while (X <= x_max) {
        x.push_back(X);
        start_calc((char*)str.toStdString().c_str(), &Y, &X);
        y.push_back(Y);
        if (X == x_min) {
            y_min = Y-3*h;
            y_max = Y+3*h;
        }
        if (Y < y_min) y_min = Y;
        if (Y > y_max) y_max = Y;
        X += h;
    }

    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min, y_max);

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();
    x.clear();
    y.clear();
}

void SecondWindow::on_pushButton_clicked()
{
    ui->widget->clearGraphs();

    make_graph();
}

