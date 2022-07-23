#include "s21_math.h"

double INF = 1.0 / 0.0;
double MIN_INF = -1.0 / 0.0;
double MIN_NAN = -0.0 / 0.0;
double myNAN = 0.0 / 0.0;

//  s21_abs
int s21_abs(int x) {
    int res;
    if (x < 0) {
        res = -1 * x;
    } else {
        res = x;
    }
    return res;
}

//  s21_fabs
long double s21_fabs(double x) {
    long double res;
    if (x < 0) {
        res = -1 * x;
    } else {
        res = x;
    }
    return res;
}

//  s21_sqrt
long double s21_sqrt(double x) {
    long double res;
    if (S21_IS_INF(x)) {
        res = s21_INF;
    } else if (S21_IS_NAN(x)) {
        res = (long double)x;
    } else if (x < 0) {
        res = s21_NAN;
    } else {
        long double temp = 0;
        res = x / 2.0;

        while ((temp - res) != 0) {
            temp = res;
            res = (temp + (x / temp)) / 2.0;
        }
    }
    return res;
}

//  s21_log
long double s21_log(double x) {
    long double res;
    if (S21_IS_INF(x)) {
        res = x;
    } else if (S21_IS_NAN(x)) {
        res = x;
    } else if (x == 0.0) {
        res = -s21_INF;
    } else if (x < 0.0) {
        res = s21_NAN;
    } else {
        int A = 0;
        int n = 1;

        while (x >= 2.0) {
            A++;
            x = x / s21_E;
        }

        long double t = x - 1;
        long double u = t;
        res = u;

        while (u > EPS || u < -EPS) {
            n++;
            u *= -((n - 1) * t) / n;
            res += u;
        }
        res = res + A;
    }
    return res;
}

//  s21_exp
long double s21_exp(double x) {
    long double res;
    if (S21_IS_NAN(x)) {
        res = s21_NAN;
    } else if (S21_IS_INF(x) == 1) {
        res = s21_INF;
    } else if (S21_IS_INF(x) == -1 ||
               (__builtin_signbit(x) && s21_fabs(x) > 20.0)) {
        res = 0;
    } else {
        res = 1.0;
        long double chlen = 1.0;
        int k = 1;
        while (s21_fabs(chlen / res) > 1e-100) {
            chlen *= (long double)x / k++;
            res += chlen;
        }
    }
    return res;
}

//  s21_ceil
long double s21_ceil(double x) {
    long double res;
    if (S21_IS_INF(x) == 1) {
        res = s21_INF;
    } else if (S21_IS_NAN(x)) {
        res = x;
    } else {
        int temp = (int)x;
        if (x == (float)temp) {
            res = x;
        } else {
            if (x > 0) {
                res = temp + 1;
            } else {
                res = temp;
            }
        }
    }
    return res;
}

//  s21_pow
long double s21_pow(double base, double exp) {
    double x = base;
    double res;
    //  all condition needed by ISO C standard 1.2017 for legal error output
    if (x == 1.0) {
        res = 1.0;
    } else if (exp == 0.0 || exp == -0.0) {
        res = 1.0;
    } else if (s21_floor(exp) == exp && exp > 0.0 &&
               (exp / 2.0 > s21_floor(exp / 2.0)) && (x == 0.0 || x == -0.0)) {
        res = x;
    } else if (_isNotINF && _isNotNaN && x < 0 && (s21_floor(exp) != exp) &&
               _expNotINF && _expNotNaN) {  //  x < 0 && exp 0.num
        res = myNAN;
    } else if (x == 0 && exp > 0) {
        res = 0.0;
    } else if (x == -1.0 && _infExp) {
        res = 1.0;
    } else if ((s21_fabs(x) < 1.0 && exp > DBL_MAX) ||
               (s21_fabs(x) > 1.0 && exp < -DBL_MAX)) {
        res = 0.0;
    } else if (s21_fabs(x) < 1.0 && exp < -DBL_MAX) {
        res = INF;
    } else if (s21_fabs(x) > 1.0 && exp > DBL_MAX) {
        res = INF;
    } else if (x < -DBL_MAX && (exp / 2.0 > s21_floor(exp / 2.0)) &&
               s21_floor(exp) == exp && exp < 0.0) {
        res = -0.0;
    } else if (x < -DBL_MAX && (exp / 2.0 == s21_floor(exp / 2.0)) &&
               s21_floor(exp) == exp && exp < 0.0) {
        res = 0.0;
    } else if (x < -DBL_MAX && (exp / 2.0 > s21_floor(exp / 2.0)) &&
               s21_floor(exp) == exp && exp > 0.0) {
        res = MIN_INF;
    } else if (x < -DBL_MAX && (exp / 2.0 == s21_floor(exp / 2.0)) &&
               s21_floor(exp) == exp && exp > 0.0) {
        res = INF;
    } else if (x > DBL_MAX) {
        res = (exp < 0.0) ? 0.0 : (exp > 0.0 && exp != s21_NAN) ? x : s21_NAN;
    } else if (x != x || exp != exp) {
        res = myNAN;
        //  there are start pow logic
    } else {
        res = s21_pow_logic(base, exp);
    }
    return (long double)res;
}

long double s21_pow_logic(double base, double exp) {
    long double res = 0.0;
    if (base < 0.0) {
        double FirstBase = 0.0;
        if (1 > exp && exp > -1.0) {
            res = myNAN;
        } else if (exp >= 1.0) {  //  степень больше или равна единице
            // if (s21_floor(exp) == exp) {  //   целая экспонента больше 1
            FirstBase = base;
            for (double i = 1.0; i < exp; i += 1.0) base *= FirstBase;
            res = base;
            // }
        } else {
            FirstBase = base;
            for (double i = 1.0; i < (-exp); i += 1.0) base *= FirstBase;
            res = 1.00 / base;
        }
    } else {  //  base > 0.0
        res = s21_exp(exp * s21_log(base));
    }
    return res;
}

//  s21_floor
long double s21_floor(double x) {  //  1.79769e+308
    long double res = x;
    if (_isNotINF && _isNotNaN) {
        long check = x;
        if (x > 0.0) {
            res = check;
        } else {
            res = (x == ((double)check)) ? x : ((double)check) - 1;
        }
    }
    return res;
}

//  s21_sin
long double s21_sin(double x) {
    long double res;
    if (S21_IS_NAN(x) || S21_IS_INF(x)) {
        res = s21_NAN;
    } else if (s21_fabs(x) < EPS) {
        res = x;
    } else {
        while (s21_fabs(x) > 2 * s21_PI) {
            if (x > 0)
                x -= 2 * s21_PI;
            else
                x += 2 * s21_PI;
        }
        if (x >= (s21_PI / 2) && x <= (s21_PI / 2) + EPS) {
            res = 1.0;
        } else {
            res = (long double)x;
            long double fact = 1.0;
            long double temp = res;
            int i = 1;
            while (s21_fabs(temp / fact) > 1e-100 && i < 100) {
                fact *= ((2 * i) * (2 * i + 1));
                temp *= -1.0L * (long double)x * (long double)x;
                res += temp / fact;
                i++;
            }
        }
    }
    return res;
}

//  s21_cos
long double s21_cos(double x) {
    long double res;
    if (S21_IS_NAN(x) || S21_IS_INF(x)) {
        res = S21_NAN_VAL;
    } else if (s21_fabs(x) < EPS) {
        res = 1.0L;
    } else {
        while (s21_fabs(x) > 2 * S21_M_PI) {
            if (x > 0)
                x -= 2 * S21_M_PI;
            else
                x += 2 * S21_M_PI;
        }
        res = 1.0L;
        long double ch = 1.0L;
        int i = 1;
        while (s21_fabs(ch / res) > 1e-100) {
            ch = (-ch * x * x) / ((2.0 * i - 1) * (2.0 * i));
            res += ch;
            i++;
        }
    }
    return res;
}

//  s21_tan
long double s21_tan(double x) {
    long double res;
    if (S21_IS_NAN(x) || S21_IS_INF(x)) {
        res = S21_NAN_VAL;
    } else {
        res = s21_sin(x) / s21_cos(x);
    }
    return res;
}

//  s21_asin
long double s21_asin(double x) {
    long double res;
    if (s21_fabs(x) > 1.0 || S21_IS_INF(x) || S21_IS_NAN(x)) {
        res = s21_NAN;
    } else {
        res = s21_atan(x / s21_sqrt(1 - s21_pow(x, 2)));
    }
    return res;
}

//  s21_acos
long double s21_acos(double x) {
    long double res;
    if (x >= 0 && x <= 1) {
        res = s21_atan((s21_sqrt(1.0 - s21_pow(x, 2))) / x);
    } else if (x >= -1 && x < 0) {
        res = s21_PI + s21_atan((s21_sqrt(1.0 - s21_pow(x, 2))) / x);
    } else {
        res = s21_NAN;
    }
    return res;
}

//  s21_atan
long double s21_atan(double x) {
    long double res;
    if (S21_IS_NAN(x)) {
        res = s21_NAN;
    } else if (S21_IS_INF(x) == 1) {
        res = s21_PI / 2;
    } else if (S21_IS_INF(x) == -1) {
        res = -1 * s21_PI / 2;
    } else {
        res = s21_fabs(x);
        long double num = res * res;
        long double temp = res;
        long double del = 1.0;
        if (res > 1.0) {
            res = (s21_PI / 2) - s21_atan(1.0 / res);
        } else {
            while (s21_fabs(temp / del) > 1e-8) {
                del += 2;
                temp *= num * (-1);
                res += temp / del;
            }
        }
        if (x < 0) {
            res = -res;
        }
    }
    return res;
}

//  s21_fmod_func
long double s21_fmod(double x, double y) {
    long double res = 0.0;
    double exp = y;
    //  all condition needed by ISO C standard 1.2017 for legal error output
    if (y == 0.0 || !(_isNotINF)) {
        res = myNAN;
    } else if ((x == 0.0 || x == -0.0) && y != 0.0) {
        res = x;
    } else if (_isNotINF && _infExp) {
        res = x;
    } else if (x != x || y != y) {
        res = x;
    } else if (S21_IS_NAN(x) == -1) {
        res = -s21_NAN;
    } else {
        //  main functional here
        res = x - (s21_rounding((x / y)) * y);
        if (s21_fabs(x) != x && res == 0) res *= -1;
    }
    return res;
}

double s21_rounding(double x) {
    return x > 0 ? (double)s21_floor(x) : (double)(s21_ceil(x));
}
