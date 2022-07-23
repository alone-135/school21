#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QInputDialog>
#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "credit_calc.h"
#include "ui_credit_calc.h"
#include "deposit_calc.h"
#include "ui_deposit_calc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QIcon icon (":./icon.icns");
//    QWidget::setWindowIcon(icon);

    setWindowTitle("Calculator by Bail Agda");

    connect(ui->_0,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->_1,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->_2,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->_3,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->_4,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->_5,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->_6,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->_7,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->_8,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->_9,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->acos_but,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->asi_but,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->atan_but,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->but_x,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->clean_but,SIGNAL(clicked()), this, SLOT(all_clean()));
    connect(ui->close_br,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->open_br,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->cos_but,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->sin_but,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->tan_but,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->ln,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->log,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->div_but,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->mult_but,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->dot_Button,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->plus,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->minus,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->sqrt,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pow,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->mod_Button,SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->result_but,SIGNAL(clicked()), this, SLOT(equal()));
    connect(ui->graph,SIGNAL(clicked()), this, SLOT(build_graph()));
    connect(ui->credit_calc,SIGNAL(clicked()), this, SLOT(make_credit_calculation()));
    connect(ui->deposit_calc,SIGNAL(clicked()), this, SLOT(make_deposit_calculation()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dig_num()
{
     QPushButton *button = (QPushButton *)sender();
     ui->result_show->setText(ui->result_show->text() + button->text());

}

void  MainWindow::equal() {
    QString print;
    if (!ui->result_show->text().isEmpty()) {
        double x = 0.0;
        if (ui->result_show->text().contains('x')) {
            bool ok;
            x = QInputDialog::getDouble(this, tr("Введите значение Х"), tr("Х = "), 0.0, -MAXFLOAT, MAXFLOAT, 8, &ok);
        }
         double res = 0.0;
         int err = 0;
         err = start_calc((char*)ui->result_show->text().toStdString().c_str(), &res, &x);
         if (err != 0) {
             print = "ERROR: value cannot be calculated";
             ui->res_print->setText(print);
         } else {
             ui->res_print->setText(QString::number(res));
         }
    } else {
        print = "ERROR: data input";
         ui->res_print->setText(print);
    }
}

void MainWindow::all_clean() {
    ui->result_show->setText("");
    ui->res_print->setText("");
}

void MainWindow::build_graph() {
    if (!ui->result_show->text().isEmpty()) {
        SecondWindow window_graph;
        QString str = ui->result_show->text();
        window_graph.set_str(str);
        window_graph.make_graph();
        window_graph.setModal(true);
        window_graph.exec();

    } else {
        ui->res_print->setText("ERROR: unable to plot");
    }
}

void MainWindow::make_credit_calculation() {
    Credit_calc window_credit;
    window_credit.setModal(true);
    window_credit.exec();
}

void MainWindow::make_deposit_calculation() {
    deposit_calc window_deposit;
    window_deposit.setModal(true);
    window_deposit.exec();
}
