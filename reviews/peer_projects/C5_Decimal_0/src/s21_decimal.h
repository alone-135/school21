#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#define s21_MAX_UINT 4294967295
#define s21_MAX_FLOAT 79228162514264337593543950335.0

#include <limits.h>
#include <math.h> /* for s21_round */
#include <stdio.h>
#include <stdlib.h> /* for abs in July's s21_from_int_to_decimal */

// -2147483647-1 INT_MIN
// 2147483647 INT_MAX  (константы limits.h)

typedef struct decimal {
    int bits[4];
} s21_decimal;

#define CONVERTING_ERROR 1

typedef enum {
    OK = 0,
    TOO_MUCH_OR_INF = 1,
    TOO_FEW_OR_NEG_INF = 2,
    s21_NAN = 3,
} error_message;

typedef union {
    int ui;
    float fl;
} floatbits;

// arithmetic.c
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// comparison.c
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// converters.c // july
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
// open source
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// dop function
int getbit(s21_decimal value, int i);
void setbit(s21_decimal *result, int r, int i);
void s21_init_decimal(s21_decimal *dec);
int s21_get_float_sign(float *src);
int s21_get_float_exp(float *src);
void s21_set_sign(s21_decimal *value, int sign);
int s21_get_sign(s21_decimal *value);

int degree_for_float(s21_decimal src);
int s21_get_int_for_float(s21_decimal src, int *int_to_float);
int s21_get_frac_for_float();

s21_decimal dislocation(s21_decimal value, int i);
void pd(s21_decimal value);

#endif  // SRC_S21_DECIMAL_H_
