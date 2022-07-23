#include "credit_calc.h"
#include "ui_credit_calc.h"

Credit_calc::Credit_calc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Credit_calc)
{
    ui->setupUi(this);
    setWindowTitle("Credit calc by Bail Agda");
}

Credit_calc::~Credit_calc()
{
    delete ui;
}


void Credit_calc::on_pushButton_calculate_clicked()
{
    ui->textBrowser_montly_pay->clear();
    ui->textBrowser_overpay->clear();
    ui->textBrowser_total_pay->clear();

    double sum = ui->doubleSpinBox_summ->value();
    double perc = ui->doubleSpinBox_perc->value();
    double years = ui->doubleSpinBox_years->value();
    double total = 0.0;

    if (ui->radioButton_anuitent->isChecked()) {
        double monthly_pay = monthly_payment_annuitent(sum, perc, years);
        double over_pay = overpayment_and_total_annuitent(sum, years, monthly_pay, &total);

        ui->textBrowser_montly_pay->setText(QString::number(monthly_pay, 'g', 19));
        ui->textBrowser_overpay->setText(QString::number(over_pay, 'g', 19));
        ui->textBrowser_total_pay->setText(QString::number(total, 'g', 19));

    } else if (ui->radioButton_difference->isChecked()) {

        double m_pay[(unsigned long)(years * 12)];
        double over_pay = 0.0;
        double total = 0.0;

        total = monthly_payment_and_overpay_difference(sum, perc, years, m_pay);
        over_pay = total - sum;
        for (int i = 0; i < (years*12); i++) {
            ui->textBrowser_montly_pay->setText(ui->textBrowser_montly_pay->toPlainText() + QString::number(i + 1, 'g', 19) + ": " +  QString::number(m_pay[i], 'g', 16) + "\n");
        }

        ui->textBrowser_overpay->setText(QString::number(over_pay, 'g', 19));
        ui->textBrowser_total_pay->setText(QString::number(total, 'g', 19));

    } else {
        ui->textBrowser_montly_pay->setText("Выберите тип кредита");
    }

}

