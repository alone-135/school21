#include "s21_calc.h"
#include <check.h>

START_TEST(calc_tests) {
    double res = 0.0;
    double x = 0.0;
    int err = 0;

    err = start_calc("1+((2-3", &res, &x);
    ck_assert_int_eq(err, 1);

    err = start_calc("1+2-3", &res, &x);
    ck_assert_double_eq(res, 1+2-3);

    err = start_calc("1-2*12-3^2", &res, &x);
    ck_assert_double_eq(res, -32);

    err = start_calc("sin(12)-3", &res, &x);
    ck_assert_double_eq(res, sin(12) - 3);

    err = start_calc("ln(12)^3-1*(-12+5)", &res, &x);
    ck_assert_double_eq_tol(res, pow(log(12), 3.0) - 1 * (-12 + 5), 7);

    err = start_calc("1+2-3", &res, &x);
    ck_assert_double_eq_tol(res, 1 + 2 - 3, 7);

    err = start_calc("(cos((-5)))+ln((10/(5*7))^2)-(tan(sin(-3mod2))-5mod3*4/5/7)", &res, &x);
    ck_assert_double_eq_tol(res, -0.874353, 7);

    err = start_calc("1+2-3", &res, &x);
    ck_assert_double_eq_tol(res, 1 + 2 - 3, 7);

    err = start_calc("cos(cos(12))-3-5", &res, &x);
    ck_assert_double_eq_tol(res, cos(cos(12)) - 3 - 5, 7);

    err = start_calc("sin(3^3-ln(12))-12+(-11+20)", &res, &x);
    ck_assert_double_eq_tol(res, sin(27 - log(12)) - 12 + (-11 + 20), 7);

    err = start_calc("sqrt(atan(12))", &res, &x);
    ck_assert_double_eq_tol(res, sqrt(atan(12)), 7);

    err = start_calc("asin(1)+5pow2", &res, &x);
    ck_assert_double_eq_tol(res, asin(1)+ pow(5, 2), 7);

    err = start_calc("1.2.", &res, &x);
    ck_assert_int_eq(err, 1);

    err = start_calc("xx", &res, &x);
    ck_assert_int_eq(err, 1);

    err = start_calc("ksusha", &res, &x);
    ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(bonus_tests) {
    double S = 100000;
    double n = 2.0;
    double perc = 5;
    double total = 0.0;
    double montly_pay = 0.0;

    montly_pay = monthly_payment_annuitent(S, perc, n);
    ck_assert_double_eq((int)montly_pay, 4387);
    double ower_pay = overpayment_and_total_annuitent(S, n, montly_pay, &total);
    ck_assert_int_eq((int)ower_pay, 5291);

    double m_pay[24];
    ower_pay = monthly_payment_and_overpay_difference(S, perc, n, m_pay);
    ck_assert_int_eq((int)ower_pay, 105208);
    ck_assert_int_eq((int)m_pay[0], 4583);

    S = 9800;
    int time = 6;
    double nalog = 13;
    double sum_nalog = 0.0;
    double final_sum = 0.0;
    n = 12;
    double profit = get_deposit_perc(S, perc, time, nalog, &sum_nalog, 1, &final_sum, n, 0, 0);
    ck_assert_int_eq((int)profit, 247);

    S = 98000000000;
    profit = get_deposit_perc(S, perc, time, nalog, &sum_nalog, 0, &final_sum, n, 0, 0);
    ck_assert_int_eq((int)profit, 2131500000);
}
END_TEST

int main() {
    Suite *s1 = suite_create("Core");
    TCase *s21_test = tcase_create("Test");
    SRunner *sr = srunner_create(s1);
    suite_add_tcase(s1, s21_test);

    tcase_add_test(s21_test, calc_tests);
    tcase_add_test(s21_test, bonus_tests);

    srunner_run_all(sr, CK_VERBOSE);
    int errors = srunner_ntests_failed(sr);
    srunner_free(sr);

    return errors == 0 ? 0 : 1;
}
