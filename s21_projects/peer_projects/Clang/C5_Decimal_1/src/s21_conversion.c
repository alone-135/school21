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
/                БЛОК ФУНКЦИЙ ПРЕОБРАЗОВАНИЯ ТИПОВ               /
/                                                                /
/===============================================================*/

/*     Так как int спокойно помещается в bits[0] то,      */
/*     Просто впихимаем его туда, не забывая сохранить    */
/*     знак int и записать в децимал                      */

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int f_result = CORRECT;
  if (dst) {
    MakeZeroDecimal(dst);
    if (src < 0) {
      src = -src;
      dst->bits[LOW] = src;
      setSign(dst, 1);
    } else {
      dst->bits[LOW] = src;
    }
  } else {
    f_result = CONVERSION_ERROR;
  }
  return f_result;
}

/*    Для того чтобы перевести число из децимал в float       */
/*    Нужно перевести так скажем перевести двоичную           */
/*    запись децимал в десятичную.                            */
/*    После получения данного числа, нужно узнать степень     */
/*    децимала. Далее, чтобы получить истинный float          */
/*    нам нужно сделать делить полученной число на 10 пока    */
/*    степень не станет нулю. Это дает нам число float        */

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int f_result = CORRECT;
  if (dst && getScale(src) <= 28) {
    unsigned long long int base = 1;
    double tmp = 0;
    *dst = 0.0;
    for (int i = 0; i <= BIT_COUNT_MAX; i++) {
      tmp += getBit(src, i) * base;
      base *= 2;
    }
    int scale_src = getScale(src);
    while (scale_src != 0) {
      tmp /= 10;
      scale_src--;
    }
    if (getSign(src) == 1) {
      tmp = -tmp;
    }
    *dst = tmp;
  } else {
    f_result = CONVERSION_ERROR;
  }
  return f_result;
}

/*     Зная что только bits[0] может поместиться в int              */
/*     нужно сделать все возможные преобразования чтобы             */
/*     избавиться и обнулить bits[1] bits[2], если это возможно     */
/*     Узнав степень децимала нам нужно обнулить ее, тем самый      */
/*     мы делим все число на 10 и оно уменьшается и если после      */
/*     этого в bits[1] и bits[2] лежат нули можно спокойно          */
/*     записывать bits[0] в int                                     */

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = 0;
  s21_decimal scale = {{10, 0, 0, 0}};
  int f_result = CORRECT;
  int sign_src = getSign(src), scale_src = getScale(src);
  while (scale_src != 0) {
    getDiv(src, scale, &src);
    scale_src--;
  }
  if (src.bits[MID] == 0 && src.bits[HIGH] == 0) {
    *dst = src.bits[LOW];
    if (sign_src == 1) {
      *dst *= -1;
    }
  } else {
    f_result = CONVERSION_ERROR;
  }
  if (getBit(src, 31) == 1 && getSign(src) == 1) {
    f_result = CONVERSION_ERROR;
    *dst = 0;
  }
  return f_result;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int f_result = CORRECT;
  if (CheckFloatCorrect(src) != CORRECT) {
    /*  Проверка на то является ли src (inf -inf nan) если да  */
    /*  То результат ошибка конвертации                        */
    f_result = CONVERSION_ERROR;
  } else {
    MakeZeroDecimal(dst);
    int sign_dst = 0;
    if (src < 0) {
      /*  Сохраняем знак src и в дальнейшем если оно отрицательное  */
      /*  чтобы минус не мешался мы его созраним в sign_dst         */
      /*  sign_dst - будующий знак децимала                         */
      sign_dst = 1;
      src *= -1;
    }
    double number = src;
    char src_submission[32] = "";
    /*    submission - представление    */
    getBinaryStringFromFloat((float)number, src_submission);
    int src_exp = getExpFloat(src_submission);
    int scale_dst = 0;
    while (scale_dst < 28 && (int)number / (int)pow(2, 22) == 0) {
      /*   Цикл для получения 8 знаков до запятой в number   */
      /*   0.00000123 --> 1230000.0                          */
      number *= 10;
      scale_dst++;
    }
    number = round(number);
    if (scale_dst <= 28 && (src_exp < 96 && src_exp > -94)) {
      while (fmod(number, 10) == 0 && scale_dst > 0) {
        /*   Убираем лишние нули до запятой для более простой   */
        /*   записи number в децимал                            */
        number /= 10;
        scale_dst--;
      }
      /*   Получаем новую бинарную строку уже от новой измененной переменной
       * number   */
      getBinaryStringFromFloat((float)number, src_submission);
      /*   Получаем новую степень float   */
      src_exp = getExpFloat(src_submission);
      setBit(
          dst, src_exp,
          1);  // Запись старшего бита в децимал (спрятанная единица в пямяти)
      for (int j = 9, i = src_exp - 1; i >= 0 && j < 32; j++, i--) {
        /*   Цикл перебирающий мантиссу записи числа number   */
        if (src_submission[j] == 1) {
          setBit(dst, i, 1);
        }
      }
      /*   Запись полученной степени в ходе функции и изначального знака src */
      setScale(dst, scale_dst);
      setSign(dst, sign_dst);
    } else {
      f_result = CONVERSION_ERROR;
    }
  }
  if (f_result == CONVERSION_ERROR) {
    MakeZeroDecimal(dst);
  }
  return f_result;
}

#undef _S21_DECIMAL_CONSTANTS
