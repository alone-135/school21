#ifndef DEPOSIT_WINDOW_TUAN_H
#define DEPOSIT_WINDOW_TUAN_H

#include <QDialog>

namespace Ui {
class deposit_window;
}

class deposit_window : public QDialog
{
    Q_OBJECT

public:
    explicit deposit_window(QWidget *parent = nullptr);
    ~deposit_window();

private slots:
    void on_pushButton_credit_clicked();

private:
    Ui::deposit_window *ui;
};

#endif // DEPOSIT_WINDOW_TUAN_H
