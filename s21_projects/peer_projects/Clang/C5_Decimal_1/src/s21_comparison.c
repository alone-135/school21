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
/             БЛОК ФУНКЦИЙ СРАВНЕНИЯ ДВУХ ДЕЦИМАЛОВ              /
/                                                                /
/===============================================================*/

int s21_is_equal(s21_decimal p1, s21_decimal p2) {
  int f_result = FALSE;
  MakeScaleEqual(&p1, &p2);
  if (getSign(p1) == getSign(p2) && getAbsoluteComparison(p1, p2) == EQUAL) {
    f_result = TRUE;
  }
  if (getSign(p1) != getSign(p2) && CheckDecimal_isZero(p1) &&
      CheckDecimal_isZero(p2)) {
    f_result = TRUE;
  }
  return f_result;
}

int s21_is_not_equal(s21_decimal p1, s21_decimal p2) {
  int f_result = TRUE;
  MakeScaleEqual(&p1, &p2);
  if (getSign(p1) == getSign(p2) && getAbsoluteComparison(p1, p2) == EQUAL) {
    f_result = FALSE;
  }
  if (getSign(p1) != getSign(p2) && CheckDecimal_isZero(p1) &&
      CheckDecimal_isZero(p2)) {
    f_result = FALSE;
  }
  return f_result;
}

int s21_is_greater_or_equal(s21_decimal p1, s21_decimal p2) {
  int f_result = FALSE;
  MakeScaleEqual(&p1, &p2);

  if (getSign(p1) == getSign(p2) && getAbsoluteComparison(p1, p2) == EQUAL) {
    f_result = TRUE;
  }
  if (getSign(p1) != getSign(p2) && CheckDecimal_isZero(p1) == 0 &&
      CheckDecimal_isZero(p2) == 0) {
    f_result = TRUE;
  }

  if (getSign(p1) == 0 && getSign(p2) == 1) {
    f_result = TRUE;
  }
  if (getSign(p1) == 0 && getSign(p2) == 0) {
    if (getAbsoluteComparison(p1, p2) == BIGGER ||
        getAbsoluteComparison(p1, p2) == EQUAL) {
      f_result = TRUE;
    }
  }
  if (getSign(p1) == 1 && getSign(p2) == 1) {
    if (getAbsoluteComparison(p1, p2) == LESS) {
      f_result = TRUE;
    }
  }
  if (getSign(p1) == 1 && getSign(p2) == 0) {
    f_result = FALSE;
  }
  return f_result;
}

int s21_is_greater(s21_decimal p1, s21_decimal p2) {
  int f_result = FALSE;
  MakeScaleEqual(&p1, &p2);

  if (getSign(p1) == 0 && getSign(p2) == 1) {
    if (CheckDecimal_isZero(p1) && CheckDecimal_isZero(p2))
      f_result = FALSE;
    else
      f_result = TRUE;
  }
  if (getSign(p1) == 0 && getSign(p2) == 0) {
    if (getAbsoluteComparison(p1, p2) == BIGGER) {
      f_result = TRUE;
    }
  }
  if (getSign(p1) == 1 && getSign(p2) == 1) {
    if (getAbsoluteComparison(p1, p2) == LESS) {
      f_result = TRUE;
    }
  }
  if (getSign(p1) == 1 && getSign(p2) == 0) {
    f_result = FALSE;
  }
  return f_result;
}

int s21_is_less_or_equal(s21_decimal p1, s21_decimal p2) {
  int check = 0;
  int f_result = TRUE;
  MakeScaleEqual(&p1, &p2);

  if (getSign(p1) == getSign(p2) && getAbsoluteComparison(p1, p2) == EQUAL) {
    check = 1;
    f_result = TRUE;
  }
  if (getSign(p1) != getSign(p2) && CheckDecimal_isZero(p1) &&
      CheckDecimal_isZero(p2)) {
    check = 1;
    f_result = TRUE;
  }

  if (getSign(p1) == 0 && getSign(p2) == 1 && check == 0) {
    f_result = FALSE;
  }
  if (getSign(p1) == 0 && getSign(p2) == 0) {
    if (getAbsoluteComparison(p1, p2) == BIGGER) {
      f_result = FALSE;
    }
  }
  if (getSign(p1) == 1 && getSign(p2) == 1) {
    if (getAbsoluteComparison(p1, p2) == LESS) {
      f_result = FALSE;
    }
  }
  if (getSign(p1) == 1 && getSign(p2) == 0) {
    if (CheckDecimal_isZero(p1) != CheckDecimal_isZero(p2)) f_result = TRUE;
  }
  return f_result;
}

int s21_is_less(s21_decimal p1, s21_decimal p2) {
  int f_result = TRUE;
  MakeScaleEqual(&p1, &p2);
  if (getSign(p1) == 0 && getSign(p2) == 1) {
    f_result = FALSE;
  }
  if (getSign(p1) == 0 && getSign(p2) == 0) {
    if (getAbsoluteComparison(p1, p2) != LESS) {
      f_result = FALSE;
    }
  }
  if (getSign(p1) == 1 && getSign(p2) == 1) {
    if (getAbsoluteComparison(p1, p2) != BIGGER) {
      f_result = FALSE;
    }
  }
  if (getSign(p1) == 1 && getSign(p2) == 0) {
    f_result = TRUE;
  }
  return f_result;
}

#undef _S21_DECIMAL_CONSTANTS
