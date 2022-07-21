#include "s21_decimal.h"

/*______arithmetic_operations______*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    if (result == NULL || value_1.exp > 28 || value_2.exp > 28) error = 1;
    /* value_1 <= value_2 (1)
       value_1 >  value_2 (0)
    */
    if (!error) {
        full_clean(result);
        int compRes = abs_dec(value_1, value_2); /* 1 or 0 */
        /* operation variant */
        if (!value_1.sign && !value_2.sign) { /* обычное сложение */
            error = addition(value_1, value_2, result);
        } else if (value_1.sign &&
                   value_2.sign) { /* сложение двух отрицательных */
            result->sign = 1;
            error = addition(value_1, value_2, result);
            if (error) error = 2;
        } else if ((!value_1.sign && value_2.sign) || /* вычитание двух чисел */
                   (value_1.sign && !value_2.sign)) {
            result->sign = (compRes) ? value_2.sign : value_1.sign;
            error = (compRes) ? subtraction(value_2, value_1, result)
                              : subtraction(value_1, value_2, result);
            replace_neg_zero(result);
        }
    }
    if (error || (last_bit_dec(*result) == -1)) full_clean(result);
    return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    if (result == NULL) error = 1;
    /* value_1 <= value_2 (1)
      value_1 >  value_2 (0)
   */
    if (!error) {
        full_clean(result);
        int compRes = abs_dec(value_1, value_2); /* 1 or 0 */
        /* operation variant */
        if (!value_1.sign && !value_2.sign) {
            result->sign = (compRes) ? 1 : 0;
            error = (compRes) ? subtraction(value_2, value_1, result)
                              : subtraction(value_1, value_2, result);
            replace_neg_zero(result);
        } else if ((value_1.sign && !value_2.sign) ||
                   (!value_1.sign && value_2.sign)) {
            result->sign = (value_1.sign) ? 1 : 0;
            error = (addition(value_1, value_2, result)) ? 2 : 0;
        } else if (value_1.sign && value_2.sign) {
            result->sign = (compRes) ? 0 : 1;
            error = (compRes) ? subtraction(value_2, value_1, result)
                              : subtraction(value_1, value_2, result);
            replace_neg_zero(result);
        }
    }
    if (error || (last_bit_dec(*result) == -1)) full_clean(result);
    return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int err = 0;
    s21_decimal x = value_1, y = value_2, z = {{0}};
    if (result != NULL) {
        if (value_1.exp > 28 || value_2.exp > 28) {
            err = 2;
        } else {
            if (!err) {
                while (1) {
                    if (((multiply(x, y, &z) == 1) || (x.exp + y.exp > 28)) &&
                        err == 0) {
                        err = 1;
                        if (get_first_bit(x) - get_first_bit(y) <= 0 &&
                            (x.exp < y.exp)) {
                            if (round_one(y, &y)) err = 1;
                        } else {
                            if (round_one(x, &x)) err = 1;
                        }
                    } else {
                        break;
                    }
                }
                *result = z;
                (*result).exp = x.exp + y.exp;
                (*result).sign = -(value_1.sign - value_2.sign);
                err_clean(result, &err);
            }
        }
    }
    return err;
}

void div_int(s21_decimal dividend, s21_decimal divisor, s21_decimal *quotient,
             s21_decimal *rem) {
    s21_decimal original_divisor = divisor;
    shift_left(&divisor, (get_first_bit(dividend) - get_first_bit(divisor)));
    if (s21_is_greater_or_equal(dividend, divisor)) {
        set_bit(quotient, 0, 1);
        s21_sub(dividend, divisor, rem);
    } else {
        *rem = dividend;
    }

    while (s21_is_not_equal(divisor, original_divisor)) {
        shift_right(&divisor, 1);
        if (s21_is_greater_or_equal(*rem, divisor)) {
            shift_left(quotient, 1);
            set_bit(quotient, 0, 1);
            s21_sub(*rem, divisor, rem);
        } else {
            shift_left(quotient, 1);
        }
    }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    full_clean(result);
    s21_decimal tmp = {{1, 0, 0, 0}}, divisor = value_2, dividend = value_1,
                quotient = {{0}};
    int err = 0, sign = 1;
    if (result != NULL) {
        if (value_1.sign == value_2.sign) sign = 0;
        divisor.sign = 0;
        dividend.sign = 0;
        if (get_first_bit(value_2) == -1) {
            err = 3;
        } else if (get_first_bit(value_1) == -1) {
            full_clean(result);
        } else if ((get_first_bit(value_1) == 95 && s21_is_less(divisor, tmp) &&
                    sign) ||
                   (get_first_bit(value_2) == 95 &&
                    s21_is_less(dividend, tmp) && sign)) {
            err = 1;
        } else if ((get_first_bit(value_1) == 95 && s21_is_less(divisor, tmp) &&
                    !sign) ||
                   (get_first_bit(value_2) == 95 &&
                    s21_is_less(dividend, tmp) && !sign)) {
            err = 2;
        } else if (value_1.exp > 28 || value_2.exp > 28) {
            err = 2;
        } else if (get_first_bit(value_1) == -1) {
            clean(&quotient);
            sign = 0;
        } else if (s21_is_equal(dividend, divisor)) {
            clean(&quotient), quotient.mantysa[0] = 1;
        } else if (get_first_bit(value_2) == 0) {
            quotient = value_1;
        } else {
            err = cast_scale(&dividend, &divisor);
            while (!s21_is_less_or_equal(divisor, dividend) && !err) {
                if (quotient.exp < 28 && get_first_bit(dividend) < 93) {
                    mult_ten(&dividend);
                    quotient.exp++;
                } else {
                    err = 2;
                    full_clean(result);
                    break;
                }
            }
            while (!err) {
                div_int(dividend, divisor, &quotient, &tmp);
                if (get_first_bit(tmp) != -1) {
                    if (quotient.exp < 28 && get_first_bit(dividend) < 93) {
                        mult_ten(&dividend);
                        quotient.exp++;
                        clean(&quotient);
                        clean(&tmp);
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
        quotient.sign = sign;
        if (!err) (*result) = quotient;
        err_clean(result, &err);
    }
    return err;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    full_clean(result);
    s21_decimal tmp = {{1}};
    int err = 0, sign = 0;
    if (result != NULL) {
        if (!check_decimal(value_1) && !check_decimal(value_2)) {
            if (value_1.sign) sign = 1;
            value_1.sign = 0;
            value_2.sign = 0;
            if (get_first_bit(value_2) == -1) {
                err = 3;
            } else if (get_first_bit(value_1) == -1 ||
                       s21_is_equal(value_1, value_2)) {
                full_clean(result);
            } else {
                cast_scale(&value_1, &value_2);
                div_int(value_1, value_2, &tmp, result);
                (*result).sign = sign;
            }
        } else {
            err = 1;
        }
    }
    return err;
}

/*______functions_comparison______*/
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int res = 1;
    int sign_value_1 = value_1.sign;
    int sign_value_2 = value_2.sign;

    // если децималы равны
    if (s21_is_equal(value_1, value_2) == 1) {
        res = 0;
        // POSITIV < NEGATIV
    } else if (value_1.sign == 0 && value_2.sign == 1) {
        res = 0;
        // NEGATIV < POSITIV
    } else if (value_1.sign == 1 && value_2.sign == 0) {
        res = 1;
        // NEGATIV < NEGATIV
    } else if (value_1.sign == 1 && value_2.sign == 1) {
        value_1.sign = 0;
        value_2.sign = 0;
        res = s21_is_greater(value_1, value_2);
        // POSITIV < POSITIV
    } else if (sign_value_1 == 0 && sign_value_2 == 0) {
        res = less_positive(value_1, value_2);
    }
    return res;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;
    if (((value_1.sign == 1 && value_2.sign == 0) ||
         s21_is_equal(value_1, value_2) == 1) ||
        (s21_is_less(value_1, value_2)) == 1)
        res = 1;
    return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    return s21_is_less(value_2, value_1);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;
    if ((s21_is_equal(value_1, value_2) == 1) ||
        (s21_is_greater(value_1, value_2) == 1))
        res = 1;
    return res;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;  // 0 - FALSE, 1 - TRUE
    if (value_1.bits[0] == value_2.bits[0] &&
        value_1.bits[1] == value_2.bits[1] &&
        value_1.bits[2] == value_2.bits[2] &&
        value_1.bits[3] == value_2.bits[3])
        res = 1;
    return res;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;
    if (s21_is_equal(value_1, value_2) == 0) res = 1;
    return res;
}

/*______сonverter_functions______*/
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int error = 0;
    if (dst == NULL) error = 1;
    if (!error) {
        full_clean(dst);
        if (src < 0) {
            dst->sign = 1;
            src = -src;
        }
        dst->bits[0] = src;
    }
    return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int error = 0;
    int scale = 0;
    if ((src == 1 / 0.0 && src == 0 / 0.0 && src == -1 / 0.0 &&
         src == -0 / 0.0) ||
        dst == NULL) {
        error = 1;
    } else if (src) {
        full_clean(dst);
        s21_float floatDigit = {0};
        floatDigit.f = src;
        if ((dst->sign = floatDigit.sign)) {
            floatDigit.f = -floatDigit.f;
        }
        int expFloat = floatDigit.exp - 127;
        double dbl = floatDigit.f;
        while (scale < 28 && (int)dbl / (int)pow(2, 21) == 0) {
            dbl *= 10;
            scale++;
        }
        dbl = round(dbl);
        if (scale <= 28 && (expFloat > -94 && expFloat < 96)) {
            while (fmod(dbl, 10) == 0 && scale > 0) {
                dbl /= 10;
                scale--;
            }
            floatDigit.f = dbl;
            expFloat = floatDigit.exp - 127;
            set_bit(dst, expFloat, 1);
            int bitFloat = 0;
            for (int mantis = 22; mantis >= 0; mantis--) {
                bitFloat = (floatDigit.i >> mantis) & 1;
                set_bit(dst, --expFloat, bitFloat);
            }
            dst->exp = scale;
        } else {
            error = 1;
        }
    } else {
        full_clean(dst);
    }
    return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int error = 0;
    if (dst == NULL) error = 1;
    if (!error) {
        *dst = 0;
        s21_decimal integer = {0};
        s21_truncate(src, &integer);
        if ((!integer.bits[1] && !integer.bits[2] && !get_bit(integer, 31))) {
            *dst = integer.bits[0];
            if (src.sign) *dst = -*dst;
        } else {
            error = 1;
        }
    }
    return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int error = 0;
    if (dst == NULL || src.exp > 28) error = 1;
    if (!error) {
        *dst = 0.0;
        double d = *dst;
        unsigned long bits = 1;
        /*Переводим все битсы из мантисы с decimal to float*/
        for (int i = 0; i < 96; i++) {
            d += get_bit(src, i) * bits;
            bits = bits * 2;
        }
        /*Делим float на exp указанное в decimal*/
        if (src.exp != 0) {
            d /= pow(10, src.exp);
        }
        /*знак из decimal в float*/
        if (src.sign) d = -d;
        *dst = d;
    }
    return error;
}

/*______another_functions______*/
int s21_floor(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if (result == NULL || value.exp > 28) error = 1;
    if (!error) {
        full_clean(result);
        s21_decimal one = {{1}};
        s21_decimal res = {0};
        s21_decimal zero = {0};
        s21_truncate(value, result);
        if (value.sign) {
            subtraction(value, *result, &res);
            res.exp = 0;
            if (!s21_is_equal(res, zero)) {
                addition(one, *result, result);
            }
            result->sign = 1;
        }
    }
    return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if (result == NULL) error = 1;
    if (!error) {
        full_clean(result);
        s21_decimal one = {{1}};
        s21_decimal res = {0};
        int rem = 0;
        s21_truncate(value, result);
        subtraction(value, *result, &res);
        res.exp = value.exp - 1;
        s21_from_decimal_to_int(res, &rem);
        result->sign = 0;
        if (rem >= 5) {
            s21_add(one, *result, result);
        }
        if (value.sign) result->sign = 1;
    }
    return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if (result == NULL) error = 1;
    if (!error) {
        full_clean(result);
        s21_decimal tmp = value;
        s21_decimal ten = {0};
        ten.bits[0] = 10;
        int exp = value.exp;
        if (!exp) *result = value;
        while (exp) {
            counter_ranks(tmp, ten, result);
            tmp = *result;
            exp--;
        }
        if (value.sign) result->sign = 1;
    }
    return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if (result == NULL) error = 1;
    if (!error) {
        full_clean(result);
        *result = value;
        result->sign = !value.sign;
    }
    return error;
}

/*______secondary_functions______*/
int addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    int owerflow = 0;
    int cast = 0;
    if (value_1.exp != value_2.exp) cast = cast_scale(&value_1, &value_2);
    if (cast) {
        round_bank(value_2, &value_2);
        cast_scale(&value_1, &value_2);
    }
    result->exp = value_2.exp;
    for (int BitNum = 0; BitNum < 96; BitNum++) {
        int x = get_bit(value_1, BitNum);
        int y = get_bit(value_2, BitNum);
        set_bit(result, BitNum, ((x ^ y) ^ owerflow));
        owerflow = (x || y) ? (x & y) ^ owerflow : 0;
        owerflow = (x && y) ? 1 : (x & y) ^ owerflow;
    }
    if (owerflow) error = 1;  // Правильно обработай!

    return error;
}

int subtraction(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int owerflow = 0, err = 0;
    int cast = 0;
    if (value_1.exp != value_2.exp) cast = cast_scale(&value_1, &value_2);
    if (cast) {
        round_bank(value_2, &value_2);
        cast_scale(&value_1, &value_2);
    }
    result->exp = value_2.exp;
    for (int BITi = 0; BITi <= 95; BITi++) {
        int x = get_bit(value_1, BITi);
        int y = get_bit(value_2, BITi);
        set_bit(result, BITi, (x ^ y ^ owerflow));
        if (!x && y) {
            owerflow = 1;
        }
        if (x && !y) {
            owerflow = 0;
        }
    }
    if (owerflow) err = 2;  // Правильно обработай!
    return err;
}

int get_bit(s21_decimal src, int bitNum) {
    int mask = 1;
    int bits = (int)bitNum / 32;
    int bit = bitNum % 32;
    return ((src.bits[bits] >> bit) & mask);
}

int set_bit(s21_decimal *src, int bitNum, int sub) {
    int mask = 1;
    int bits = (int)bitNum / 32;
    int bit = bitNum % 32;
    if (sub) {
        src->bits[bits] |= (mask << bit);
    } else {
        src->bits[bits] &= ~(mask << bit);
    }
    return 0;
}

int cast_scale(s21_decimal *value_1, s21_decimal *value_2) {
    int error = 0;
    int ower = 0;
    s21_decimal *minExp = (value_1->exp < value_2->exp) ? value_1 : value_2;
    s21_decimal v1 = {{0}};
    s21_decimal v2 = {{0}};
    int deltaScale = value_1->exp - value_2->exp;
    if (deltaScale < 0) deltaScale = -deltaScale;
    int limitDec = 95 - last_bit_dec(*minExp);
    int checkScale = deltaScale * 3;
    int check = (checkScale > limitDec) ? 0 : 1;
    if (check) {
        if (deltaScale != 0) {
            if (deltaScale < 0) deltaScale *= -1;
            for (int i = 0; i < deltaScale; i++) {
                v1 = *minExp;
                v2 = *minExp;
                shift_left(&v1, 1);
                shift_left(&v2, 3);
                ower = addition(v1, v2, minExp);
            }
            minExp->exp =
                (value_1->exp < value_2->exp) ? value_2->exp : value_1->exp;
        }
    }
    if (!check || ower) error = 1;
    return error;
}

int less_positive(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;
    cast_scale(&value_1, &value_2);
    for (int i = 95; i >= 0; i--) {
        if ((get_bit(value_1, i) && get_bit(value_2, i)) ||
            (!get_bit(value_1, i) && !get_bit(value_2, i))) {
            continue;
        }

        if (!get_bit(value_1, i) && get_bit(value_2, i)) {
            res = 1;
            break;
        } else {
            res = 0;
            break;
        }
    }
    return res;
}

int abs_dec(s21_decimal value_1, s21_decimal value_2) {
    /* value_1 <= value_2 (true)*/
    int result = 0;
    s21_decimal *tmp1 = &value_1;
    s21_decimal *tmp2 = &value_2;
    tmp1->sign = 0;
    tmp2->sign = 0;
    result = s21_is_less_or_equal(*tmp1, *tmp2);
    return result;
}

int shift_left(s21_decimal *value, int moves) {
    int err = 0;
    s21_decimal tmp = *value;
    for (int i = 0; i < moves; i++) {
        for (int j = 95; j > 0; j--) {
            if (j == 95 && get_bit(tmp, j)) {
                err = 1, j = -1;
            } else {
                set_bit(&tmp, j, get_bit(tmp, j - 1));
            }
        }
        set_bit(&tmp, 0, 0);
    }
    if (err == 0) *value = tmp;
    return err;
}

int shift_right(s21_decimal *value, int moves) {
    s21_decimal tmp = *value;
    for (int i = 0; i < moves; i++) {
        for (int j = 0; j < 95; j++) {
            set_bit(&tmp, j, get_bit(tmp, j + 1));
        }
        set_bit(&tmp, 95, 0);
    }
    *value = tmp;
    return 0;
}

void replace_neg_zero(s21_decimal *result) {
    if (!result->bits[0] && !result->bits[1] && !result->bits[2] &&
        result->sign)
        result->sign = 0;
}

void full_clean(s21_decimal *target) {
    for (int i = 0; i < 4; i++) target->bits[i] = 0;
}

void counter_ranks(s21_decimal src, s21_decimal ten, s21_decimal *result) {
    s21_decimal remainder = {0};
    full_clean(result);
    // src.exp = 0;
    for (int i = last_bit_dec(src); i >= 0; i--) {
        if (get_bit(src, i)) set_bit(&remainder, 0, 1);
        if (s21_is_greater_or_equal(remainder, ten)) {
            s21_sub(remainder, ten, &remainder);
            if (i != 0) shift_left(&remainder, 1);
            if (get_bit(src, i - 1)) set_bit(&remainder, 0, 1);
            shift_left(result, 1);
            set_bit(result, 0, 1);
        } else {
            shift_left(result, 1);
            if (i) shift_left(&remainder, 1);
            if ((i - 1) >= 0 && get_bit(src, i - 1)) set_bit(&remainder, 0, 1);
        }
    }
}

int last_bit_dec(s21_decimal src) {
    int num = -1;
    for (int i = 95; i >= 0; i--) {
        if (get_bit(src, i)) {
            num = i;
            break;
        }
    }
    return num;
}

void clean(s21_decimal *value) {
    value->bits[0] = 0;
    value->bits[1] = 0;
    value->bits[2] = 0;
}

int get_first_bit(s21_decimal value) {
    int i = 95;
    for (; i >= 0; i--) {
        if (get_bit(value, i)) break;
    }
    return i;
}

void round_bank(s21_decimal value, s21_decimal *result) {
    s21_decimal one = {{1}};
    s21_decimal res = {0};
    int rem = 0;
    s21_truncate(value, result);
    subtraction(value, *result, &res);
    res.exp = value.exp - 1;
    s21_from_decimal_to_int(res, &rem);
    if (rem > 5) {
        s21_add(one, *result, result);
    }
    if (rem == 5) {
        if (get_bit(*result, 0)) s21_add(one, *result, result);
    }
}

int mult_ten(s21_decimal *value) {
    int err = 0;
    s21_decimal v1 = *value, v2 = *value;
    if (shift_left(&v1, 1) || shift_left(&v2, 3) || addition(v1, v2, value))
        err = 1;
    return err;
}

int round_one(s21_decimal value, s21_decimal *result) {
    int err = 0;
    if (value.exp == 0) {
        err = 1;
    } else {
        s21_decimal tmp = value;
        tmp.exp = 1;
        s21_round(tmp, result);
        (*result).exp = value.exp - 1;
    }
    return err;
}

int multiply(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int err = 0;
    full_clean(result);
    if (get_first_bit(value_1) != -1 && get_first_bit(value_2) != -1) {
        for (int i = 0; i < 95; i++) {
            s21_decimal temp = value_1;
            if (get_bit(value_2, i) == 1) {
                if (shift_left(&temp, i)) err = 1;
                addition(temp, *result, result);
            }
        }
    }
    return err;
}

void err_clean(s21_decimal *value, int *err) {
    if (*err) {
        if (value->sign) *err = 2;
        full_clean(value);
    }
}

int check_decimal(s21_decimal value) {
    int err = 0;
    if (value.exp > 28 || value.sign > 1 || value.jrNotUse != 0 ||
        value.mjNotUse != 0)
        err = 1;
    return err;
}
