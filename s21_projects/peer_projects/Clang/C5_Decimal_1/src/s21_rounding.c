#define _S21_DECIMAL_CONSTANTS
#define _SUPPORT_FUNCTIONS_
#include "./s21_decimal.h"

/*===============================================================/
/                                                                /
/                  S21_DECIMAL PROJECT SCHOOL 21                 /
/                               by                               /
/     tonitaga jerlenem nenitawi zoomdeni clotilde marselit      /
/                                                                /
/===============================================================*/

/*===============================================================/
/                                                                /
/               БЛОК ФУНКЦИЙ ОКРУГЛЕНИЯ ДЕЦИМАЛА                 /
/                                                                /
/===============================================================*/

/*     Просто берем и меняем знак с нуля на один и наоборот     */

int s21_negate(s21_decimal value, s21_decimal *result) {
  MakeZeroDecimal(result);
  *result = value;
  if (getSign(value) == 0) {
    setSign(result, 1);
  }
  if (getSign(value) == 1) {
    setSign(result, 0);
  }
  return ZERO;
}

/*    Создаем новый децимал который будет нам помогать уменьшать степень      */
/*    Узнаем знак и степень value затем делим value на 10, чтобы уменьшить    */
/*    степень value на один. Далее обратно устанавливаем знак и               */
/*    перекидывает в result                                                   */

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal Ten = {{10, 0, 0, 0}};
  MakeZeroDecimal(result);
  int sign = getSign(value);
  int scale = getScale(value);
  while (scale > 0) {
    getDiv(value, Ten, &value);
    scale--;
  }
  setSign(&value, sign);
  *result = value;
  return ZERO;
}

/*     Используя функцию s21_truncate при положительных      */
/*     децималах уже отброшена часть после запятой, т.е      */
/*     уже все округлено, но чтобы округлить отрицательное   */
/*     число в пол нужно от уже отброшенной дробной части    */
/*     отнять единицу                                        */

int s21_floor(s21_decimal value, s21_decimal *result) {
  MakeZeroDecimal(result);
  s21_decimal one = {{1, 0, 0, 0}};
  s21_truncate(value, &value);
  if (getSign(value) == 1) {
    s21_sub(value, one, &value);
  }
  *result = value;
  return ZERO;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  MakeZeroDecimal(result);

  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  s21_decimal tmp = value;
  int s_tmp = getScale(value);
  int s_value = getScale(value);
  int sign_value = getSign(value);

  while (s_value > 0) {
    if (s_value == 1) {
      tmp = value;
    }
    getDiv(value, ten, &value);
    s_value--;
  }

  if (s_tmp != 0) {
    getMul(value, ten, &value);
    getSub(tmp, value, &tmp);
    getDiv(value, ten, &value);
  } else {
    tmp.bits[LOW] = 0;
  }

  if (tmp.bits[LOW] >= 5) getSum(value, one, &value);
  setSign(&value, sign_value);
  *result = value;
  return 0;
}

#undef _S21_DECIMAL_CONSTANTS
