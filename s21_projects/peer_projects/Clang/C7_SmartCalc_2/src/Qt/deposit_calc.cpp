#include "deposit_calc.h"
#include "ui_deposit_calc.h"

deposit_calc::deposit_calc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deposit_calc)
{
    ui->setupUi(this);
    setWindowTitle("Deposit calc by Bail Agda");
}

deposit_calc::~deposit_calc()
{
    delete ui;
}

void deposit_calc::on_get_result_clicked()
{
    double P = ui->summa_vklada->value();
    double perc = ui->procent->value();
    double ost = ui->ostatok->value();
    int time = ui->srok_mec->value();
    double sum_snyat = ui->sum_snyat->value();
    double sum_pop = ui->sum_popoln->value();

    double sum_nalog = 0.0;
    double nalog = 13.0;
    double profit = 0.0;
    double final_sum = 0.0;
    int n = 1;
    int kap = 0;

    if (ui->nalog->value() != 0.0) {
        nalog = ui->nalog->value();
    }
    if (ui->kapitalizac->isChecked()) {
        kap = 1;
        if (ui->periodichnost->currentIndex() == 0) {
            n = 1;
        } else if(ui->periodichnost->currentIndex() == 1) {
            n = 12;
        } else {
            n = 4;
        }
    }

    if (ost >= (P - sum_snyat)) {
        ui->error_input->setText("ERROR: превышение допустимой суммы снятия");
    } else {
        ui->error_input->setText("");
        profit = get_deposit_perc(P, perc, time, nalog, &sum_nalog, kap, &final_sum, n, sum_pop, sum_snyat);

        ui->profit->cleanText();
        ui->sum_nalog->cleanText();

        ui->profit->setValue(profit);
        ui->sum_nalog->setValue(sum_nalog);
        ui->sum_v_konce->setValue(final_sum);
    }
}

