#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>

typedef union {
  unsigned int bits[4];
  struct {
    unsigned int mantysa[3];
    unsigned int jrNotUse : 16;
    unsigned int exp : 8;
    unsigned int mjNotUse : 7;
    unsigned int sign : 1;
  };
} s21_decimal;

typedef union {
  float f;
  unsigned int i;
  struct {
    unsigned int mantysa : 23;
    unsigned int exp : 8;
    unsigned int sign : 1;
  };
} s21_float;

/*___arithmetic_operations___*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*______functions_comparison______*/
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

/*______сonverter_functions______*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/*___another_functions___*/
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/*___secondary_functions___*/
int addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int subtraction(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int get_bit(s21_decimal src, int bitNum);
int set_bit(s21_decimal *src, int bitNum, int sub);
int cast_scale(s21_decimal *value_1, s21_decimal *value_2);
int less_positive(s21_decimal value_1, s21_decimal value_2);
int abs_dec(s21_decimal value_1, s21_decimal value_2);
int shift_left(s21_decimal *value, int moves);
int shift_right(s21_decimal *value, int moves);
void replace_neg_zero(s21_decimal *result);
void full_clean(s21_decimal *target);
void counter_ranks(s21_decimal src, s21_decimal ten, s21_decimal *result);
int last_bit_dec(s21_decimal src);
void div_int(s21_decimal dividend, s21_decimal divisor, s21_decimal *quotient,
             s21_decimal *rem);
void clean(s21_decimal *value);
int get_first_bit(s21_decimal value);
void round_bank(s21_decimal value, s21_decimal *result);
int mult_ten(s21_decimal *value);
int round_one(s21_decimal value, s21_decimal *result);
int multiply(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void err_clean(s21_decimal *value, int *err);
int check_decimal(s21_decimal value);

#endif  // SRC_S21_DECIMAL_H_
