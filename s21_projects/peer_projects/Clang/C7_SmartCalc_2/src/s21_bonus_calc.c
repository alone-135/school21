#include "s21_calc.h"

double monthly_payment_annuitent(double S, double perc, double n) {
    double monthly_payment = 0.0;
    double i = perc/100/12;

    monthly_payment = S*((i*pow((1+i), 12*n))/(pow((1+i), 12*n) - 1));
    monthly_payment = round(monthly_payment*100)/100;

    return monthly_payment;
}

double overpayment_and_total_annuitent(double S, double n, double montly_pay, double *total) {
    *total = montly_pay*(12*n);
    double overpayment = *total - S;
    return overpayment;
}

double monthly_payment_and_overpay_difference(double S, double perc, double n, double *monthly_payment) {
    double ostatok;
    double over_pay = 0.0;

    double b = S / (n * 12);
    for (int i = 0; i < n * 12; i++) {
        ostatok = S - (b * i);
        monthly_payment[i] = b + ostatok * ((perc / 100) / 12);
        over_pay += monthly_payment[i];
    }
    return over_pay;
}

double get_deposit_perc(double P, double perc, int time, \
    double nalog, double *sum_nalog, int kap, double *final_sum,
                        int n, double sum_pop, double sum_snyat) {
    double profit = 0.0;
    P -= sum_snyat;
    P += sum_pop;
    if (kap == 0) {
        profit = (P*(perc/100)*time)/12;
        *final_sum = P;
    } else {
        profit = P*((pow(1+((perc/100)/n), n*((double)time/12)))-1);
        *final_sum = profit + P;
    }
    if (profit >= 42500) {
        *sum_nalog = nalog*0.01*profit;
        profit -= *sum_nalog;
    }
    return profit;
}

//  int main() {
//     double S = 100000;
//     double n = 2.0;
//     double perc = 5;
//     double total = 0.0;
//     double montly_pay = 0.0;

//     // montly_pay = monthly_payment_annuitent(S, perc, n);
//     // ck_assert_double_eq((int)montly_pay, 4387);
//     // double ower_pay = overpayment_and_total_annuitent(S, n, montly_pay, &total);
//     // ck_assert_int_eq((int)ower_pay, 5291);

//     double ower_pay = monthly_payment_and_overpay_difference(S, perc, n, &montly_pay);

// //  double P = 9800;
// //  double perc = 5.5;
// //  int time = 6;
// //  double nalog = 13;
// //  double sum_nalog = 0.0;
// //  double final_sum = 0.0;
// //  int n = 12;
// //  double profit = get_deposit_perc(P, perc, time, nalog, &sum_nalog, 1, &final_sum, n);
// //  printf("%lf\n", profit);
//  return 0;
// }
