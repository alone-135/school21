#ifndef CREDIT_WINDOW_TUAN_H
#define CREDIT_WINDOW_TUAN_H

#include <QDialog>

namespace Ui {
class credit_window;
}

class credit_window : public QDialog
{
    Q_OBJECT

public:
    explicit credit_window(QWidget *parent = nullptr);
    ~credit_window();

private slots:
    void on_pushButton_credit_clicked();

private:
    Ui::credit_window *ui;
};

#endif // CREDIT_WINDOW_TUAN_H
