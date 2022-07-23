#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS1 1E-7
#define EPS 1e-15
#define s21_PI 3.141592653589793238462643383279502884197169399375105820974944
#define s21_E 2.718281828459045235360287471352662497757247093699959574966967
#define s21_NAN (__builtin_nanf(""))
#define s21_INF (__builtin_inff())
#define RAD 57.2958l
#define S21_IS_INF(x) __builtin_isinf_sign(x)
#define S21_IS_NAN(x) __builtin_isnan(x)

#define S21_HUGE_VAL (__builtin_inff())
#define S21_NAN_VAL (__builtin_nanf(""))
#define S21_M_PI2 1.5707963267948966192313216916397514
#define S21_M_PI 3.14159265358979323846264338327950288
#define S21_ME 2.71828182845904523536028747135266250
#define S21_LN2 0.693147180559945309417232121458176568

#define _isNotINF x <= DBL_MAX&& x >= -DBL_MAX
#define _isNotNaN x == x

#define _expNotINF exp <= DBL_MAX&& exp >= -DBL_MAX
#define _expNotNaN exp == exp
#define _infExp (exp > DBL_MAX || exp < -DBL_MAX)

int s21_abs(int x);

long double s21_exp(double x);
long double s21_log(double x);
long double s21_sqrt(double x);
long double s21_ceil(double x);

long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);

long double s21_asin(double x);
long double s21_acos(double x);
long double s21_atan(double x);

long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_pow(double base, double exp);

long double s21_pow_logic(double base, double exp);
double s21_rounding(double x);

#endif  // SRC_S21_MATH_H_
