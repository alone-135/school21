#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "iostream"

#ifdef __cplusplus
extern "C"
{
#endif
#include "../s21_calc.h"
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
     Ui::MainWindow *ui;

private:
//     SecondWindow *graphic;
signals:
//     void signal();
private slots:
    void dig_num();
    void equal();
    void all_clean();
    void build_graph();
    void make_credit_calculation();
    void make_deposit_calculation();
};
#endif // MAINWINDOW_H
