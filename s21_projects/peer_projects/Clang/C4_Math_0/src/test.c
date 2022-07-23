#include <check.h>
#include <limits.h>
#include <math.h>

#include "s21_math.h"

////////////////    s21_abs
START_TEST(s21_abs_test1) {
    int number = 0;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test2) {
    int number = -1;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test3) {
    int number = 1;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test4) {
    int number = 33;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test5) {
    int number = -33;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test6) {
    int number = INT_MAX;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test7) {
    int number = INT_MIN;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test8) {
    int number = -5555;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test9) {
    int number = -0;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test10) {
    int number = 1234567;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test11) {
    int number = -1234567;
    ck_assert_int_eq(s21_abs(number), abs(number));
}
END_TEST

START_TEST(s21_abs_test12) { ck_assert_int_eq(abs(-10), s21_abs(-10)); }
END_TEST

START_TEST(s21_abs_test13) { ck_assert_int_eq(abs(7895), s21_abs(7895)); }
END_TEST

START_TEST(s21_abs_test14) { ck_assert_int_eq(abs(-10101), s21_abs(-10101)); }
END_TEST

START_TEST(s21_abs_test15) { ck_assert_int_eq(abs(10101), s21_abs(10101)); }
END_TEST

START_TEST(s21_abs_test16) {
    for (int i = -128; i <= 127; i++) ck_assert_int_eq(abs(i), s21_abs(i));
}
END_TEST
///////////////

//////////////  s21_exp
START_TEST(s21_exp_test1) {
    double number = 0.0;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test2) {
    double number = -0.0;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test3) {
    double number = 1.0;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test4) {
    double number = 1.1111;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test5) {
    double number = -1.1111;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test6) {
    double number = 10;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test7) {
    double number = -10;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test8) {
    double number = -1.9999999;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test9) {
    double number = 1.9999999;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test10) {
    double number = -0.9999999;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test11) {
    double number = 0.9999999;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test12) {
    ck_assert_ldouble_nan(s21_exp(S21_NAN_VAL));
    ck_assert_double_nan(exp(S21_NAN_VAL));
}
END_TEST

START_TEST(s21_exp_test13) {
    ck_assert_ldouble_infinite(s21_exp(S21_HUGE_VAL));
    ck_assert_double_infinite(exp(S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_exp_test14) {
    ck_assert_ldouble_eq(s21_exp(-S21_HUGE_VAL), 0.0);
    ck_assert_ldouble_eq(exp(-S21_HUGE_VAL), 0.0);
}
END_TEST

START_TEST(s21_exp_test15) {
    double number = 5.5;
    ck_assert_ldouble_eq_tol(s21_exp(number), (long double)exp(number), EPS1);
}
END_TEST

START_TEST(s21_exp_test16) {
    ck_assert_double_eq_tol(s21_exp(3.3333), s21_exp(3.3333), EPS1);
}
END_TEST

START_TEST(s21_exp_test17) {
    ck_assert_double_eq_tol(s21_exp(-5.5), s21_exp(-5.5), EPS1);
}
END_TEST

START_TEST(s21_exp_test18) {
    ck_assert_double_eq(s21_exp(4566.7899), s21_exp(4566.7899));
}
END_TEST

START_TEST(s21_exp_test19) { ck_assert_double_nan(s21_exp(NAN)); }
END_TEST

START_TEST(s21_exp_test20) {
    ck_assert_double_eq(exp(INFINITY), s21_exp(INFINITY));
}
END_TEST

START_TEST(s21_exp_test21) {
    ck_assert_double_eq_tol(exp(0.4564), s21_exp(0.4564), EPS1);
}
END_TEST

START_TEST(s21_exp_test22) { ck_assert_double_eq(exp(0), s21_exp(0)); }
END_TEST

START_TEST(s21_exp_test23) {
    ck_assert_double_eq_tol(exp(-45.11), s21_exp(-45.11), EPS1);
}
END_TEST

START_TEST(s21_exp_test24) {
    ck_assert_double_eq_tol(exp(-1), s21_exp(-1), EPS1);
}
END_TEST

START_TEST(s21_exp_test25) {
    ck_assert_double_eq_tol(exp(-0.000001), s21_exp(-0.000001), EPS1);
}
END_TEST

START_TEST(s21_exp_test26) {
    for (double i = -2.7863; i <= 2.6831; i += 0.001)
        ck_assert_double_eq_tol(exp(i), s21_exp(i), EPS1);
}
END_TEST
///////////////

//////////////  pow
START_TEST(s21_pow_test1) {
    double res1 = pow(2, 3);
    long double res2 = s21_pow(2, 3);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test2) {
    double res1 = pow(0, 0);
    long double res2 = s21_pow(0, 0);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test3) {
    double res1 = pow(3, -1);
    long double res2 = s21_pow(3, -1);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test4) {
    double res1 = pow(-5, 5);
    long double res2 = s21_pow(-5, 5);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test5) {
    long double res1 = pow(0.352342, 7);
    long double res2 = s21_pow(0.352342, 7);
    ck_assert_ldouble_eq_tol(res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test6) {
    double res1 = pow(0.5, 1.245);
    long double res2 = s21_pow(0.5, 1.245);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test7) {
    double res1 = pow(0.99999, 0.99999);
    long double res2 = s21_pow(0.99999, 0.99999);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test8) {
    double res1 = pow(99, -0.99999);
    long double res2 = s21_pow(99, -0.99999);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test9) {
    double res1 = pow(99, -0.0001);
    long double res2 = s21_pow(99, -0.0001);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test10) {
    double res1 = pow(1, 10.000199999);
    long double res2 = s21_pow(1, 10.000199999);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test11) {
    double res1 = pow(1.0001, 10.000199999);
    long double res2 = s21_pow(1.0001, 10.000199999);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test12) {
    double res1 = pow(1.0001, -10.000199999);
    long double res2 = s21_pow(1.0001, -10.000199999);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test13) {
    double res1 = pow(-1.0001, -10.100199999);
    long double res2 = s21_pow(-1.0001, -10.100199999);
    ck_assert_ldouble_nan((long double)res1);
    ck_assert_ldouble_nan(res2);
}
END_TEST

START_TEST(s21_pow_test14) {
    double res1 = pow(S21_HUGE_VAL, -S21_HUGE_VAL);
    long double res2 = s21_pow(S21_HUGE_VAL, -S21_HUGE_VAL);
    ck_assert_ldouble_eq_tol(res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test15) {
    double res1 = pow(-12.5, 5);
    long double res2 = s21_pow(-12.5, 5);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test16) {
    double res1 = pow(-12.5, 6);
    long double res2 = s21_pow(-12.5, 6);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test17) {
    double res1 = pow(0.0, 6);
    long double res2 = s21_pow(0.0, 6);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test18) {
    double res1 = pow(S21_HUGE_VAL, -2);
    long double res2 = s21_pow(S21_HUGE_VAL, -2);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST

START_TEST(s21_pow_test19) {
    ck_assert_double_eq_tol(pow(0.3123, 0.789456), s21_pow(0.3123, 0.789456),
                            1e-6);
}
END_TEST

START_TEST(s21_pow_test20) {
    ck_assert_double_eq_tol(pow(56.3, 0.3), s21_pow(56.3, 0.3), 1e-6);
}
END_TEST

START_TEST(s21_pow_test21) { ck_assert_double_eq(pow(1, 0), s21_pow(1, 0)); }
END_TEST

START_TEST(s21_pow_test22) { ck_assert_double_eq(pow(-1, 3), s21_pow(-1, 3)); }
END_TEST

START_TEST(s21_pow_test23) {
    ck_assert_double_eq(pow(-INFINITY, 3), s21_pow(-S21_HUGE_VAL, 3));
}
END_TEST

START_TEST(s21_pow_test24) { ck_assert_double_eq(pow(0, 0), s21_pow(0, 0)); }
END_TEST

START_TEST(s21_pow_test25) { ck_assert_double_eq(pow(0, -1), s21_pow(0, -1)); }
END_TEST

START_TEST(s21_pow_test26) { ck_assert_double_eq(pow(0, 1), s21_pow(0, 1)); }
END_TEST

START_TEST(s21_pow_test27) {
    ck_assert_double_eq(pow(INFINITY, 0), s21_pow(S21_HUGE_VAL, 0));
}
END_TEST

START_TEST(s21_pow_test28) {
    ck_assert_double_eq(pow(INFINITY, -1), s21_pow(S21_HUGE_VAL, -1));
}
END_TEST

START_TEST(s21_pow_test29) { ck_assert_double_nan(s21_pow(0, S21_NAN_VAL)); }
END_TEST

START_TEST(s21_pow_test30) {
    ck_assert_double_nan(s21_pow(S21_NAN_VAL, S21_NAN_VAL));
}
END_TEST

START_TEST(s21_pow_test31) {
    ck_assert_double_eq(pow(INFINITY, INFINITY),
                        s21_pow(S21_HUGE_VAL, S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_pow_test32) {
    ck_assert_double_nan(s21_pow(S21_NAN_VAL, S21_HUGE_VAL));
}
END_TEST

// START_TEST(s21_pow_test33) {
//     ck_assert_double_nan(s21_pow(S21_HUGE_VAL, S21_NAN_VAL));
// }
END_TEST

START_TEST(s21_pow_test34) {
    ck_assert_double_nan(s21_pow(S21_NAN_VAL, -S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_pow_test35) {
    ck_assert_double_nan(s21_pow(-S21_HUGE_VAL, S21_NAN_VAL));
}
END_TEST

START_TEST(s21_pow_test36) {
    ck_assert_double_eq(pow(2, INFINITY), s21_pow(2, S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_pow_test37) {
    ck_assert_double_nan(s21_pow(-0.789456, -0.789456));
}
END_TEST

START_TEST(s21_pow_test38) {
    ck_assert_double_nan(s21_pow(-500.789456, -10.1354323));
}
END_TEST

START_TEST(s21_pow_test39) {
    ck_assert_double_nan(s21_pow(-500.789456, 34.13));
}
END_TEST

START_TEST(s21_pow_test40) {
    ck_assert_double_eq_tol(pow(10.789456, 3.13), s21_pow(10.789456, 3.13),
                            1e-2);
}
END_TEST

START_TEST(s21_pow_test41) {
    ck_assert_double_eq_tol(pow(-1, -S21_HUGE_VAL), s21_pow(-1, -S21_HUGE_VAL),
                            EPS1);
}
END_TEST

START_TEST(s21_pow_test42) {
    ck_assert_double_eq_tol(pow(0, S21_HUGE_VAL), s21_pow(0, S21_HUGE_VAL),
                            EPS1);
}
END_TEST

START_TEST(s21_pow_test43) {
    double res1 = pow(-S21_HUGE_VAL, -2);
    long double res2 = s21_pow(-S21_HUGE_VAL, -2);
    ck_assert_ldouble_eq_tol((long double)res1, res2, EPS1);
}
END_TEST
/////

//  cos
START_TEST(s21_cos_test1) {
    for (int R = 20; R >= -20; R -= 4)
        for (double k = 2 * S21_M_PI; k > -2 * S21_M_PI; k -= S21_M_PI / 9)
            ck_assert_ldouble_eq_tol(cos(k + R * S21_M_PI),
                                     s21_cos(k + R * S21_M_PI), EPS1);
}
END_TEST

START_TEST(s21_cos_test2) {
    for (int R = 20; R >= -20; R -= 2)
        for (double k = 2 * S21_M_PI; k > -2 * S21_M_PI; k -= S21_M_PI / 6)
            ck_assert_ldouble_eq_tol(cos(k + R * S21_M_PI),
                                     s21_cos(k + R * S21_M_PI), EPS1);
}
END_TEST

START_TEST(s21_cos_test3) {
    ck_assert_ldouble_eq_tol(cos(0.0), s21_cos(0.0), EPS1);
}
END_TEST

START_TEST(s21_cos_test4) {
    ck_assert_ldouble_eq_tol(cos(S21_M_PI2), s21_cos(S21_M_PI2), EPS1);
}
END_TEST

START_TEST(s21_cos_test5) {
    ck_assert_ldouble_eq_tol(cos(3 * S21_M_PI2), s21_cos(3 * S21_M_PI2), EPS1);
}
END_TEST

START_TEST(s21_cos_test6) {
    ck_assert_ldouble_eq_tol(cos(2 * S21_M_PI2), s21_cos(2 * S21_M_PI2), EPS1);
}
END_TEST

START_TEST(s21_cos_test7) {
    ck_assert_ldouble_eq_tol(cos(-2 * S21_M_PI2), s21_cos(-2 * S21_M_PI2),
                             EPS1);
}
END_TEST

START_TEST(s21_cos_test8) {
    ck_assert_ldouble_eq_tol(cos(-S21_M_PI), s21_cos(-S21_M_PI), EPS1);
}
END_TEST

START_TEST(s21_cos_test9) {
    ck_assert_ldouble_eq_tol(cos(-0.0), s21_cos(-0.0), EPS1);
}
END_TEST

START_TEST(s21_cos_test10) {
    ck_assert_ldouble_eq_tol(cos(12415.12415), s21_cos(12415.12415), EPS1);
}
END_TEST

START_TEST(s21_cos_test11) {
    ck_assert_ldouble_eq_tol(cos(-124345.9999), s21_cos(-124345.9999), EPS1);
}
END_TEST

START_TEST(s21_cos_test12) {
    ck_assert_ldouble_eq_tol(cos(11.010101), s21_cos(11.010101), EPS1);
}
END_TEST

START_TEST(s21_cos_test13) { ck_assert_ldouble_nan(s21_cos(S21_HUGE_VAL)); }
END_TEST

START_TEST(s21_cos_test14) { ck_assert_ldouble_nan(s21_cos(-S21_HUGE_VAL)); }
END_TEST

START_TEST(s21_cos_test15) { ck_assert_ldouble_nan(s21_cos(S21_NAN_VAL)); }
END_TEST

START_TEST(s21_cos_test16) {
    for (double i = -1.000000; i <= 1.000000; i += 0.00001)
        ck_assert_double_eq_tol(cos(i), s21_cos(i), EPS1);
}
END_TEST

START_TEST(s21_cos_test17) { ck_assert_double_nan(s21_cos(S21_NAN_VAL)); }
END_TEST

START_TEST(s21_cos_test18) { ck_assert_double_nan(s21_cos(-S21_HUGE_VAL)); }
END_TEST

START_TEST(s21_cos_test19) { ck_assert_double_nan(s21_cos(S21_HUGE_VAL)); }
END_TEST

START_TEST(s21_cos_test20) {
    for (double i = -223.654; i <= 148.522; i += 2.456)
        ck_assert_double_eq_tol(cos(i), s21_cos(i), EPS1);
}
END_TEST

START_TEST(s21_cos_test21) { ck_assert_double_nan(s21_cos(-0.0 / 0.0)); }
END_TEST

START_TEST(s21_cos_test22) {
    for (double i = -10009.6; i <= -9808.0; i += 0.1)
        ck_assert_double_eq_tol(cos(i), s21_cos(i), EPS1);
}
END_TEST

START_TEST(s21_cos_test23) {
    for (double i = 9809.6; i <= 10890.0; i += 0.1)
        ck_assert_double_eq_tol(cos(i), s21_cos(i), EPS1);
}
END_TEST
/////

//  tan
START_TEST(s21_tan_test1) {
    ck_assert_ldouble_eq_tol(tan(0.123456), s21_tan(0.123456), EPS1);
}
END_TEST

START_TEST(s21_tan_test2) { ck_assert_ldouble_nan(s21_tan(S21_NAN_VAL)); }
END_TEST

START_TEST(s21_tan_test3) { ck_assert_ldouble_nan(s21_tan(S21_HUGE_VAL)); }
END_TEST

START_TEST(s21_tan_test4) { ck_assert_ldouble_nan(s21_tan(-S21_HUGE_VAL)); }
END_TEST

START_TEST(s21_tan_test5) {
    ck_assert_ldouble_eq_tol(tan(-0.123456), s21_tan(-0.123456), EPS1);
}
END_TEST

START_TEST(s21_tan_test6) {
    ck_assert_ldouble_eq_tol(tan(11115.123456), s21_tan(11115.123456), EPS1);
}
END_TEST

START_TEST(s21_tan_test7) {
    ck_assert_ldouble_eq_tol(tan(-11115.123456), s21_tan(-11115.123456), EPS1);
}
END_TEST

START_TEST(s21_tan_test8) {
    ck_assert_ldouble_eq_tol(tan(0.000001), s21_tan(0.000001), EPS1);
}
END_TEST

START_TEST(s21_tan_test9) {
    ck_assert_ldouble_eq_tol(tan(-0.0), s21_tan(-0.0), EPS1);
}
END_TEST

START_TEST(s21_tan_test10) { ck_assert_ldouble_nan(s21_tan(-0.0 / 0.0)); }
END_TEST

START_TEST(s21_tan_test11) {
    for (double i = 1.0; i >= -1.0; i -= 0.0001)
        ck_assert_ldouble_eq_tol(tan(i), s21_tan(i), EPS1);
}
END_TEST
/////

//  s21_abs
START_TEST(s21_abs_func) {
    ck_assert_double_eq(s21_abs(-135), abs(-135));
    ck_assert_double_eq(s21_abs(321), abs(321));
}
END_TEST

//  s21_fabs
START_TEST(s21_fabs_func) {
    ck_assert_double_eq(s21_fabs(-135.234), fabs(-135.234));
    ck_assert_double_eq(s21_fabs(321.234), fabs(321.234));
}
END_TEST

//  s21_sqrt
START_TEST(s21_sqrt_func) {
    ck_assert_double_nan(s21_sqrt(s21_NAN));
    ck_assert_double_nan(sqrt(s21_NAN));
    ck_assert_double_infinite(s21_sqrt(s21_INF));
    ck_assert_double_infinite(sqrt(s21_INF));
    ck_assert_double_eq(s21_sqrt(0), sqrt(0));
    ck_assert_int_eq(s21_sqrt(-1), sqrt(-1));
    ck_assert_double_eq(s21_sqrt(1234.4321), sqrt(1234.4321));
    ck_assert_double_eq(s21_sqrt(90000000000), sqrt(90000000000));
}
END_TEST

//  s21_log
START_TEST(s21_log_func) {
    ck_assert_ldouble_eq_tol(s21_log(1234.1234), log(1234.1234), EPS1);
    ck_assert_int_eq(s21_log(s21_NAN), log(s21_NAN));
    ck_assert_double_eq(s21_log(s21_INF), log(s21_INF));
    ck_assert_double_eq(s21_log(90000000000), log(90000000000));
    ck_assert_double_eq(s21_log(0), log(0));
    ck_assert_double_eq(s21_log(1), log(1));
    ck_assert_double_nan(s21_log(-2342421));
    ck_assert_double_nan(log(-2342421));
}
END_TEST

//  s21_exp
START_TEST(s21_exp_func) {
    ck_assert_int_eq(s21_exp(s21_NAN), exp(s21_NAN));
    ck_assert_double_eq(s21_exp(s21_INF), exp(s21_INF));
    ck_assert_double_eq(s21_exp(0), exp(0));
    ck_assert_double_eq(s21_exp(1), exp(1));
    ck_assert_double_eq(s21_exp(5), exp(5));
}
END_TEST

//  s21_ceil
START_TEST(s21_ceil_func) {
    ck_assert_double_nan(s21_ceil(s21_NAN));
    ck_assert_double_nan(ceil(s21_NAN));
    ck_assert_double_eq(s21_ceil(s21_INF), ceil(s21_INF));
    ck_assert_double_eq(s21_ceil(0), ceil(0));
    ck_assert_double_eq(s21_ceil(123.3), ceil(123.3));
    ck_assert_double_eq(s21_ceil(-123.3), ceil(-123.3));
}
END_TEST

//  s21_sin
START_TEST(s21_sin_func) {
    ck_assert_double_nan(s21_sin(s21_NAN));
    ck_assert_double_nan(sin(s21_NAN));
    ck_assert_double_nan(s21_sin(s21_INF));
    ck_assert_double_nan(sin(s21_INF));
    ck_assert_double_eq(s21_sin(0), sin(0));
    ck_assert_double_eq(s21_sin(0.5), sin(0.5));
    ck_assert_double_eq(s21_sin(-0.5), sin(-0.5));
    ck_assert_double_eq(s21_sin(-1), sin(-1));
    ck_assert_double_eq(s21_sin(1), sin(1));
    ck_assert_double_eq_tol(s21_sin(7), sin(7), EPS1);
    ck_assert_double_eq_tol(s21_sin(-10), sin(-10), EPS1);
}
END_TEST

//  s21_cos
START_TEST(s21_cos_func) {
    ck_assert_double_nan(s21_cos(s21_NAN));
    ck_assert_double_nan(cos(s21_NAN));
    ck_assert_double_nan(s21_cos(s21_INF));
    ck_assert_double_nan(cos(s21_INF));
    ck_assert_double_eq_tol(s21_cos(0), cos(0), EPS1);
    ck_assert_double_eq_tol(s21_cos(0.5), cos(0.5), EPS1);
    ck_assert_double_eq_tol(s21_cos(-0.5), cos(-0.5), EPS1);
    ck_assert_double_eq_tol(s21_cos(-1), cos(-1), EPS1);
    ck_assert_double_eq_tol(s21_cos(1), cos(1), EPS1);
    ck_assert_double_eq_tol(s21_cos(7), cos(7), EPS1);
}
END_TEST

//  s21_tan
START_TEST(s21_tan_func) {
    ck_assert_double_nan(s21_tan(s21_NAN));
    ck_assert_double_nan(tan(s21_NAN));
    ck_assert_double_nan(s21_tan(s21_INF));
    ck_assert_double_nan(tan(s21_INF));
    ck_assert_double_eq_tol(s21_tan(0), tan(0), EPS1);
    ck_assert_double_eq_tol(s21_tan(0.5), tan(0.5), EPS1);
    ck_assert_double_eq_tol(s21_tan(-0.5), tan(-0.5), EPS1);
    ck_assert_double_eq_tol(s21_tan(-1), tan(-1), EPS1);
    ck_assert_double_eq_tol(s21_tan(1), tan(1), EPS1);
    ck_assert_double_eq_tol(s21_tan(7), tan(7), EPS1);
}
END_TEST

//  s21_asin
START_TEST(s21_asin_func) {
    ck_assert_double_nan(s21_asin(s21_NAN));
    ck_assert_double_nan(asin(s21_NAN));
    ck_assert_double_nan(s21_asin(s21_INF));
    ck_assert_double_nan(asin(s21_INF));
    ck_assert_double_eq_tol(s21_asin(0), asin(0), 1e-7);
    ck_assert_double_eq_tol(s21_asin(0.5), asin(0.5), 1e-7);
    ck_assert_double_eq_tol(s21_asin(-0.5), asin(-0.5), 1e-7);
    ck_assert_double_eq_tol(s21_asin(-1), asin(-1), 1e-7);
    ck_assert_double_eq_tol(s21_asin(1), asin(1), 1e-7);
    ck_assert_double_nan(s21_asin(7));
    ck_assert_double_nan(asin(7));
}
END_TEST

//  s21_acos
START_TEST(s21_acos_func) {
    ck_assert_double_nan(s21_acos(s21_NAN));
    ck_assert_double_nan(acos(s21_NAN));
    ck_assert_double_nan(s21_acos(s21_INF));
    ck_assert_double_nan(acos(s21_INF));
    ck_assert_double_eq_tol(s21_acos(0), acos(0), 1e-7);
    ck_assert_double_eq_tol(s21_acos(0.5), acos(0.5), 1e-7);
    ck_assert_double_eq_tol(s21_acos(-0.5), acos(-0.5), 1e-7);
    ck_assert_double_eq_tol(s21_acos(-1), acos(-1), 1e-7);
    ck_assert_double_eq_tol(s21_acos(1), acos(1), 1e-7);
    ck_assert_double_nan(s21_acos(7));
    ck_assert_double_nan(acos(7));
}
END_TEST

//  s21_atan
START_TEST(s21_atan_func) {
    ck_assert_double_nan(s21_atan(s21_NAN));
    ck_assert_double_eq_tol(s21_atan(s21_INF), atan(s21_INF), 1e-7);
    ck_assert_double_eq_tol(s21_atan(-1 * s21_INF), atan(-1 * s21_INF), 1e-7);
    ck_assert_double_eq_tol(s21_atan(0), atan(0), 1e-7);
    ck_assert_double_eq_tol(s21_atan(0.5), atan(0.5), 1e-7);
    ck_assert_double_eq_tol(s21_atan(-0.5), atan(-0.5), 1e-7);
    ck_assert_double_eq_tol(s21_atan(-1), atan(-1), 1e-7);
    ck_assert_double_eq_tol(s21_atan(1), atan(1), 1e-7);
    ck_assert_double_eq_tol(s21_atan(7), atan(7), 1e-7);
}
END_TEST
//////

//  fmod
START_TEST(s21_fmod_test1) {
    ck_assert_ldouble_eq_tol(fmod(12345, 12.234), s21_fmod(12345, 12.234),
                             EPS1);
}
END_TEST

START_TEST(s21_fmod_test2) {
    ck_assert_ldouble_eq_tol(fmod(0.0, 0.0001), s21_fmod(0.0, 0001), EPS1);
}
END_TEST

START_TEST(s21_fmod_test3) { ck_assert_ldouble_nan(s21_fmod(0.0, 0.0)); }
END_TEST

START_TEST(s21_fmod_test4) {
    ck_assert_ldouble_eq_tol(fmod(-2834.242, 11.2), s21_fmod(-2834.242, 11.2),
                             EPS1);
}
END_TEST

START_TEST(s21_fmod_test5) {
    ck_assert_ldouble_eq_tol(fmod(4, 2), s21_fmod(4, 2), EPS1);
}
END_TEST

START_TEST(s21_fmod_test6) { ck_assert_ldouble_nan(s21_fmod(-10, 0)); }
END_TEST

START_TEST(s21_fmod_test7) {
    ck_assert_ldouble_eq_tol(fmod(-1, S21_HUGE_VAL), s21_fmod(-1, S21_HUGE_VAL),
                             EPS1);
}
END_TEST

START_TEST(s21_fmod_test8) {
    ck_assert_ldouble_eq_tol(fmod(121, 11.0001), s21_fmod(121, 11.0001), EPS1);
}
END_TEST

START_TEST(s21_fmod_test9) {
    ck_assert_ldouble_eq_tol(fmod(1244.12414, 1244), s21_fmod(1244.12414, 1244),
                             EPS1);
}
END_TEST

START_TEST(s21_fmod_test10) {
    ck_assert_ldouble_eq_tol(fmod(1.21, -0.99999), s21_fmod(1.21, -0.99999),
                             EPS1);
}
END_TEST

START_TEST(s21_fmod_test11) {
    ck_assert_ldouble_eq_tol(fmod(1.21, 124214141), s21_fmod(1.21, 124214141),
                             EPS1);
}
END_TEST

START_TEST(s21_fmod_test12) { ck_assert_double_nan(fmod(1, 0)); }
END_TEST

START_TEST(s21_fmod_test13) { ck_assert_double_nan(s21_fmod(1, 0)); }
END_TEST

START_TEST(s21_fmod_test14) {
    ck_assert_double_eq(fmod(0, -1), s21_fmod(0, -1));
}
END_TEST

START_TEST(s21_fmod_test15) { ck_assert_double_eq(fmod(0, 1), s21_fmod(0, 1)); }
END_TEST

START_TEST(s21_fmod_test16) { ck_assert_double_nan(fmod(S21_HUGE_VAL, -1)); }
END_TEST

START_TEST(s21_fmod_test17) {
    ck_assert_double_nan(s21_fmod(S21_HUGE_VAL, -1));
}
END_TEST

START_TEST(s21_fmod_test18) {
    ck_assert_double_eq(fmod(-1, -S21_HUGE_VAL), s21_fmod(-1, -S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_fmod_test19) {
    ck_assert_double_eq(fmod(0, S21_HUGE_VAL), s21_fmod(0, S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_fmod_test21) { ck_assert_double_nan(fmod(0, S21_NAN_VAL)); }
END_TEST

START_TEST(s21_fmod_test22) {
    ck_assert_double_nan(s21_fmod(S21_NAN_VAL, S21_NAN_VAL));
}
END_TEST

START_TEST(s21_fmod_test23) {
    ck_assert_double_nan(fmod(S21_NAN_VAL, S21_NAN_VAL));
}
END_TEST

START_TEST(s21_fmod_test24) {
    ck_assert_double_nan(s21_fmod(S21_NAN_VAL, S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_fmod_test25) {
    ck_assert_double_nan(s21_fmod(S21_HUGE_VAL, S21_NAN_VAL));
}
END_TEST

START_TEST(s21_fmod_test26) {
    ck_assert_double_nan(s21_fmod(S21_NAN_VAL, -S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_fmod_test27) {
    ck_assert_double_nan(s21_fmod(-S21_HUGE_VAL, S21_NAN_VAL));
}
END_TEST

START_TEST(s21_fmod_test28) {
    ck_assert_double_nan(fmod(S21_NAN_VAL, S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_fmod_test29) {
    ck_assert_double_nan(fmod(S21_HUGE_VAL, S21_NAN_VAL));
}
END_TEST

START_TEST(s21_fmod_test30) {
    ck_assert_double_nan(fmod(S21_NAN_VAL, -S21_HUGE_VAL));
}
END_TEST

START_TEST(s21_fmod_test31) {
    ck_assert_double_nan(fmod(-S21_HUGE_VAL, S21_NAN_VAL));
}
END_TEST
/////////

int main() {
    Suite *s = suite_create("Core");
    TCase *tc = tcase_create("Core");
    SRunner *sr = srunner_create(s);

    suite_add_tcase(s, tc);

    //  abs
    tcase_add_test(tc, s21_abs_test1);
    tcase_add_test(tc, s21_abs_test2);
    tcase_add_test(tc, s21_abs_test3);
    tcase_add_test(tc, s21_abs_test4);
    tcase_add_test(tc, s21_abs_test5);
    tcase_add_test(tc, s21_abs_test6);
    tcase_add_test(tc, s21_abs_test7);
    tcase_add_test(tc, s21_abs_test8);
    tcase_add_test(tc, s21_abs_test9);
    tcase_add_test(tc, s21_abs_test9);
    tcase_add_test(tc, s21_abs_test10);
    tcase_add_test(tc, s21_abs_test11);
    tcase_add_test(tc, s21_abs_test12);
    tcase_add_test(tc, s21_abs_test13);
    tcase_add_test(tc, s21_abs_test14);
    tcase_add_test(tc, s21_abs_test15);
    tcase_add_test(tc, s21_abs_test16);

    //  exp
    tcase_add_test(tc, s21_exp_test1);
    tcase_add_test(tc, s21_exp_test2);
    tcase_add_test(tc, s21_exp_test3);
    tcase_add_test(tc, s21_exp_test4);
    tcase_add_test(tc, s21_exp_test5);
    tcase_add_test(tc, s21_exp_test6);
    tcase_add_test(tc, s21_exp_test7);
    tcase_add_test(tc, s21_exp_test8);
    tcase_add_test(tc, s21_exp_test9);
    tcase_add_test(tc, s21_exp_test9);
    tcase_add_test(tc, s21_exp_test10);
    tcase_add_test(tc, s21_exp_test11);
    tcase_add_test(tc, s21_exp_test12);
    tcase_add_test(tc, s21_exp_test13);
    tcase_add_test(tc, s21_exp_test14);
    tcase_add_test(tc, s21_exp_test15);
    tcase_add_test(tc, s21_exp_test16);
    tcase_add_test(tc, s21_exp_test17);
    tcase_add_test(tc, s21_exp_test18);
    tcase_add_test(tc, s21_exp_test19);
    tcase_add_test(tc, s21_exp_test20);
    tcase_add_test(tc, s21_exp_test21);
    tcase_add_test(tc, s21_exp_test22);
    tcase_add_test(tc, s21_exp_test23);
    tcase_add_test(tc, s21_exp_test24);
    tcase_add_test(tc, s21_exp_test25);
    tcase_add_test(tc, s21_exp_test26);

    //  pow
    tcase_add_test(tc, s21_pow_test1);
    tcase_add_test(tc, s21_pow_test2);
    tcase_add_test(tc, s21_pow_test3);
    tcase_add_test(tc, s21_pow_test4);
    tcase_add_test(tc, s21_pow_test5);
    tcase_add_test(tc, s21_pow_test6);
    tcase_add_test(tc, s21_pow_test7);
    tcase_add_test(tc, s21_pow_test8);
    tcase_add_test(tc, s21_pow_test9);
    tcase_add_test(tc, s21_pow_test9);
    tcase_add_test(tc, s21_pow_test10);
    tcase_add_test(tc, s21_pow_test11);
    tcase_add_test(tc, s21_pow_test12);
    tcase_add_test(tc, s21_pow_test13);
    tcase_add_test(tc, s21_pow_test14);
    tcase_add_test(tc, s21_pow_test15);
    tcase_add_test(tc, s21_pow_test16);
    tcase_add_test(tc, s21_pow_test17);
    tcase_add_test(tc, s21_pow_test18);
    tcase_add_test(tc, s21_pow_test19);
    tcase_add_test(tc, s21_pow_test20);
    tcase_add_test(tc, s21_pow_test21);
    tcase_add_test(tc, s21_pow_test22);
    tcase_add_test(tc, s21_pow_test23);
    tcase_add_test(tc, s21_pow_test24);
    tcase_add_test(tc, s21_pow_test25);
    tcase_add_test(tc, s21_pow_test26);
    tcase_add_test(tc, s21_pow_test27);
    tcase_add_test(tc, s21_pow_test28);
    tcase_add_test(tc, s21_pow_test29);
    tcase_add_test(tc, s21_pow_test30);
    tcase_add_test(tc, s21_pow_test31);
    tcase_add_test(tc, s21_pow_test32);
    tcase_add_test(tc, s21_pow_test34);
    tcase_add_test(tc, s21_pow_test35);
    tcase_add_test(tc, s21_pow_test36);
    tcase_add_test(tc, s21_pow_test37);
    tcase_add_test(tc, s21_pow_test38);
    tcase_add_test(tc, s21_pow_test39);
    tcase_add_test(tc, s21_pow_test40);
    tcase_add_test(tc, s21_pow_test41);
    tcase_add_test(tc, s21_pow_test42);
    tcase_add_test(tc, s21_pow_test43);

    //  cos
    tcase_add_test(tc, s21_cos_test1);
    tcase_add_test(tc, s21_cos_test2);
    tcase_add_test(tc, s21_cos_test3);
    tcase_add_test(tc, s21_cos_test4);
    tcase_add_test(tc, s21_cos_test5);
    tcase_add_test(tc, s21_cos_test6);
    tcase_add_test(tc, s21_cos_test7);
    tcase_add_test(tc, s21_cos_test8);
    tcase_add_test(tc, s21_cos_test9);
    tcase_add_test(tc, s21_cos_test9);
    tcase_add_test(tc, s21_cos_test10);
    tcase_add_test(tc, s21_cos_test11);
    tcase_add_test(tc, s21_cos_test12);
    tcase_add_test(tc, s21_cos_test13);
    tcase_add_test(tc, s21_cos_test14);
    tcase_add_test(tc, s21_cos_test15);
    tcase_add_test(tc, s21_cos_test16);
    tcase_add_test(tc, s21_cos_test17);
    tcase_add_test(tc, s21_cos_test18);
    tcase_add_test(tc, s21_cos_test19);
    tcase_add_test(tc, s21_cos_test20);
    tcase_add_test(tc, s21_cos_test21);
    tcase_add_test(tc, s21_cos_test22);
    tcase_add_test(tc, s21_cos_test23);

    //  cos
    tcase_add_test(tc, s21_tan_test1);
    tcase_add_test(tc, s21_tan_test2);
    tcase_add_test(tc, s21_tan_test3);
    tcase_add_test(tc, s21_tan_test4);
    tcase_add_test(tc, s21_tan_test5);
    tcase_add_test(tc, s21_tan_test6);
    tcase_add_test(tc, s21_tan_test7);
    tcase_add_test(tc, s21_tan_test8);
    tcase_add_test(tc, s21_tan_test9);
    tcase_add_test(tc, s21_tan_test9);
    tcase_add_test(tc, s21_tan_test10);
    tcase_add_test(tc, s21_tan_test11);

    //  s21_abs
    tcase_add_test(tc, s21_abs_func);
    //  s21_fabs
    tcase_add_test(tc, s21_fabs_func);
    //  s21_sqrt
    tcase_add_test(tc, s21_sqrt_func);
    //  s21_log
    tcase_add_test(tc, s21_log_func);
    //  s21_exp
    tcase_add_test(tc, s21_exp_func);
    //  s21_ceil
    tcase_add_test(tc, s21_ceil_func);
    //  s21_sin
    tcase_add_test(tc, s21_sin_func);
    //  s21_cos
    tcase_add_test(tc, s21_cos_func);
    //  s21_tan
    tcase_add_test(tc, s21_tan_func);
    //  s21_asin
    tcase_add_test(tc, s21_asin_func);
    //  s21_acos
    tcase_add_test(tc, s21_acos_func);
    //  s21_atan
    tcase_add_test(tc, s21_atan_func);

    //  fmod
    tcase_add_test(tc, s21_fmod_test1);
    tcase_add_test(tc, s21_fmod_test2);
    tcase_add_test(tc, s21_fmod_test3);
    tcase_add_test(tc, s21_fmod_test4);
    tcase_add_test(tc, s21_fmod_test5);
    tcase_add_test(tc, s21_fmod_test6);
    tcase_add_test(tc, s21_fmod_test7);
    tcase_add_test(tc, s21_fmod_test8);
    tcase_add_test(tc, s21_fmod_test9);
    tcase_add_test(tc, s21_fmod_test9);
    tcase_add_test(tc, s21_fmod_test10);
    tcase_add_test(tc, s21_fmod_test11);
    tcase_add_test(tc, s21_fmod_test12);
    tcase_add_test(tc, s21_fmod_test13);
    tcase_add_test(tc, s21_fmod_test14);
    tcase_add_test(tc, s21_fmod_test15);
    tcase_add_test(tc, s21_fmod_test16);
    tcase_add_test(tc, s21_fmod_test17);
    tcase_add_test(tc, s21_fmod_test18);
    tcase_add_test(tc, s21_fmod_test19);
    tcase_add_test(tc, s21_fmod_test21);
    tcase_add_test(tc, s21_fmod_test22);
    tcase_add_test(tc, s21_fmod_test23);
    tcase_add_test(tc, s21_fmod_test24);
    tcase_add_test(tc, s21_fmod_test25);
    tcase_add_test(tc, s21_fmod_test26);
    tcase_add_test(tc, s21_fmod_test27);
    tcase_add_test(tc, s21_fmod_test28);
    tcase_add_test(tc, s21_fmod_test29);
    tcase_add_test(tc, s21_fmod_test30);
    tcase_add_test(tc, s21_fmod_test31);

    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);

    return 0;
}
