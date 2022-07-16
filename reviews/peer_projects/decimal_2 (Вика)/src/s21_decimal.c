#include "s21_decimal.h"

//====================================================================================//
//                 А Р И Ф М Е Т И Ч Е С К И Е    О П Е Р А Т О Р Ы //
//====================================================================================//
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    memset(result->bits, 0, sizeof(result->bits));
    int return_value = OK, sign1 = s21_get_sign(&value_1),
        sign2 = s21_get_sign(&value_2);
    unsigned int mask = 1u << 31;
    if (!sign1 && !sign2) {
        int scale_1 = (char)(value_1.bits[3] >> 16),
            scale_2 = (char)(value_2.bits[3] >> 16);
        if (scale_1 != scale_2) {
            s21_scale_equalize(&value_1, &value_2);
        }
        int bit_additioin_result = OK;
        s21_decimal tmp_res;
        bit_additioin_result = s21_add_bits(value_1, value_2, &tmp_res);
        if (bit_additioin_result == BIG_NUM) {
            return_value = BIG_NUM;
        } else {
            *result = tmp_res;
            result->bits[3] = value_1.bits[3];
        }
    } else if (sign1 && !sign2) {
        value_1.bits[3] &= ~mask;
        return_value = s21_sub(value_2, value_1, result);
    } else if (!sign1 && sign2) {
        value_2.bits[3] &= ~mask;
        return_value = s21_sub(value_1, value_2, result);
    } else {
        value_1.bits[3] &= ~mask;
        value_2.bits[3] &= ~mask;
        return_value = s21_add(value_1, value_2, result);
        if (return_value == BIG_NUM)
            return_value = SMALL_NUM;
        else
            result->bits[3] |= mask;
    }
    return return_value;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int return_value = OK, resultSign;
    memset(result->bits, 0, sizeof(result->bits));
    int sign_1 = s21_get_sign(&value_1), sign_2 = s21_get_sign(&value_2);
    int scale_1 = (char)(value_1.bits[3] >> 16),
        scale_2 = (char)(value_2.bits[3] >> 16);
    if (scale_1 != scale_2) {
        s21_scale_equalize(&value_1, &value_2);
    }
    unsigned int mask = 1u << 31;
    s21_set_sign(&value_1, sign_1);
    s21_set_sign(&value_2, sign_2);
    if (s21_get_sign(&value_1) != s21_get_sign(&value_2)) {
        resultSign = s21_get_sign(&value_1);
        value_1.bits[3] &= ~mask;
        value_2.bits[3] &= ~mask;
        return_value = s21_add(value_1, value_2, result);
        if (return_value == BIG_NUM) {
            return_value = SMALL_NUM;
        } else {
            s21_set_sign(result, resultSign);
        }
    } else {
        if (s21_is_equal(value_1, value_2) == TRUE) {
        } else {
            int sign1 = s21_get_sign(&value_1);
            int sign2 = s21_get_sign(&value_2);
            value_1.bits[3] &= ~mask;
            value_2.bits[3] &= ~mask;
            s21_decimal *smallPtr, *bigPtr;
            if (s21_is_less(value_1, value_2) == TRUE) {
                smallPtr = &value_1;
                bigPtr = &value_2;
                resultSign = !sign2;
            } else {
                smallPtr = &value_2;
                bigPtr = &value_1;
                resultSign = sign1;
            }
            s21_sub_only_bits(*bigPtr, *smallPtr, result);
            s21_set_scale(result, (char)(value_1.bits[3] >> 16));
            s21_set_sign(result, resultSign);
        }
    }
    return return_value;
}

int s21_mul(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
    s21_clear_bits(result);
    int return_value = OK;
    int sign_result;

    if (s21_get_sign(&number_1) != s21_get_sign(&number_2)) {
        sign_result = 1;
    } else {
        sign_result = 0;
    }

    int last_bit_1 = s21_last_bit(number_1);
    s21_decimal tmp_res = {{0, 0, 0, 0}};

    int bit_addition_result = OK;

    for (int i = 0; i <= last_bit_1; i++) {
        s21_clear_bits(&tmp_res);
        int value_bit_1 = s21_get_bit(number_1, i);

        if (value_bit_1) {
            tmp_res = number_2;
            bit_addition_result = s21_offset_left(&tmp_res, i);
            bit_addition_result = s21_bit_addition(*result, tmp_res, result);
        }
    }

    if (bit_addition_result == BIG_NUM) {
        if (sign_result)
            return_value = SMALL_NUM;
        else
            return_value = BIG_NUM;
        s21_clear_bits(result);
    } else {
        int scale = s21_get_scale(&number_1) + s21_get_scale(&number_2);
        s21_set_scale(result, scale);
        s21_set_sign(result, sign_result);
    }

    return return_value;
}

int s21_div(s21_decimal divident, s21_decimal divisor, s21_decimal *result) {
    int return_value = OK;
    s21_clear_bits(result);
    s21_decimal zero = {{0, 0, 0, 0}};
    if (s21_is_equal(divisor, zero) == TRUE) {
        return_value = DIVISION_BY_ZERO;
        s21_clear_bits(result);
    } else {
        int beginScale = s21_get_scale(&divident) - s21_get_scale(&divisor);
        int resultSign = s21_get_sign(&divident) != s21_get_sign(&divisor);
        s21_decimal remainder = {0}, tmp = {0};
        s21_set_scale(&divisor, 0);
        s21_set_scale(&divident, 0);
        s21_set_sign(&divisor, 0);
        s21_set_sign(&divident, 0);
        s21_div_only_bits(divident, divisor, &remainder, &tmp);
        s21_bits_copy(tmp, result);
        s21_decimal border_value = {{4294967295u, 4294967295, 4294967295u, 0}};
        s21_decimal ten = {{10, 0, 0, 0}};
        s21_set_scale(&border_value, 1);
        int inside_scale = 0;
        for (; inside_scale <= 27 && s21_is_equal(remainder, zero) == FALSE;) {
            if (s21_is_less(*result, border_value) == FALSE) {
                break;
            }
            s21_mul(remainder, ten, &remainder);
            s21_div_only_bits(remainder, divisor, &remainder, &tmp);
            s21_mul(*result, ten, result);
            s21_bit_addition(*result, tmp, result);
            inside_scale++;
        }
        s21_decimal musor;
        int endScale = beginScale + inside_scale;
        for (; endScale > 28;) {
            s21_div_only_bits(*result, ten, &musor, result);
            endScale--;
        }
        for (; endScale < 0;) {
            s21_mul(*result, ten, result);
            endScale++;
        }
        s21_set_scale(result, endScale);
        s21_set_sign(result, resultSign);
    }
    return return_value;
}

int s21_mod(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
    memset(result->bits, 0, sizeof(result->bits));
    int return_value = OK;
    s21_decimal zero = {{0, 0, 0, 0}};
    if (s21_is_equal(number_2, zero)) {
        return_value = DIVISION_BY_ZERO;
    } else {
        if (!s21_get_sign(&number_1) && !s21_get_sign(&number_2)) {
            while (s21_is_greater_or_equal(number_1, number_2)) {
                s21_sub(number_1, number_2, &number_1);
            }
        } else if (!s21_get_sign(&number_1) && s21_get_sign(&number_2)) {
            s21_set_sign(&number_2, 0);
            while (s21_is_greater_or_equal(number_1, number_2)) {
                s21_sub(number_1, number_2, &number_1);
            }
        } else if (s21_get_sign(&number_1) && !s21_get_sign(&number_2)) {
            s21_set_sign(&number_1, 0);
            while (s21_is_greater_or_equal(number_1, number_2)) {
                s21_sub(number_1, number_2, &number_1);
            }
            s21_set_sign(&number_1, 1);
        } else if (s21_get_sign(&number_1) && s21_get_sign(&number_2)) {
            s21_set_sign(&number_1, 0);
            s21_set_sign(&number_2, 0);
            while (s21_is_greater_or_equal(number_1, number_2)) {
                s21_sub(number_1, number_2, &number_1);
            }
            s21_set_sign(&number_1, 1);
        }
        *result = number_1;
    }

    return return_value;
}

//====================================================================================//
//                      О П Е Р А Т О Р Ы   С Р А В Н Е Н И Я //
//====================================================================================//

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    int scale;
    int result = 1;
    s21_handle_scales_equality(&value_1, &value_2, &scale);
    if (s21_sign_minus(value_1) && !s21_sign_minus(value_2)) {
        result = 0;
    } else if (!s21_sign_minus(value_1) && s21_sign_minus(value_2)) {
        result = 1;
    } else if (s21_sign_minus(value_1) == s21_sign_minus(value_2)) {
        for (int i = 2; i >= 0; i--) {
            if (value_1.bits[i] > value_2.bits[i]) {
                result = 1;
                break;
            } else if (value_1.bits[i] < value_2.bits[i]) {
                result = 0;
                break;
            } else if (value_1.bits[i] == value_2.bits[i]) {
                result = 0;
                continue;
            }
        }
        if (s21_get_bit(value_1, 127)) {
            if (result == 1)
                result = 0;
            else
                result = 1;
        }
    }
    return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int is_equal = TRUE;
    if (s21_get_scale(&value_1) != s21_get_scale(&value_2))
        s21_scale_equalize(&value_1, &value_2);
    if (value_1.bits[0] == 0 && value_2.bits[0] == 0 && value_1.bits[1] == 0 &&
        value_2.bits[1] == 0 && value_1.bits[2] == 0 && value_2.bits[2] == 0) {
    } else if (value_1.bits[0] != value_2.bits[0] ||
               value_1.bits[1] != value_2.bits[1] ||
               value_1.bits[2] != value_2.bits[2] ||
               value_1.bits[3] != value_2.bits[3]) {
        is_equal = FALSE;
    }
    return is_equal;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    return (s21_is_greater(value_2, value_1));
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
    return (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2));
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) { /* >= */
    return (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2));
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) { /* != */
    return (!s21_is_equal(value_1, value_2));
}

//====================================================================================//
//                          П Р Е О Б Р А З О В А Т Е Л И //
//====================================================================================//

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int res = SUCCESS;
    if (dst) {
        s21_decimal_init(dst);
        if (src & 1u << 31) {
            s21_set_bit(dst, 127, 1);
            src *= -1;
        }
        int n = 0;
        while (n < 31) {
            if (src & 1u << n) s21_set_bit(dst, n, 1);
            n++;
        }
    } else {
        res = ERROR;
    }
    return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    memset(dst->bits, 0, sizeof(dst->bits));
    int return_value = SUCCESS;
    if (isinf(src) || isnan(src)) {
        return_value = ERROR;
    } else {
        if (src != 0) {
            int sign = s21_get_float_sign(&src), exp = s21_get_float_exp(&src);
            double temp = (double)fabs(src);
            int off = 0;
            for (; off < 28 && (int)temp / (int)pow(2, 21) == 0;
                 temp *= 10, off++) {
            }
            temp = round(temp);
            if (off <= 28 && (exp > -94 && exp < 96)) {
                floatbits mant;
                temp = (float)temp;
                for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
                }
                mant.fl = temp;
                exp = s21_get_float_exp(&mant.fl);
                dst->bits[exp / 32] |= 1 << exp % 32;
                for (int i = exp - 1, j = 22; j >= 0; i--, j--)
                    if ((mant.ui & (1 << j)) != 0)
                        dst->bits[i / 32] |= 1 << i % 32;
                dst->bits[3] = (sign << 31) | (off << 16);
            }
        }
    }

    return return_value;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int res = SUCCESS;
    *dst = 0;
    if (dst) {
        int sign = s21_get_bit(src, 127);
        s21_decimal tmp = {{0, 0, 0, 0}};
        s21_truncate(src, &tmp);
        if (s21_get_higher_bit(tmp) < 31) {
            *dst = tmp.bits[0];
            if (sign == 1) *dst *= -1;
        } else {
            res = ERROR;
        }
    } else {
        res = ERROR;
    }
    return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int res = SUCCESS;
    if (!dst || s21_get_scale(&src) > 28) {
        res = 1;
    } else {
        *dst = 0.0;
        int scale = s21_get_scale(&src);
        int sign = s21_get_bit(src, 127);
        int last_bit = s21_get_bit(src, 127);
        if (sign) s21_set_bit(&src, 127, 1);
        s21_set_scale(&src, scale);
        double tmp = *dst;
        if (last_bit == 1) s21_set_bit(&src, 127, 1);
        unsigned long base = 1;
        for (int i = 0; i < 96; i++) {
            tmp += s21_get_bit(src, i) * base;
            base = base * 2;
        }
        while (scale != 0) {
            tmp = tmp / 10;
            scale--;
        }
        if (s21_get_bit(src, 127)) tmp *= -1;
        *dst = tmp;
    }
    return res;
}

//====================================================================================//
//                            Д Р У И Г Е   Ф У Н К Ц И И //
//====================================================================================//

int s21_floor(s21_decimal value, s21_decimal *result) {
    memset(result->bits, 0, sizeof(result->bits));
    int ret_val = OK;
    s21_truncate(value, result);
    s21_decimal one = {{1, 0, 0, 0}};
    if (s21_get_sign(&value)) {
        ret_val = s21_sub(*result, one, result);
    }
    return ret_val;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    memset(result->bits, 0, sizeof(result->bits));
    unsigned int mask = 1u << 31;
    int return_value = OK;
    int sign = s21_get_sign(&value);
    value.bits[3] &= ~mask;
    s21_decimal tmp = {{0}};
    s21_truncate(value, &tmp);
    s21_decimal tmp_copy = tmp;
    s21_sub(value, tmp, &tmp);
    s21_decimal zero_five = {{5, 0, 0, 0}};
    s21_decimal one = {{1, 0, 0, 0}};
    s21_set_scale(&zero_five, 1);
    if (!s21_is_greater_or_equal(tmp, zero_five)) {
        *result = tmp_copy;
    } else {
        return_value = s21_add(tmp_copy, one, result);
    }
    if (sign) result->bits[3] |= mask;
    return return_value;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    unsigned int mask = 1u << 31;
    memset(result->bits, 0, sizeof(result->bits));
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal tmp = {{0, 0, 0, 0}};
    int sign_value = s21_get_sign(&value);
    int scale = s21_get_scale(&value);
    if (scale) {
        for (int i = scale; i > 0; i--) {
            s21_div_only_bits(value, ten, &tmp, result);
            value = *result;
        }
    } else {
        *result = value;
    }
    if (sign_value) result->bits[3] |= mask;
    return OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    unsigned int mask = 1u << 31;
    *result = value;
    int sign = s21_get_sign(result);
    if (sign) {
        result->bits[3] &= ~mask;
    } else {
        result->bits[3] |= mask;
    }
    return OK;
}

//====================================================================================//
//                             Д О П   Ф У Н К Ц И И //
//====================================================================================//

int s21_get_bit(const s21_decimal dst, int bit) {
    int res = 0;
    if (bit / 32 < 4) {
        unsigned int mask = 1u << (bit % 32);
        res = dst.bits[bit / 32] & mask;
    }
    return !!res;
}

int s21_last_bit(s21_decimal num) {
    int last_bit = 95;
    for (; last_bit >= 0 && s21_get_bit(num, last_bit) == 0; last_bit--) {
    }
    return last_bit;
}

int s21_offset_left(s21_decimal *dst, int src) {
    int return_value = OK;
    int lastbit = s21_last_bit(*dst);
    if (lastbit + src > 95) {
        return_value = BIG_NUM;
    } else {
        for (int i = 0; i < src; i++) {
            int value_31bit = s21_get_bit(*dst, 31);
            int value_63bit = s21_get_bit(*dst, 63);
            dst->bits[0] <<= 1;
            dst->bits[1] <<= 1;
            dst->bits[2] <<= 1;
            if (value_31bit) s21_set_bit(dst, 32, 1);
            if (value_63bit) s21_set_bit(dst, 64, 1);
        }
    }
    return return_value;
}

int s21_get_sign(const s21_decimal *dst) {
    unsigned int mask = 1u << 31;
    return (dst->bits[3] & mask);
}

int s21_get_scale(const s21_decimal *dst) { return (char)(dst->bits[3] >> 16); }

void s21_set_scale(s21_decimal *varPtr, int scale) {
    int clearMask = ~(0xFF << 16);
    varPtr->bits[3] &= clearMask;
    int mask = scale << 16;
    varPtr->bits[3] |= mask;
}

void s21_mul_only_bits(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *result) {
    memset(result->bits, 0, sizeof(result->bits));
    s21_decimal tmp_res;
    int last_bit_1 = s21_last_bit(value_1);
    for (int i = 0; i <= last_bit_1; i++) {
        memset(tmp_res.bits, 0, sizeof(tmp_res.bits));
        int value_bit_1 = s21_get_bit(value_1, i);

        if (value_bit_1) {
            tmp_res = value_2;
            s21_offset_left(&tmp_res, i);
            s21_add_bits(*result, tmp_res, result);
        }
    }
}

int s21_add_bits(s21_decimal var1, s21_decimal var2, s21_decimal *result) {
    memset(result->bits, 0, sizeof(result->bits));
    int return_value = OK;
    int buffer = 0;
    for (int i = 0; i < 96; i++) {
        int cur_bit_of_var1 = s21_get_bit(var1, i);
        int cur_bit_of_var2 = s21_get_bit(var2, i);
        if (!cur_bit_of_var1 && !cur_bit_of_var2) {
            if (buffer) {
                s21_set_bit(result, i, 1);
                buffer = 0;
            } else {
                s21_set_bit(result, i, 0);
            }
        } else if (cur_bit_of_var1 != cur_bit_of_var2) {
            if (buffer) {
                s21_set_bit(result, i, 0);
                buffer = 1;
            } else {
                s21_set_bit(result, i, 1);
            }
        } else {
            if (buffer) {
                s21_set_bit(result, i, 1);
                buffer = 1;
            } else {
                s21_set_bit(result, i, 0);
                buffer = 1;
            }
        }
        if (i == 95 && buffer == 1) return_value = BIG_NUM;
    }
    return return_value;
}

void s21_set_sign(s21_decimal *dst, int sign) {
    unsigned int mask = 1u << 31;
    if (sign == 0) {
        dst->bits[3] &= ~mask;
    } else {
        dst->bits[3] |= mask;
    }
}

void s21_sub_only_bits(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *result) {
    memset(result->bits, 0, sizeof(result->bits));
    if (s21_is_equal(value_1, value_2) == TRUE) {
    } else {
        int value_1_last_bit = s21_last_bit(value_1);
        int buffer = 0;
        for (int i = 0; i <= value_1_last_bit; i++) {
            int current_bit_of_value_1 = s21_get_bit(value_1, i);
            int current_bit_of_value_2 = s21_get_bit(value_2, i);
            if (!current_bit_of_value_1 && !current_bit_of_value_2) {
                if (buffer) {
                    buffer = 1;
                    s21_set_bit(result, i, 1);
                } else {
                    s21_set_bit(result, i, 0);
                }
            } else if (current_bit_of_value_1 && !current_bit_of_value_2) {
                if (buffer) {
                    buffer = 0;
                    s21_set_bit(result, i, 0);
                } else {
                    s21_set_bit(result, i, 1);
                }
            } else if (!current_bit_of_value_1 && current_bit_of_value_2) {
                if (buffer) {
                    buffer = 1;
                    s21_set_bit(result, i, 0);
                } else {
                    buffer = 1;
                    s21_set_bit(result, i, 1);
                }
            } else if (current_bit_of_value_1 && current_bit_of_value_2) {
                if (buffer) {
                    buffer = 1;
                    s21_set_bit(result, i, 1);
                } else {
                    s21_set_bit(result, i, 0);
                }
            }
        }
    }
}

void s21_div_only_bits(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *buf, s21_decimal *result) {
    memset(buf->bits, 0, sizeof(buf->bits));
    memset(result->bits, 0, sizeof(result->bits));
    for (int i = s21_last_bit(value_1); i >= 0; i--) {
        if (s21_get_bit(value_1, i)) s21_set_bit(buf, 0, 1);
        if (s21_is_greater_or_equal(*buf, value_2) == TRUE) {
            s21_sub_only_bits(*buf, value_2, buf);
            if (i != 0) s21_offset_left(buf, 1);
            if (s21_get_bit(value_1, i - 1)) s21_set_bit(buf, 0, 1);
            s21_offset_left(result, 1);
            s21_set_bit(result, 0, 1);
        } else {
            s21_offset_left(result, 1);
            if (i != 0) s21_offset_left(buf, 1);
            if ((i - 1) >= 0 && s21_get_bit(value_1, i - 1))
                s21_set_bit(buf, 0, 1);
        }
    }
}

// void s21_check_scale(s21_decimal *value1, s21_decimal *value2) {
//     int scale_value1 = s21_get_scale(value1);
//     int scale_value2 = s21_get_scale(value2);
//     if (scale_value1 != scale_value2) {
//         s21_scale_equalize(value1, value2);
//     }
// }

void s21_minus_scale(s21_decimal *a) {
    s21_decimal ten = {{10, 0, 0, 0}};
    if (s21_last_bit(*a) < 32 && a->bits[0] < 10) a->bits[0] = 0;
    s21_decimal musor;
    s21_div_only_bits(*a, ten, &musor, a);
}

void s21_scale_equalize(s21_decimal *value_1, s21_decimal *value_2) {
    s21_decimal ten = {{10u, 0, 0, 0}};
    if (s21_get_scale(value_1) < s21_get_scale(value_2)) {
        int difference = s21_get_scale(value_2) - s21_get_scale(value_1);
        if (s21_get_bit(*value_2, 93) == 0 && s21_get_bit(*value_2, 94) == 0 &&
            s21_get_bit(*value_2, 95) == 0) {
            for (int i = 0; i < difference; i++) {
                s21_mul_only_bits(*value_1, ten, value_1);
            }
            s21_set_scale(value_1, s21_get_scale(value_2));
        } else {
            for (int i = 0; i < difference; i++) {
                s21_minus_scale(value_2);
            }
            s21_set_scale(value_2, s21_get_scale(value_1));
        }
    } else {
        int difference = s21_get_scale(value_1) - s21_get_scale(value_2);
        if (s21_get_bit(*value_1, 93) == 0 && s21_get_bit(*value_1, 94) == 0 &&
            s21_get_bit(*value_1, 95) == 0) {
            for (int i = 0; i < difference; i++) {
                s21_mul_only_bits(*value_2, ten, value_2);
            }
            s21_set_scale(value_2, s21_get_scale(value_1));
        } else {
            for (int i = 0; i < difference; i++) {
                s21_minus_scale(value_1);
            }
            s21_set_scale(value_1, s21_get_scale(value_2));
        }
    }
}

void s21_set_bit(s21_decimal *dst, int bit, int value) {
    unsigned int mask = 1u << (bit % 32);
    if (bit / 32 < 4 && value) {
        dst->bits[bit / 32] |= mask;
    } else if (bit / 32 < 4 && !value) {
        dst->bits[bit / 32] &= ~mask;
    }
}

void s21_decimal_init(s21_decimal *dst) {
    if (dst) {
        dst->bits[0] = 0;
        dst->bits[1] = 0;
        dst->bits[2] = 0;
        dst->bits[3] = 0;
    }
}

int s21_get_higher_bit(s21_decimal value) {
    int i = 95;
    for (; i >= 0; i--) {
        if (s21_get_bit(value, i)) break;
    }
    return i;
}

// void s21_get_binary_from_float(float src, char *float_bin_buff) {
//     union floatbits float_number_bits;
//     float_number_bits.fl = src;
//     for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
//         *float_bin_buff = !!(float_number_bits.ui & mask);
//         float_bin_buff++;
//     }
// }

// int s21_get_scale_float(const char *src) {
//     int res = 0;
//     int base = 1;
//     for (int i = 8; i > 0; i--) {
//         res += src[i] * base;
//         base = base * 2;
//     }
//     return (res - 127);
// }

// void s21_mantissa_to_decimal(s21_decimal *dst, char *float_bin_buff, int exp)
// {
//     for (int i = exp - 1, j = 9; i >= 0 && j < 32; i--, j++) {
//         if (float_bin_buff[j]) s21_set_bit(dst, i, 1);
//     }
// }

int s21_bit_addition(s21_decimal var1, s21_decimal var2, s21_decimal *result) {
    memset(result->bits, 0, sizeof(result->bits));
    int return_value = OK;
    int buffer = 0;

    for (int i = 0; i < 96; i++) {
        int cur_bit_of_var1 = s21_get_bit(var1, i);
        int cur_bit_of_var2 = s21_get_bit(var2, i);

        if (!cur_bit_of_var1 && !cur_bit_of_var2) {
            if (buffer) {
                s21_set_bit(result, i, 1);
                buffer = 0;
            } else {
                s21_set_bit(result, i, 0);
            }
        } else if (cur_bit_of_var1 != cur_bit_of_var2) {
            if (buffer) {
                s21_set_bit(result, i, 0);
                buffer = 1;
            } else {
                s21_set_bit(result, i, 1);
            }
        } else {
            if (buffer) {
                s21_set_bit(result, i, 1);
                buffer = 1;
            } else {
                s21_set_bit(result, i, 0);
                buffer = 1;
            }
        }
        if (i == 95 && buffer == 1) return_value = BIG_NUM;
    }

    return return_value;
}

int s21_get_float_exp(float *src) {
    return ((*(int *)src & ~0x80000000) >> 23) - 127;
}

int s21_get_float_bit(float src) { return *(int *)&src; }

void s21_change_scale(s21_decimal *value, int change_scale) {
    value->bits[3] >>= 16;
    value->bits[3] += change_scale;
    value->bits[3] <<= 16;
}

void s21_bits_copy(s21_decimal src, s21_decimal *dest) {
    dest->bits[0] = src.bits[0];
    dest->bits[1] = src.bits[1];
    dest->bits[2] = src.bits[2];
}

int s21_get_float_sign(float *src) { return *(int *)src >> 31; }

void s21_clear_bits(s21_decimal *varPtr) {
    memset(varPtr->bits, 0, sizeof(varPtr->bits));
}

int s21_sign_minus(s21_decimal a) { return a.bits[3] >> 31; }

int s21_handle_scales_equality(s21_decimal *value_1, s21_decimal *value_2,
                               int *final_scale) {
    s21_decimal value1_tmp = *value_1;
    s21_decimal value2_tmp = *value_2;
    int scale1 = s21_get_scale(value_1);
    int scale2 = s21_get_scale(value_2);
    int ret = 0, scale_to_write = scale1;
    if (scale1 > scale2) {
        ret = s21_equalize_scales(&value1_tmp, &value2_tmp, scale1);
        scale_to_write = scale1;
        if (ret != 0) {
            scale_to_write = scale2;
            value1_tmp = *value_1;
            value2_tmp = *value_2;
            ret = s21_equalize_scales(&value1_tmp, &value2_tmp, scale2);
        }
    } else if (scale1 < scale2) {
        ret = s21_equalize_scales(&value1_tmp, &value2_tmp, scale2);
        scale_to_write = scale2;
        if (ret != 0) {
            scale_to_write = scale1;
            value1_tmp = *value_1;
            value2_tmp = *value_2;
            ret = s21_equalize_scales(&value1_tmp, &value2_tmp, scale1);
        }
    }
    *final_scale = scale_to_write;
    *value_1 = value1_tmp;
    *value_2 = value2_tmp;
    return ret;
}

int s21_equalize_scales(s21_decimal *dec1, s21_decimal *dec2, int scale) {
    int scale1 = s21_get_scale(dec1);
    int scale2 = s21_get_scale(dec2);
    int ret = 0;
    int sign1 = s21_get_bit(*dec1, 127);
    dec1->bits[3] = 0;
    int sign2 = s21_get_bit(*dec2, 127);
    dec2->bits[3] = 0;
    if (scale1 > scale)
        ret = s21_equalize_to_lower(dec1, scale1 - scale);
    else if (scale1 < scale)
        ret = s21_equalize_to_bigger(dec1, scale - scale1);
    if (scale2 > scale)
        ret = s21_equalize_to_lower(dec2, scale2 - scale);
    else if (scale2 < scale)
        ret = s21_equalize_to_bigger(dec2, scale - scale2);
    s21_set_scale(dec1, scale);
    s21_set_scale(dec2, scale);
    if (sign1) s21_set_bit(dec1, 127, 1);
    if (sign2) s21_set_bit(dec2, 127, 1);
    return ret;
}

int s21_equalize_to_lower(s21_decimal *dec, int scale) {
    int ret = 0;
    while (scale--) {
        s21_decimal reminder;
        s21_decimal ten = {{10, 0, 0, 0}};
        *dec = s21_binary_division(*dec, ten, &reminder, &ret);
        if (ret != 0) break;
    }
    return ret;
}

int s21_equalize_to_bigger(s21_decimal *dec, int scale) {
    int ret = 0;
    while (scale--) {
        s21_decimal buf1 = *dec, buf2 = *dec;
        ret = s21_shift_left(&buf2, 3);
        if (ret != 0) break;
        ret = s21_shift_left(&buf1, 1);
        if (ret != 0) break;
        ret = s21_add(buf2, buf1, dec);
        if (ret != 0) break;
    }
    return ret;
}

s21_decimal s21_binary_division(s21_decimal dec1, s21_decimal dec2,
                                s21_decimal *remainder, int *fail) {
    s21_decimal_init(remainder);
    s21_decimal result = {{0, 0, 0, 0}};
    int result_scale = 0;
    *fail = s21_handle_scales_equality(&dec1, &dec2, &result_scale);
    for (int i = s21_get_higher_bit(dec1); i >= 0; i--) {
        if (s21_get_bit(dec1, i)) s21_set_bit(remainder, 0, 1);
        if (s21_is_greater_or_equal(*remainder, dec2)) {
            *fail = s21_sub_without_scale(*remainder, dec2, remainder);
            if (i != 0) *fail = s21_shift_left(remainder, 1);
            if (s21_get_bit(dec1, i - 1)) s21_set_bit(remainder, 0, 1);
            *fail = s21_shift_left(&result, 1);
            s21_set_bit(&result, 0, 1);
        } else {
            *fail = s21_shift_left(&result, 1);
            if (i != 0) *fail = s21_shift_left(remainder, 1);
            if (i - 1 >= 0 && s21_get_bit(dec1, i - 1))
                s21_set_bit(remainder, 0, 1);
        }
    }
    s21_set_scale(remainder, result_scale);
    return result;
}

int s21_sub_without_scale(s21_decimal value1, s21_decimal value2,
                          s21_decimal *result) {
    s21_decimal_init(result);
    int ret = 0;
    int reminder = 0;
    if (!s21_get_bit(value1, 127) && s21_get_bit(value2, 127)) {
        s21_negate(value2, &value2);
        ret = s21_add_without_scale(value1, value2, result);
    } else if (s21_get_bit(value1, 127) && !s21_get_bit(value2, 127)) {
        s21_set_bit(&value2, 127, 1);
        ret = s21_add_without_scale(value1, value2, result);
    } else {
        if (s21_get_bit(value1, 127) && s21_get_bit(value2, 127)) {
            s21_negate(value2, &value2);
            s21_negate(value1, &value1);
            s21_swap_values(&value1, &value2);
        }
        if (!s21_is_greater_or_equal(value1, value2)) {
            s21_set_bit(result, 127, 1);
            s21_swap_values(&value1, &value2);
        }
        for (int i = 0; i < 96; i++) {
            if (s21_get_bit(value1, i) - s21_get_bit(value2, i) == 0) {
                if (reminder == 1) {
                    s21_set_bit(result, i, 1);
                }
            } else if (s21_get_bit(value1, i) - s21_get_bit(value2, i) == 1) {
                if (reminder == 0)
                    s21_set_bit(result, i, 1);
                else
                    reminder = 0;
            } else if (s21_get_bit(value1, i) - s21_get_bit(value2, i) == -1) {
                if (reminder != 1) {
                    s21_set_bit(result, i, 1);
                    reminder = 1;
                } else {
                    reminder = 1;
                }
            }
            if (i == 95 && reminder) {
                if (s21_get_bit(*result, 127))
                    ret = 2;
                else
                    ret = 1;
            }
        }
    }
    return ret;
}

void s21_swap_values(s21_decimal *value1, s21_decimal *value2) {
    s21_decimal value2_tmp = *value2;
    *value2 = *value1;
    *value1 = value2_tmp;
}

int s21_add_without_scale(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result) {
    int result_Function = 0;
    if (s21_get_bit(value_1, 127) != s21_get_bit(value_2, 127)) {
        s21_decimal value_1tmp = value_1;
        s21_decimal value_2tmp = value_2;
        if (s21_get_bit(value_1, 127))
            s21_negate(value_1, &value_1tmp);
        else
            s21_negate(value_2, &value_2tmp);
        result_Function = s21_sub_without_scale(value_1tmp, value_2tmp, result);
        if (s21_get_bit(value_1, 127) && s21_is_greater(value_1, value_2))
            s21_negate(*result, result);
        else if (s21_is_greater(value_2, value_1))
            s21_negate(*result, result);
    } else {
        int check_minus;
        int in_mind = 0;
        s21_decimal temp = {{0, 0, 0, 0}};
        if (s21_get_bit(value_1, 127) == 1) s21_set_bit(&temp, 127, 1);
        for (int i = 0; i < 96; i++) {
            if (s21_get_bit(value_1, i) && s21_get_bit(value_2, i)) {
                if (in_mind) s21_set_bit(&temp, i, 1);
                in_mind = 1;
            } else if (s21_get_bit(value_1, i) || s21_get_bit(value_2, i)) {
                if (!in_mind) s21_set_bit(&temp, i, 1);
            } else if (in_mind) {
                s21_set_bit(&temp, i, 1);
                in_mind = 0;
            }
            if (i == 95 && in_mind) {
                check_minus = s21_sign_minus(temp);
                if (check_minus == 1)
                    result_Function = 2;
                else
                    result_Function = 1;
            }
        }
        *result = temp;
    }
    return result_Function;
}

int s21_shift_left(s21_decimal *dec, int shift) {
    int ret_val = 0;
    int highest_bit = s21_get_higher_bit(*dec);
    if (highest_bit + shift > 95) {
        ret_val = 1;
    } else {
        for (int i = 0; i < shift; i++) {
            int last_low_bit_set = s21_get_bit(*dec, 31);
            int last_mid_bit_set = s21_get_bit(*dec, 63);
            dec->bits[0] = dec->bits[0] << 1;
            dec->bits[1] = dec->bits[1] << 1;
            dec->bits[2] = dec->bits[2] << 1;
            if (last_low_bit_set) s21_set_bit(dec, 32, 1);
            if (last_mid_bit_set) s21_set_bit(dec, 64, 1);
        }
    }
    if (s21_get_bit(*dec, 127) && ret_val) ret_val = 2;
    return ret_val;
}
