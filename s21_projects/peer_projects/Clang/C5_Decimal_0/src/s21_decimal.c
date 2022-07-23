#include "s21_decimal.h"

int getbit(s21_decimal value, int i) {
    int result = (value.bits[i / 32] >> i % 32) & 1;
    return result;
}

void setbit(s21_decimal *result, int r, int i) {
    if (r == 1)
        result->bits[i / 32] = result->bits[i / 32] | (1 << i % 32);
    if (r == 0)
        result->bits[i / 32] = result->bits[i / 32] & ~(1 << i % 32);
}

void s21_init_decimal(s21_decimal *dec) {
  dec->bits[0] = dec->bits[1] = dec->bits[2] = dec->bits[3] = 0;
}

int s21_get_float_exp(float *src) {
  return ((*(int *)src & ~0x80000000) >> 23) - 127;  //  достаем экспаненту флота
}

void s21_set_sign(s21_decimal *value, int sign) {
  unsigned int mask = 0x80000000;  // 31 bit for minus
  if (sign != 0) {
    value->bits[3] |= mask;  // up flag
  } else {
    value->bits[3] &= ~mask;   // maskiruet down flag
  }
}

int s21_get_sign(s21_decimal *value) {
  unsigned int mask = 0x80000000;
  int result = value->bits[3] & mask;
  return result;
}

int degree_for_float(s21_decimal src) {
    s21_set_sign(&src, 0);
    int degree = src.bits[3] >> 16;
    return degree;
}

int s21_get_int_for_float(s21_decimal src, int *int_to_float) {
    char result = OK;
    s21_decimal temp = src;
    int degree = degree_for_float(src);
    s21_decimal ten = {{10, 0, 0, 0}};
    for (int i = 1; i <= degree; i++) {
        s21_div(temp, ten, &temp);
    }
    if (temp.bits[1] == 0 && temp.bits[2] == 0) {
        result = s21_from_decimal_to_int(temp, int_to_float);
        *int_to_float = abs(*int_to_float);
    } else {
        result = CONVERTING_ERROR;
    }
    return result;
}

int s21_sub_light(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_init_decimal(result);
    int v1 = 0, v2 = 0, r = 0, f = 1, s1 = 0, s2 = 0;
    s1 = getbit(value_1, 127);
    s2 = getbit(value_2, 127);
    if ((s1 ^ s2) == 0) {
        for (int i = 0; i < 96; i++) {
            v1 = getbit(value_1, i);
            v2 = getbit(value_2, i);
            if (f == 0) {
                if (v1)
                    f = 1;
                v1 = !v1;
            }
            r = v1 ^ v2;
            if (!v1 && v2)
                f = 0;
            setbit(result, r, i);
        }
    } else {
        setbit(&value_1, (0), 127);
        setbit(&value_2, (0), 127);
        s21_add(value_1, value_2, result);
        if (s1)
            setbit(result, 1, 127);
    }
    return 0;
}

int s21_mod_light(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_init_decimal(result);
    s21_decimal r = {{0, 0, 0, 0}};
    s21_decimal r2 = {{0, 0, 0, 0}};
    s21_div(value_1, value_2, &r);
    s21_mul(r, value_2, &r2);
    s21_sub_light(value_1, r2, result);
    return 0;
}

int s21_get_frac_for_float(s21_decimal src) {
    int frac_to_float;
    int int_to_float;
    s21_decimal temp = src;
    s21_decimal temp_frac = src;
    s21_decimal ten_frac = {{1, 0, 0, 0}};
    s21_decimal ten_frac_res = {{0, 0, 0, 0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal res = {{0, 0, 0, 0}};
    int degree;
    if (s21_get_int_for_float(src, &int_to_float) != 0) {
        frac_to_float = 0;
    } else {
        degree = degree_for_float(src);
        for (int i = 1; i <= degree; i++) {
            s21_div(temp, ten, &res);
            temp = res;
            s21_mul(ten_frac, ten, &ten_frac_res);  // pow(10,degree) for decimal
            ten_frac = ten_frac_res;
        }
        s21_decimal res_frac = temp_frac;  //  {0, 0, 0, 0};
        s21_mod_light(res_frac, ten_frac, &res_frac);
        while (res_frac.bits[1] != 0 || res_frac.bits[2] != 0) {
           s21_div(res_frac, ten, &res_frac);
        }
        s21_from_decimal_to_int(res_frac, &frac_to_float);
    }
    return frac_to_float;
}

/////////////////////// TANYA & ALYONA //////////////////

s21_decimal dislocation(s21_decimal value, int i) {
    int v;
    s21_decimal result = {{0, 0, 0, 0}};
    for (int k = 2; k >= 0; k--) {
        if (i < 32)
            result.bits[k] = value.bits[k] << i;
        for (int p = 32 * k - 1; p >= 0 && k != 0; p--) {
            v = getbit(value, p);
            if (v) {
                setbit(&result, v, p + i);
            }
        }
    }
    return result;
}

int getdegree(s21_decimal value) {
    int result = 1 * getbit(value, 112) + 2 * getbit(value, 113)
    + 4 * getbit(value, 114) + 8 * getbit(value, 115) + 16 * getbit(value, 116);
    return result;
}

s21_decimal equalization(s21_decimal value, int difference) {
    s21_decimal tmp1 = value;
    s21_decimal tmp2 = value;
    s21_decimal tmp = value;
    for (int k = difference; k > 0; k--) {
        tmp1 = dislocation(tmp, 1);
        tmp2 = dislocation(tmp, 3);
        s21_add(tmp1, tmp2, &tmp);
    }
    difference = difference << 16;
    tmp.bits[3] = value.bits[3] + difference;
    return tmp;
}

int choose_degree(s21_decimal *value_1, s21_decimal *value_2) {
    int bug = 0;
    int degree_1 = getdegree(*value_1);
    int degree_2 = getdegree(*value_2);
    if (degree_1 > 28 || degree_2 > 28)
        bug = 2;
    if (degree_1 < degree_2) {
        *value_1 = equalization(*value_1, degree_2 - degree_1);
    }
    if (degree_1 > degree_2) {
        *value_2 = equalization(*value_2, degree_1 - degree_2);
    }
    return bug;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_init_decimal(result);
    int bug = 0;
    int v1 = 0, v2 = 0, r = 0, f = 0, s1 = 0, s2 = 0;
    s1 = getbit(value_1, 127);
    s2 = getbit(value_2, 127);
    bug = choose_degree(&value_1, &value_2);
    result->bits[3] = value_2.bits[3];
    if ((s1 ^ s2) == 0) {
        if (s1 & s2)
            setbit(result, 1, 127);
        for (int i = 0; i < 96; i++) {
            v1 = getbit(value_1, i);
            v2 = getbit(value_2, i);
            r = v1 ^ v2;
            if (f == 1) {
                r = r ^ f;
                if (r)
                    f = 0;
            }
            if (v1 & v2)
                f = 1;
            setbit(result, r, i);
            if (i == 95 && f == 1)
                bug = 1;
        }
    } else {
        setbit(&value_1, (0), 127);
        setbit(&value_2, (0), 127);
        if (s1)
            s21_sub(value_2, value_1, result);
        if (s2)
            s21_sub(value_1, value_2, result);
    }
    return bug;
}


int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_init_decimal(result);
    int bug = 0;
    int v1 = 0, v2 = 0, r = 0, f = 1, s1 = 0, s2 = 0;
    s1 = getbit(value_1, 127);
    s2 = getbit(value_2, 127);
    bug = choose_degree(&value_1, &value_2);
    result->bits[3] = value_2.bits[3];
    setbit(&value_1, (0), 127);
    setbit(&value_2, (0), 127);
    if (s21_is_greater(value_2, value_1)) {
        s21_decimal tmp = value_1;
        value_1 = value_2;
        value_2 = tmp;
        if (!s2)
            setbit(result, 1, 127);
        if (s2)
            setbit(result, 0, 127);
    }
    if ((s1 ^ s2) == 0) {
        for (int i = 0; i < 96; i++) {
            v1 = getbit(value_1, i);
            v2 = getbit(value_2, i);
            if (f == 0) {
                if (v1)
                    f = 1;
                v1 = !v1;
            }
            r = v1 ^ v2;
            if (!v1 && v2)
                f = 0;
            setbit(result, r, i);
        }
    } else {
        setbit(&value_1, (0), 127);
        setbit(&value_2, (0), 127);
        bug = s21_add(value_1, value_2, result);
        if (s1)
            setbit(result, 1, 127);
    }
    return bug;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_init_decimal(result);
    int v2 = 0, s1 = 0, s2 = 0;
    s21_decimal tmp = {{0, 0, 0, 0}};
    s1 = getbit(value_1, 127);
    s2 = getbit(value_2, 127);
    for (int i = 0; i < 96; i++) {
        v2 = getbit(value_2, i);
        if (v2) {
            tmp = dislocation(value_1, i);
            s21_add(*result, tmp, result);
        }
    }
    int degree_1 = getdegree(value_1);
    int degree_2 = getdegree(value_2);
    int degree_3 = degree_1 + degree_2;
    degree_3 = degree_3 << 16;
    result->bits[3] = result->bits[3] + degree_3;
    if ((s1 ^ s2) == 1)
        setbit(result, 1, 127);
    return 0;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_init_decimal(result);
    s21_decimal r = {{0, 0, 0, 0}};
    s21_decimal r2 = {{0, 0, 0, 0}};
    s21_div(value_1, value_2, &r);
    s21_mul(r, value_2, &r2);
    s21_sub(value_1, r2, result);
    return 0;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int cnt = 0;
    if (getbit(value_1, 127) == getbit(value_2, 127)) {
        for (int bits = 2; bits >= 0; bits--) {
            for (int i = 32 * bits + 31; i >= 32 * bits; i--) {
                if (getbit(value_1, i) != getbit(value_2, i)) {
                    break;
                }
                cnt++;
            }
        }
    }
    return cnt == 96 ? 1 : 0;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
    return !s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    return s21_is_less_or_equal(value_1, value_2) && s21_is_not_equal(value_1, value_2);
}
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
    choose_degree(&value_1, &value_2);
    int less = 1;
    int minus = 0;
    int cnt = 0;
    int break_counter = 0;
    if (getbit(value_1, 127) == 1 && getbit(value_2, 127) == 1)
        minus = 1;
    if (!(getbit(value_1, 127) == 1 && getbit(value_2, 127) == 0)) {
        if ((getbit(value_1, 127) == 0 && getbit(value_2, 127) == 1)) {
            less = 0;
        } else {
            for (int bits = 2; bits >= 0; bits--) {
              if (break_counter == 1)
                break;
              for (int i = 32 * bits + 31; i >= 32 * bits; i--) {
                  if (getbit(value_1, i) != getbit(value_2, i)) {
                      if (getbit(value_1, i) == 1)
                          less = 0;
                      break_counter = 1;
                      break;
                  }
                  cnt++;
              }
            }
        }
    }
    if (cnt == 96)
        minus = 0;
    return !minus ? less : !less;
}

int s21_is_less_or_equal_light(s21_decimal value_1, s21_decimal value_2) {
    int less = 1;
    int minus = 0;
    int cnt = 0;
    int break_counter = 0;
    if (getbit(value_1, 127) == 1 && getbit(value_2, 127) == 1)
        minus = 1;
    if (!(getbit(value_1, 127) == 1 && getbit(value_2, 127) == 0)) {
        if ((getbit(value_1, 127) == 0 && getbit(value_2, 127) == 1)) {
            less = 0;
        } else {
            for (int bits = 2; bits >= 0; bits--) {
              if (break_counter == 1)
                break;
              for (int i = 32 * bits + 31; i >= 32 * bits; i--) {
                  if (getbit(value_1, i) != getbit(value_2, i)) {
                      if (getbit(value_1, i) == 1)
                          less = 0;
                      break_counter = 1;
                      break;
                  }
                  cnt++;
              }
            }
        }
    }
    if (cnt == 96)
        minus = 0;
    return !minus ? less : !less;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    return !s21_is_less_or_equal(value_1, value_2);
}
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
    return s21_is_less_or_equal(value_2, value_1);
}

int s21_is_greater_or_equal_light(s21_decimal value_1, s21_decimal value_2) {
    return s21_is_less_or_equal_light(value_2, value_1);
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_init_decimal(result);
    int bug = 0;
    s21_decimal nul = {{0, 0, 0, 0}};
    if (s21_is_equal(value_2, nul))
        bug =  3;
    int v1 = 0, v2 = 0, p = 95, i = 95, b = 0, s1 = 0, s2 = 0;
    s21_decimal r = value_1;
    s1 = getbit(value_1, 127);
    s2 = getbit(value_2, 127);
    for (; !v1; i--) {
        v1 = getbit(value_1, i);
    }
    for (; !v2; p--) {
        v2 = getbit(value_2, p);
    }
    s21_decimal tmp = dislocation(value_2, i -= p);
    setbit(&r, (0), 127);
    setbit(&value_2, (0), 127);
    while (i >= 0) {
        if (s21_is_less_or_equal_light(tmp, r)) {
            s21_sub_light(r, tmp, &r);
            b = 1;
        }
        setbit(result, b, i);
        tmp = dislocation(value_2, i -= 1);
        b = 0;
    }
    if ((s1 ^ s2) == 1)
        setbit(result, 1, 127);
    return bug;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if (value.bits[3] == -2147483648) {
        *result = value;
    } else {
        s21_truncate(value, result);
        s21_decimal sub_value = {{1, 0, 0, 0}};
        if (getbit(*result, 127) == 1) {
            s21_sub_light(*result, sub_value, result);
        }
    }
    return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    int error = 0;
    int degree_exponent = 1 * getbit(value, 112) + 2 * getbit(value, 113)
    + 4 * getbit(value, 114) + 8 * getbit(value, 115) + 16 * getbit(value, 116);

    if (degree_exponent != 0) {
        s21_decimal tmp = value;
        for (int i = 119; i >= 112; i--) {
            setbit(&tmp, 0, i);
        }
        s21_decimal zero = {{0, 0, 0, 0}};
        s21_decimal ten = {{10, 0, 0, 0}};
        s21_decimal mod_ten = {{0, 0, 0, 0}};
        s21_decimal tmp_mod_ten = {{1, 0, 0, 0}};
        for (int i = 1; i <= degree_exponent; i++) {
            s21_div(tmp, ten, result);
            tmp = *result;
            if (i != degree_exponent) {
                *result = zero;
            }
            s21_mul(tmp_mod_ten, ten, &mod_ten);
            tmp_mod_ten = mod_ten;
            if (i != degree_exponent) {
                mod_ten = zero;
            }
        }
        s21_decimal mod_res = {{0, 0, 0, 0}};
        s21_mod_light(value, mod_ten, &mod_res);
        s21_decimal last_num = zero;
        s21_decimal five = {{5, 0, 0, 0}};
        s21_decimal one = {{1, 0, 0, 0}};
        s21_decimal mod_ten_div = zero;
        s21_div(mod_ten, ten, &mod_ten_div);
        s21_div(mod_res, mod_ten_div, &last_num);
        if (s21_is_greater_or_equal_light(last_num, five)) {
            if (getbit(value, 127) == 0) {
                s21_add(*result, one, result);
            } else {
                s21_sub_light(*result, one, result);
            }
        }
    } else {
        *result = value;
    }
    return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int error = 0;
    s21_decimal tmp = value;
    int degree_exponent = 1 * getbit(value, 112) + 2 * getbit(value, 113)
    + 4 * getbit(value, 114) + 8 * getbit(value, 115) + 16 * getbit(value, 116);
    for (int i = 119; i >= 112; i--) {
        setbit(&tmp, 0, i);
    }
    if (degree_exponent) {
        s21_decimal zero = {{0, 0, 0, 0}};
        s21_decimal ten = {{10, 0, 0, 0}};
        for (int i = 1; i <= degree_exponent; i++) {
            s21_div(tmp, ten, result);
            tmp = *result;
            if (i != degree_exponent) {
                *result = zero;
            }
        }
    } else {
        *result = value;
    }
    return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    int error = 0;
    *result = value;
    if (getbit(value, 127) == 0) {
        setbit(result, 1, 127);
    } else {
        setbit(result, 0, 127);
    }
    return error;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  char result = OK;
    if (dst) {
      s21_init_decimal(dst);
      if (src < 0) {
        s21_set_sign(dst, 1);  //  sign
        src = abs(src);  // otbrosit znak
      }
      dst->bits[0] = src;
    } else {
      result = CONVERTING_ERROR;
    }
    return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  char result = CONVERTING_ERROR;
  unsigned int mask = 0x7F0000;
    if ((src.bits[3] & mask) == 0) {    // если нет степени
        if (src.bits[1] == 0 && src.bits[2] == 0) {
            if (src.bits[0] <= INT_MAX) {
                *dst = src.bits[0];
                if (s21_get_sign(&src) != 0 && src.bits[0] <= (INT_MAX -1)) {
                    *dst *= -1;
                }
                result = OK;
            }
        }
    } else {
        s21_get_int_for_float(src, dst);
    }
  return result;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = OK;
  if (dst) {
    s21_init_decimal(dst);
    if (fabs(src) < 1e-28) {
      result = CONVERTING_ERROR;
      src = 0;
    } else if (fabs(src) > s21_MAX_FLOAT || isinf(src)) {
      result = CONVERTING_ERROR;
    } else {
        result = CONVERTING_ERROR;
      int exp = s21_get_float_exp(&src);

      if (dst && src != 0) {
        double temp = (double)fabs(src);
        int off = 0;
        for (; off < 28 && (int)temp / 0x200000 == 0; temp *= 10, off++) {}
        temp = round(temp);
        if (off <= 28 && (exp > -94 && exp < 96)) {
          floatbits mant;
          temp = (float)temp;
          for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {}
          mant.fl = temp;
          exp = s21_get_float_exp(&mant.fl);
          dst->bits[exp / 32] |= 1 << exp % 32;
          for (int i = exp - 1, j = 22; j >= 0; i--, j--) {
            unsigned long int bit = 1 << (i % 32);
            if ((mant.ui & (1 << j)) != 0) dst->bits[i / 32] |= bit;
          }
           dst->bits[3] = (off << 16);
          if (src < 0) {
            s21_set_sign(dst, 1);
            src = fabs(src);  //  otbrosit znak
          }
          result = OK;
        }
      }
    }
  } else {
    result = CONVERTING_ERROR;
  }
  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    char result = OK;
    int degree = 0;
    int sign = 0;
    int int_to_float = 0;
    double float_frac = 0;
    if ((src.bits[3] & 0x80000000) > 0) {
        sign = 1;  // флаг отрицательного числа
    }
    int a = s21_get_frac_for_float(src);
    while (a > 0) {
        a /= 10;
        degree++;
    }
    result = s21_get_int_for_float(src, &int_to_float);
    if (result == OK) {
        float_frac = s21_get_frac_for_float(src) * pow(10, -degree);
        *dst = int_to_float + float_frac;
        if (sign) {
            *dst *= -1;
        }
    }
    return result;
}
