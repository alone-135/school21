#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "credit_window.h"
#include "deposit_window.h"

bool flagSum = false;
//bool flagMult = true;
bool flagZnak = false;
bool flagScob = false;
bool flagDot = false;
bool isDigit = false;
bool isRightBracket = false;
bool isLeftBracket = false;
bool flagRes = false;
bool firstZnak = false;
int checkCountScob = 0;
int is_x = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //block one
    connect(ui->pushButton_0,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_righScobka,SIGNAL(clicked()), this, SLOT(helpRightOperator()));
    connect(ui->pushButton_lSCobka,SIGNAL(clicked()), this, SLOT(helpLeftOperator()));

// blockOperators
   connect(ui->pushButton_Clear,SIGNAL(clicked()), this, SLOT(clearButton()));
   connect(ui->pushButton_mod,SIGNAL(clicked()), this, SLOT(operationsMult()));
   connect(ui->pushButton_plus,SIGNAL(clicked()), this, SLOT(operationsSum()));
   connect(ui->pushButton_minus,SIGNAL(clicked()), this, SLOT(operationsSum()));
   connect(ui->pushButton_ymnozit,SIGNAL(clicked()), this, SLOT(operationsMult()));
   connect(ui->pushButton_delit,SIGNAL(clicked()), this, SLOT(operationsMult()));
   connect(ui->pushButton_stepen,SIGNAL(clicked()), this, SLOT(operationsMult()));
   //bloc math
   connect(ui->pushButton_in,SIGNAL(clicked()), this, SLOT(mathFunction()));
   connect(ui->pushButton_sqrt,SIGNAL(clicked()), this, SLOT(mathFunction()));
   connect(ui->pushButton_sin,SIGNAL(clicked()), this, SLOT(mathFunction()));
   connect(ui->pushButton_asin,SIGNAL(clicked()), this, SLOT(mathFunction()));
   connect(ui->pushButton_cos,SIGNAL(clicked()), this, SLOT(mathFunction()));
   connect(ui->pushButton_acos,SIGNAL(clicked()), this, SLOT(mathFunction()));
   connect(ui->pushButton_tan,SIGNAL(clicked()), this, SLOT(mathFunction()));
   connect(ui->pushButton_atan,SIGNAL(clicked()), this, SLOT(mathFunction()));
   connect(ui->pushButton_log,SIGNAL(clicked()), this, SLOT(mathFunction()));


    //block border

    //     connect(ui->pushButton_dot,SIGNAL(clicked()), this, SLOT(digits_numbers()));
   ui->pushButton_plus->setCheckable(true);
   ui->pushButton_minus->setCheckable(true);
   ui->pushButton_ymnozit->setCheckable(true);
   ui->pushButton_delit->setCheckable(true);
   ui->pushButton_stepen->setCheckable(true);
//
   //
   //
   //
   //
   //
   h = 0.1;
   xBegin = -3;
   xEnd = 3 +h;

   ui->widget->xAxis->setRange(-10,10);
   ui->widget->yAxis->setRange(0,10);

   for (X = xBegin; X <= xEnd; X+= h) {
        x.push_back(X);
        y.push_back(X*X);
   }

   ui->widget->addGraph();
   ui->widget->graph(0)->addData(x,y);
   ui->widget->replot();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digits_numbers() {
    if (flagRes == true) {
        ui->label->clear();
        flagRes = false;
    }
    if (isRightBracket == false) {
        QPushButton *button = (QPushButton *)sender();
        QString newlabel;
        ui->label->setText(ui->label->text() + button->text());
        flagZnak = false;
//        flagSum = false;
//        flagMult = false;
        flagScob = true;
        isDigit = true;
        isLeftBracket = true;
        firstZnak = true;
    }
}

void MainWindow::on_pushButton_dot_clicked()
{
     QPushButton *button = (QPushButton *)sender();
     if (flagDot == false && isDigit == true && isRightBracket == false) {
        ui->label->setText(ui->label->text() + button->text());
        flagDot = true;
        isDigit = false;

     }
}

void MainWindow::operationsSum() {
    QPushButton *button = (QPushButton *)sender();
    if (/*flagSum == false*/ (flagZnak == false && isDigit == true) || firstZnak == false || flagSum == true) {
        ui->label->setText(ui->label->text() + button->text());
        flagZnak = true;
        flagDot = false;
        isDigit = false;
        isRightBracket = false;
        isLeftBracket = false;
        firstZnak = true;
        flagSum = false;
    }


}

void MainWindow::operationsMult() {
    QPushButton *button = (QPushButton *)sender();


    if (/*flagMult == false*/flagZnak == false && flagDot == false && isDigit == true) {
        ui->label->setText(ui->label->text() + button->text());
        flagZnak = true;
        isLeftBracket = false;
//        flagMult = true;
//        flagSum = true;
        flagDot = false;
        isDigit = false;
        isRightBracket = false;
     }



}

void MainWindow::helpLeftOperator() {
    QPushButton *button = (QPushButton *)sender();
    //скобки
    if(checkCountScob >= 0 && !isDigit &&  flagDot == false) {
        ui->label->setText(ui->label->text() + button->text());
        flagScob = true;
        flagZnak = false;
        isDigit = false;
        isLeftBracket = true;
        checkCountScob++;
    }
}


void MainWindow::helpRightOperator() {
    QPushButton *button = (QPushButton *)sender();
    if (flagScob == true && checkCountScob > 0 && isLeftBracket == true && flagZnak == false) {
        ui->label->setText(ui->label->text() + button->text());
        checkCountScob--;
        isRightBracket = true;
    }
//    if (checkCountScob == 0) {
//        flagScob = false;
//        isDigit = false;
//    }
}

void MainWindow:: clearButton() {
    ui->label->clear();
    flagSum = false;
    //bool flagMult = true;
    flagZnak = false;
    flagScob = false;
    flagDot = false;
    isDigit = false;
    isRightBracket = false;
    isLeftBracket = false;
    flagRes = false;
    firstZnak = false;
    checkCountScob = 0;
    is_x = 1;
}


void MainWindow::mathFunction() {
    QPushButton *button = (QPushButton *)sender();
    if(flagZnak == true || firstZnak == false) {
        ui->label->setText(ui->label->text() + button->text());
        flagScob = true;
        isLeftBracket = true;
        isDigit = false;
        firstZnak = true;
        flagSum = true;
        checkCountScob++;
    }
}

void MainWindow::on_pushButton_Graph_clicked()
{
    QString send = ui->label->text();
    QByteArray ba = send.toLocal8Bit();
    char* buf = ba.data();
    ui->widget->clearGraphs();
    x.clear();
    y.clear();
    result_1 = 0;
    result_2 = 0;
    xBegin = 0;
    xEnd = 0;
    h = 0.1;

    double Y = ui->x_value->text().toDouble();
    double X = 0;
    if (Y == 0) Y = 1;

    xy_1 = ui->x1->text().toDouble();
    xy_2 = ui->x2->text().toDouble();
    result_1 = ui->y1->text().toInt();
    result_2 = ui->y2->text().toInt();

    xBegin = result_2;
    xEnd = result_1 + h;

    ui->widget->xAxis->setRange(xy_2, xy_1);
    ui->widget->yAxis->setRange(result_2, result_1);
    N = (xEnd - xBegin)/h + 2;

    for (X = xBegin; X <= xEnd; X+=h) {
        x.push_back(X);
        y.push_back(s21_parsing(buf, Y*X));
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}

void MainWindow::on_pushButton_ravno_clicked(){
    double x = 0;
    QPushButton *button = (QPushButton *)sender();
    button->setChecked(true);
    QString send = ui->label->text();
    QByteArray ba = send.toLocal8Bit();
    char* buf = ba.data();

    if (ui->x_value->text() != "") {
        x = (ui->x_value->text().toDouble());
    }
    QString toStr = QString::number(s21_parsing(buf, x), 'g', 15);
    ui->label->setText(toStr);
    flagSum = false;
    //bool flagMult = true;
    flagZnak = false;
    flagScob = false;
    flagDot = false;
    isDigit = false;
    isRightBracket = false;
    isLeftBracket = false;
    flagRes = false;
    firstZnak = false;
    checkCountScob = 0;
    is_x = 1;
}


void MainWindow::on_pushButton_x_clicked()
{
    int loc_falg = 1;
    if (ui->label->text() == '0') {
        ui->label->setText("");
        loc_falg = 0;
    }
    if ((isDigit == true) && loc_falg == 1) {
        ui->label->setText(ui->label->text() + "*x");
    } else {
       ui->label->setText(ui->label->text() + "x");
    }
//    flag = 0;
//    min_flag = 0;
//    pl_falg = 0;
//    is_digit = 0;
//    is_r_bracket = 1;
//    is_sign = 1;
//    is_x = 0;
}

void MainWindow::on_pushButton_clicked()
{
    credit_window window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_pushButton_10_clicked()
{
    deposit_window window;
    window.setModal(true);
    window.exec();
}

