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
/             БЛОК ФУНКЦИЙ МАТЕМАТИЧЕСКИХ ОПЕРАЦИЙ               /
/                                                                /
/===============================================================*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal DifMax;
  s21_decimal MaxValue = {{BITS_MAX, BITS_MAX, BITS_MAX, 0}};
  MakeZeroDecimal(result);
  MakeScaleEqual(&value_1, &value_2);  // понижение степеней

  /*          Отбрасывание дробной части при переполнении         */
  if (getSign(value_1) == getSign(value_2)) {
    getInversionBits(MaxValue, value_2, &DifMax);
    while (getAbsoluteComparison(value_1, DifMax) == BIGGER) {
      if ((getAbsoluteComparison(value_1, DifMax) == BIGGER) &&
          (getScale(value_1) != 0)) {
        MakeScaleLessOne(&value_1, &value_2);
        getInversionBits(value_2, MaxValue, &DifMax);
      }
      if ((getAbsoluteComparison(value_1, DifMax) == BIGGER) &&
          (getScale(value_1) == 0)) {
        error = 1;
      }
      break;
    }
  }

  if ((getSign(value_1) == getSign(value_2))) {
    getSum(value_1, value_2, result);
    if (getSign(value_1) && getSign(value_2))
      setSign(result, 1);
    else
      setSign(result, 0);
  }
  if ((getSign(value_1) != getSign(value_2))) {
    if (getAbsoluteComparison(value_1, value_2) == BIGGER) {
      getSub(value_1, value_2, result);
      if (getSign(value_1))
        setSign(result, 1);
      else
        setSign(result, 0);
    } else if (getAbsoluteComparison(value_2, value_1) == BIGGER) {
      getSub(value_2, value_1, result);
      if (getSign(value_1))
        setSign(result, 0);
      else
        setSign(result, 1);
    }
  }
  setScale(result, getScale(value_2));
  if (getScale(*result) > 28 ||
      (getScale(*result) == 28 && result->bits[LOW] == 0 &&
       result->bits[MID] == 0 && result->bits[HIGH] == 0))
    error = 2;
  if (error != 0) MakeZeroDecimal(result);
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int f_result = OK;
  MakeZeroDecimal(result);
  MakeScaleEqual(&value_1, &value_2);

  s21_decimal MaxDecimal = {{BITS_MAX, BITS_MAX, BITS_MAX, 0}};
  s21_decimal tmp;
  MakeZeroDecimal(&tmp);
  if (getSign(value_1) != getSign(value_2)) {
    getSub(MaxDecimal, value_2, &tmp);
    while (getAbsoluteGreater(value_1, tmp)) {
      if (getAbsoluteGreater(value_1, tmp) && getScale(value_1) != 0) {
        MakeScaleLessOne(&value_1, &value_2);
        getSub(MaxDecimal, value_2, &tmp);
      }
      if (getAbsoluteGreater(value_1, tmp) && getScale(value_2) == 0) {
        f_result = INF;
      }
      break;
    }
  }
  CheckOperationsForSub(value_1, value_2, result);
  setScale(result, getScale(value_1));
  int result_scale = getScale(*result);
  if (result_scale > 28 ||
      (result_scale == 28 && CheckDecimal_isZero(*result) == 1)) {
    f_result = N_INF;
  }
  if (f_result != OK) {
    MakeZeroDecimal(result);
  }
  return f_result;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int f_result = OK;
  MakeZeroDecimal(result);

  s21_decimal Ten = {{10, 0, 0, 0}};
  s21_decimal MaxDecimal = {{BITS_MAX, BITS_MAX, BITS_MAX, 0}};
  s21_decimal tmp;
  MakeZeroDecimal(&tmp);

  if (CheckDecimal_isZero(value_2)) {
    MakeZeroDecimal(result);
  } else {
    while (getScale(value_1) + getScale(value_2) >= 28) {
      if (getAbsoluteGreater(value_1, Ten) == 0 &&
          getAbsoluteGreater(value_2, Ten) == 0) {
        break;
      }
      if (getScale(value_1) + getScale(value_2) == 28) {
        break;
      }
      if ((getScale(value_1) >= getScale(value_2) &&
           getAbsoluteGreater(value_1, Ten)) ||
          (getAbsoluteGreater(value_2, Ten) == 0 &&
           getAbsoluteGreater(value_1, Ten))) {
        int s_value1 = getScale(value_1);
        getDiv(value_1, Ten, &value_1);
        setScale(&value_1, s_value1 - 1);
        continue;
      }
      if (getAbsoluteGreater(value_2, Ten) == BIGGER) {
        int s_value2 = getScale(value_2);
        getDiv(value_2, Ten, &value_2);
        setScale(&value_2, s_value2 - 1);
      }
    }

    if (CheckDecimal_isZero(value_2) == 0) {
      getDiv(MaxDecimal, value_2, &tmp);
      if (getAbsoluteGreater(value_1, tmp) == BIGGER) {
        f_result = INF;
      }
    }

    getMullCheckingSign(value_1, value_2, result);
    setScale(result, getScale(value_1) + getScale(value_2));
    while (getScale(*result) >= 28) {
      if (CheckDecimal_isZero(*result) == 1) {
        f_result = N_INF;
        break;
      }
      if (getScale(*result) == 28) {
        break;
      }
      if (CheckDecimal_isZero(*result) == 0) {
        int s_result = getScale(*result);
        getDiv(*result, Ten, result);
        setScale(result, s_result - 1);
      }
    }
    if (f_result != OK) {
      MakeZeroDecimal(result);
    }
  }
  return f_result;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  MakeZeroDecimal(result);
  int f_result = 0, scale_of_result, sign_result = 0;
  scale_of_result = getScale(value_1) - getScale(value_2);
  s21_decimal scale_1 = {{10, 0, 0, 0}};
  s21_decimal divisor = {{0, 0, 0, 0}};
  if (getSign(value_1) != getSign(value_2)) sign_result = 1;
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 &&
      value_2.bits[2] == 0) {  // проверка деление на 0
    f_result = N_NAN;
  } else {
    getDivMod(value_1, value_2, result, &divisor);
    while (CheckDecimal_isZero(divisor) == 0 &&
           getConsiderableLength(*result) < 93 && scale_of_result < 28) {
      getMul(value_1, scale_1, &value_1);
      scale_of_result++;
      getDivMod(value_1, value_2, result, &divisor);
    }
  }
  while (scale_of_result < 0) {
    getMul(*result, scale_1, result);
    scale_of_result++;
    if (getConsiderableLength(*result) > 93 && scale_of_result < 0)
      f_result = INF;
  }
  setScale(result, scale_of_result);
  if (sign_result == 1) setSign(result, 1);
  if (getScale(*result) > 28 && f_result != N_NAN) f_result = N_INF;
  if (f_result != OK) MakeZeroDecimal(result);
  return f_result;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int f_result = OK;
  int ScaleResult = 0;
  MakeZeroDecimal(result);

  s21_decimal divisor = {{0, 0, 0, 0}};
  if (CheckDecimal_isZero(value_2)) {
    f_result = N_NAN;
  } else {
    MakeScaleEqualMod(&value_1, &value_2);
    ScaleResult = getScale(value_1);
    getDivMod(value_1, value_2, result, &divisor);
  }
  *result = divisor;
  setScale(result, ScaleResult);
  if (getScale(*result) > 28 && f_result != N_NAN) {
    f_result = N_INF;
  }
  if (f_result != OK) {
    MakeZeroDecimal(result);
  }
  return f_result;
}

#undef _S21_DECIMAL_CONSTANTS
