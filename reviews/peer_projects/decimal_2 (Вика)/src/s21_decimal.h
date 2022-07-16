#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define minimum 1e-28
#define inf 1.0 / 0.0
#define nan 0.0 / 0.0
#define TRUE 1
#define FALSE 0
#define SIGN 0x80000000
#define OK 0
#define BIG_NUM 1
#define SMALL_NUM 2
#define DIVISION_BY_ZERO 3
#define SUCCESS 0
#define ERROR 1

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef union floatbits {
  int ui;
  float fl;
} floatbits;

// Арифметические операторы
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Операторы сравнения
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Преобразователи
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Другие функции
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// допы
int s21_get_bit(const s21_decimal decVar, int bit);
int s21_last_bit(s21_decimal number);
int s21_offset_left(s21_decimal *dst, int src);
int s21_get_sign(const s21_decimal *dst);
int s21_get_scale(const s21_decimal *dst);
void s21_set_scale(s21_decimal *dst, int scale);
void s21_mul_only_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_bits(s21_decimal var1, s21_decimal var2, s21_decimal* result);
void s21_set_sign(s21_decimal *dst, int sign);
void s21_sub_only_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_div_only_bits(s21_decimal a, s21_decimal b, s21_decimal *buf, s21_decimal *result);
void s21_check_scale(s21_decimal *value1, s21_decimal *value2);
void s21_minus_scale(s21_decimal* a);
void s21_scale_equalize(s21_decimal *value_1, s21_decimal *value_2);
void s21_set_bit(s21_decimal *dst, int bit, int value);
int s21_offset_left(s21_decimal *dst, int src);
void s21_decimal_init(s21_decimal *dst);
int s21_get_higher_bit(s21_decimal value);
void s21_get_binary_from_float(float src, char *float_bin_buff);
int s21_get_scale_float(const char *src);
void s21_mantissa_to_decimal(s21_decimal *dst, char *float_bin_buff, int exp);
int s21_bit_addition(s21_decimal var1, s21_decimal var2, s21_decimal *result);
int s21_get_float_exp(float *src);
int s21_get_float_bit(float src);
void s21_change_scale(s21_decimal *value, int change_scale);
void s21_bits_copy(s21_decimal src, s21_decimal *dest);
int s21_get_float_sign(float *src);
void s21_clear_bits(s21_decimal *varPtr);
int s21_sign_minus(s21_decimal a);
int s21_handle_scales_equality(s21_decimal *value_1, s21_decimal *value_2, int *final_scale);
int s21_equalize_scales(s21_decimal *dec1, s21_decimal *dec2, int scale);
int s21_equalize_to_lower(s21_decimal *dec, int scale);
int s21_equalize_to_bigger(s21_decimal *dec, int scale);
s21_decimal s21_binary_division(s21_decimal dec1, s21_decimal dec2, s21_decimal *remainder, int *fail);
int s21_sub_without_scale(s21_decimal value1, s21_decimal value2, s21_decimal *result);
void s21_swap_values(s21_decimal *value1, s21_decimal *value2);
int s21_add_without_scale(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_shift_left(s21_decimal *dec, int shift);

#endif  // SRC_S21_DECIMAL_H_
