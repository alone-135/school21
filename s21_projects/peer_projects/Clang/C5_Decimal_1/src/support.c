#define _S21_DECIMAL_CONSTANTS
#define _SUPPORT_FUNCTIONS_
#include "s21_decimal.h"

/*===============================================================/
/                                                                /
/                  S21_DECIMAL PROJECT SCHOOL 21                 /
/                               by                               /
/     tonitaga jerlenem nenitawi zoomdeni clotilde marselit      /
/                                                                /
/===============================================================*/

/*     Обнуляет все bits[i]     */

void MakeZeroDecimal(s21_decimal *p) {
  for (int i = LOW; i < SCALE + 1; i++) p->bits[i] = 0;
}

/*      Возвращает 1 если все bits[i] = 0      */
/*      Возвращает 0 если хотя бы один         */
/*      bits[i] не равен нулю                  */

int CheckDecimal_isZero(s21_decimal p) {
  int result = 0;
  if (p.bits[LOW] == 0 && p.bits[MID] == 0 && p.bits[HIGH] == 0) {
    result = 1;
  }
  return result;
}

/*      Bit_Index - индекс бита который нужно найти                       */
/*      Изначально нужно создать маску в зависимости от Bit_Index         */
/*      Так как каждый bits[i] имеет размерность 32 бита,                 */
/*      то что бы попасть в нужный bits[i] нужно определить в              */
/*      какой ячейке находится Bit_Index                                  */
/*      следующим образом (Bit_Index % 32):                               */
/*          Например: Bit_Index = 45 Bit_Index % 32 = 1 -->               */
/*          Bit_Index находится в bits[1]                                 */
/*      Например: Надо получить бит под индексом 2 в 8-битном числе       */
/*          01101100 - (число)                                            */
/*          00000100 - (маска)                                            */
/*          00000100 - (результат)                                        */
/*      Здесь нужно использовать побитовую операцию 'и'                   */

int getBit(s21_decimal p, int Bit_Index) {
  int Bit_result = 0;
  unsigned int mask = 1u << (Bit_Index % 32);
  if ((p.bits[Bit_Index / 32] & mask) != 0) Bit_result = 1;
  return Bit_result;
}

/*      S_Index - номер бита который нужно заменить                         */
/*      R_Index - значение на которое нужно поменять S_Index                */
/*      Изначально нужно создать маску в зависимости от S_Index             */
/*      Так как каждый bits[i] имеет размерность 32 бита,                   */
/*      то что бы попасть в нужный bits[i] нужно определить в                */
/*      какой ячейке находится S_Index следующим образом (S_Index % 32):    */
/*             Например: S_Index = 45 S_Index % 32 = 1 -->                  */
/*             S_Index находится в bits[1]                                  */
/*      Как заменить S_Index на R_Index если R_Index = 1                    */
/*             Например: 11110011 поменять 3 бит на единицу                 */
/*             нужна маска типа 00000100 и побитовой операцией или          */
/*             получаем 11110011 | 00000100 = 11110111                      */
/*      Как заменить S_Index на R_Index если R_Index = 0                    */
/*             Например: 11110011 поменять 2 бит на ноль                    */
/*             нужна маска типа 11111101 (инверсированная маска)            */
/*             и побитовой операцией 'и' получаем                           */
/*             11110011 & 11111101 = 11110001                               */
/*      Если маска равна 10001101                                           */
/*      То инверсированная маска (~mask) равна 01110010                     */

void setBit(s21_decimal *p, int S_Index, int R_Index) {
  unsigned int mask = 1 << (S_Index % 32);
  if (R_Index == 1) p->bits[S_Index / 32] |= mask;
  if (R_Index == 0) p->bits[S_Index / 32] &= ~mask;
}

/*      Изначально нужно создать маску, для этого воспользуемся      */
/*      теорией, знаковый бит находится на 31 биту bits[3],          */
/*      поэтому нужно создать маску, которая позволит узнать         */
/*      какая цифра там стоит ноль или единица, 0 - (+) 1 - (-)      */
/*          Например: Имеет 8 битное число и на 7 его бите           */
/*          находится знак, 10001000, маска 10000000 результат       */
/*          10000000 используя побитовую операцию 'и'                */
/*      Маска создается путем сдвига вправо единицы на 31 бит        */

int getSign(s21_decimal p) {
  int sign = getBit(p, 127);
  return sign;
}

/*      R_Index - значение на которое нужно поменять 31 бит                 */
/*      Изначально нужно создать маску со сдвигом вправо на 31 бит          */
/*      Как заменить 31 бит на R_Index если R_Index = 1                     */
/*             Например: 01110011 поменять 7 бит на единицу                 */
/*             нужна маска типа 10000000 и побитовой операцией или          */
/*             получаем 01110011 | 10000000 = 11110111                      */
/*      Как заменить 31 бит на R_Index если R_Index = 0                     */
/*             Например: 11110011 поменять 7 бит на ноль                    */
/*             нужна маска типа 01111111 (инверсированная маска)            */
/*             и побитовой операцией 'и' получаем                           */
/*             11110011 & 01111111 = 11110001                               */
/*      Если маска равна 10001101                                           */
/*      То инверсированная маска (~mask) равна 01110010                     */

void setSign(s21_decimal *p, int R_Index) {
  unsigned int mask = 1u << 31;
  if (R_Index == 1) p->bits[SCALE] |= mask;
  if (R_Index == 0) p->bits[SCALE] &= ~mask;
}

/*      Изначально нужно обнулить 31 бит в bits[3]                 */
/*      так как если там будет единичка она нам помешает           */
/*      Далее мы знаем что раздел точности в bits[3]               */
/*      Начинается с 16 бита поэтому имеющийся bits[3]             */
/*      сдвигаем на 16 битов вправо использую побитовый сдвиг      */
/*      И если сразу после этого вернуть bits[3] то мы             */
/*      получим значение степени числа                             */

int getScale(s21_decimal p) {
  setSign(&p, 0);
  p.bits[SCALE] >>= 16;
  return p.bits[SCALE];
}

/*      Scale - новая степень на которую нужно поменять         */
/*      Замена будет проходить полной заменой bits[3]           */
/*      Поэтому изначально нужно сохранить 31 бит               */
/*      Присваиваем значение Scale в bits[3]                    */
/*      Далее нужно чтобы степень встала на свое место          */
/*      Зная расположение в памяти сдвинет на 16 бит влево      */
/*      Если изначальный 31 бит был равен единице               */
/*      Нужно ее восстановить используя setSign                 */

void setScale(s21_decimal *p, int Scale) {
  int saveSign = getSign(*p);
  p->bits[SCALE] = Scale;
  p->bits[SCALE] <<= 16;
  if (saveSign == 1) setSign(p, saveSign);
}

/*      Функция заполняет строку str бинарно             */
/*      Для этого используется преобразование:           */
/*      преобразуем адрес float в указатель на uint      */
/*      также как и хранится в памяти компьютера         */
/*          0     10...0        ...00...0                */
/*        sign   exp 8bit    мантисса 23bit              */
/*      Инверсия: !1000011 = 0111100                     */
/*      Инверсия любого числа отличного от нуля          */
/*      равна нулю, поэтому двойная инверсия             */
/*      позволяет получить 100% либо 0 либо 1            */

void getBinaryStringFromFloat(float f, char *str) {
  unsigned int bits = *((unsigned int *)&f);
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    *str = !!(bits & mask);
    str++;
  }
}

/*     Функция уравнивает степени двух децималов        */
/*     Сначала определяется больший децимал и           */
/*     меньший децимал, определяется их начальная       */
/*     степень, затем умножаем меньший децимал на       */
/*     десять тем самый увеличивая его степень, но      */
/*     может быть переполнение, поэтому есть второй     */
/*     цикл, который делит больший децимал на           */
/*     десять тем самым уменьшая его степень.           */
/*     После уравнивания степени нужно занести          */
/*     сохраненный знаки и новые степени децималов      */

void MakeScaleEqual(s21_decimal *p1, s21_decimal *p2) {
  s21_decimal Big_decimal, Little_decimal;
  /*  Scale переменная которая хранит в себе десятку   */
  /*  Для того чтобы увеличивать или уменьшать степень  */
  s21_decimal Scale = {{10, ZERO, ZERO, ZERO}};
  MakeZeroDecimal(&Big_decimal);
  MakeZeroDecimal(&Little_decimal);

  int sign_p1 = getSign(*p1);
  int sign_p2 = getSign(*p2);
  int Big_Scale = 0, Little_Scale = 0;
  if (getScale(*p1) > getScale(*p2)) {
    Big_decimal = *p1;
    Little_decimal = *p2;
    Big_Scale = getScale(*p1);
    Little_Scale = getScale(*p2);
  }
  if (getScale(*p1) < getScale(*p2)) {
    Big_decimal = *p2;
    Little_decimal = *p1;
    Big_Scale = getScale(*p2);
    Little_Scale = getScale(*p1);
  }
  while (Big_Scale != Little_Scale) {
    while (getConsiderableLength(Little_decimal) < 93 &&
           Big_Scale != Little_Scale) {
      getMul(Little_decimal, Scale, &Little_decimal);
      Little_Scale += 1;
    }
    while (Big_Scale != Little_Scale) {
      if (Big_Scale - Little_Scale == ONE) {
        if (Big_decimal.bits[LOW] >= 5 && Big_decimal.bits[LOW] < 10) {
          Big_decimal.bits[LOW] = 1;
          Big_Scale -= 1;
          break;
        }
      }
      getDiv(Big_decimal, Scale, &Big_decimal);
      Big_Scale -= 1;
    }
  }
  if (getScale(*p1) > getScale(*p2)) {
    *p1 = Big_decimal;
    *p2 = Little_decimal;
    setScale(p1, Big_Scale);
    setScale(p2, Little_Scale);
    setSign(p1, sign_p1);
    setSign(p2, sign_p2);
  }
  if (getScale(*p1) < getScale(*p2)) {
    *p1 = Little_decimal;
    *p2 = Big_decimal;
    setScale(p1, Little_Scale);
    setScale(p2, Big_Scale);
    setSign(p1, sign_p1);
    setSign(p2, sign_p2);
  }
}

void MakeScaleEqualMod(s21_decimal *p1, s21_decimal *p2) {
  s21_decimal Big_decimal, Little_decimal;
  /*  Scale переменная которая хранит в себе десятку   */
  /*  Для того чтобы увеличивать или уменьшать степень  */
  s21_decimal Scale = {{10, ZERO, ZERO, ZERO}};
  MakeZeroDecimal(&Big_decimal);
  MakeZeroDecimal(&Little_decimal);

  int sign_p1 = getSign(*p1);
  int sign_p2 = getSign(*p2);
  int Big_Scale = 0, Little_Scale = 0;
  if (getScale(*p1) > getScale(*p2)) {
    Big_decimal = *p1;
    Little_decimal = *p2;
    Big_Scale = getScale(*p1);
    Little_Scale = getScale(*p2);
  }
  if (getScale(*p1) < getScale(*p2)) {
    Big_decimal = *p2;
    Little_decimal = *p1;
    Big_Scale = getScale(*p2);
    Little_Scale = getScale(*p1);
  }
  while (Big_Scale != Little_Scale) {
    while (getConsiderableLength(Little_decimal) < 93 &&
           Big_Scale != Little_Scale) {
      getMul(Little_decimal, Scale, &Little_decimal);
      Little_Scale += 1;
    }
    while (Big_Scale != Little_Scale) {
      if (Big_decimal.bits[LOW] >= 1 && Big_decimal.bits[LOW] < 10 &&
          Big_decimal.bits[MID] == 0 && Big_decimal.bits[HIGH] == 0) {
        break;
      }
      getDiv(Big_decimal, Scale, &Big_decimal);
      Big_Scale -= 1;
    }
    if (Big_decimal.bits[LOW] >= 1 && Big_decimal.bits[LOW] < 10 &&
        Big_decimal.bits[MID] == 0 && Big_decimal.bits[HIGH] == 0) {
      break;
    }
  }
  if (getScale(*p1) > getScale(*p2)) {
    *p1 = Big_decimal;
    *p2 = Little_decimal;
    setScale(p1, Big_Scale);
    setScale(p2, Little_Scale);
    setSign(p1, sign_p1);
    setSign(p2, sign_p2);
  }
  if (getScale(*p1) < getScale(*p2)) {
    *p1 = Little_decimal;
    *p2 = Big_decimal;
    setScale(p1, Little_Scale);
    setScale(p2, Big_Scale);
    setSign(p1, sign_p1);
    setSign(p2, sign_p2);
  }
}

/*      Зная запись float в памяти которая            */
/*      хранится в str, знаем что с [1;8] биты        */
/*      хранится экспонента float переводим           */
/*      двоичное число в десятичное, также            */
/*      зная константу вычисления степени float,      */
/*      которая равна 127 находим следующим           */
/*      образом степень exp - 127                     */

int getExpFloat(char *str) {
  int exp = 0, base = 1;
  for (int i = 8; i > 0; i--) {
    exp += str[i] * base;
    base *= 2;
  }
  return (exp - 127);
}

/*      Функция находим сумму двух decimal и               */
/*      сохраняет это значение в новой переменной           */
/*      result. Чтобы не было ошибок в вычислении          */
/*      нужно избавиться от мусора внутри result           */
/*      Существует 4 различные ситуации нахождения         */
/*      нулей и единиц в одном и том же бите двух          */
/*      decimal'ов. При сложении двух единиц выхо-         */
/*      дит ноль, но в голове нужно помнить что есть       */
/*      единица. Для этого создана переменная saveBit      */
/*      Она хранит в таких ситуациях единицу               */

void getSum(s21_decimal p1, s21_decimal p2, s21_decimal *result) {
  MakeZeroDecimal(result);
  int saveBit = 0;
  for (int i = 0; i < 96; i++) {
    if (getBit(p1, i) == getBit(p2, i)) setBit(result, i, ZERO + saveBit);
    if (getBit(p1, i) != getBit(p2, i)) setBit(result, i, ONE - saveBit);
    int s = getBit(p1, i) + getBit(p2, i) + saveBit;
    if (s > 1)
      saveBit = ONE;
    else
      saveBit = ZERO;
  }
}

/*      Функция находит разницу двух decimal и             */
/*      сохраняет это значение в новой переменной           */
/*      result. Чтобы не было ошибок в вычислении          */
/*      нужно избавиться от мусора внутри result           */
/*      Существует 4 различные ситуации нахождения         */
/*      нулей и единиц в одном и том же бите двух          */
/*      decimal'ов. При сложении двух единиц выхо-         */
/*      дит ноль, но в голове нужно помнить что есть       */
/*      единица. Для этого создана переменная saveBit      */
/*      Она хранит в таких ситуациях единицу               */

void getSub(s21_decimal p1, s21_decimal p2, s21_decimal *result) {
  MakeZeroDecimal(result);
  int saveBit = 0;
  for (int i = 0; i < 96; i++) {
    if (getBit(p1, i) == getBit(p2, i)) setBit(result, i, ZERO + saveBit);
    if (getBit(p1, i) != getBit(p2, i)) setBit(result, i, ONE - saveBit);
    int s = getBit(p1, i) - getBit(p2, i) - saveBit;
    if (s < 0)
      saveBit = ONE;
    else
      saveBit = ZERO;
  }
}

void getMul(s21_decimal p1, s21_decimal p2, s21_decimal *result) {
  MakeZeroDecimal(result);
  if (getBit(p2, 0) == 1) {
    *result = p1;
  }
  for (int i = 1; i < getConsiderableLength(p2); i++) {
    if (getBit(p2, i) == 0) {
      MakeShiftLeftorRight(&p1, LEFT);
    }
    if (getBit(p2, i) == 1) {
      MakeShiftLeftorRight(&p1, LEFT);
      getSum(*result, p1, result);
    }
  }
}

void getDiv(s21_decimal p1, s21_decimal p2, s21_decimal *result) {
  MakeZeroDecimal(result);
  if (getAbsoluteComparison(p1, p2) == BIGGER ||
      getAbsoluteComparison(p1, p2) == EQUAL) {
    int length = getConsiderableLength(p1);
    s21_decimal middle = {{ZERO, ZERO, ZERO, ZERO}};
    s21_decimal divisor = {{ZERO, ZERO, ZERO, ZERO}};
    for (int i = length - 1; i >= 0; i--) {
      setBit(&middle, 0, getBit(p1, i));
      if (getAbsoluteComparison(middle, p2) == LESS) {
        setBit(result, 0, 0);
        if (i != 0) {
          MakeShiftLeftorRight(result, LEFT);
          MakeShiftLeftorRight(&middle, LEFT);
        }
      } else {
        setBit(result, 0, 1);
        s21_sub(middle, p2, &divisor);
        MakeZeroDecimal(&middle);
        middle = divisor;
        if (i != 0) {
          MakeShiftLeftorRight(result, LEFT);
          MakeShiftLeftorRight(&middle, LEFT);
        }
      }
    }
  }
}

void getDivMod(s21_decimal p1, s21_decimal p2, s21_decimal *result,
               s21_decimal *divisor) {
  MakeZeroDecimal(result);
  MakeZeroDecimal(divisor);
  if (getAbsoluteComparison(p1, p2) == BIGGER ||
      getAbsoluteComparison(p1, p2) == EQUAL) {
    int length = getConsiderableLength(p1);
    s21_decimal middle = {{ZERO, ZERO, ZERO, ZERO}};
    for (int i = length - 1; i >= 0; i--) {
      setBit(&middle, 0, getBit(p1, i));
      if (getAbsoluteComparison(middle, p2) == LESS) {
        setBit(result, 0, 0);
        if (i != 0) {
          MakeShiftLeftorRight(result, LEFT);
          MakeShiftLeftorRight(&middle, LEFT);
        }
        if (i == 0) {
          *divisor = middle;
        }
      } else {
        setBit(result, 0, 1);
        getSub(middle, p2, divisor);
        MakeZeroDecimal(&middle);
        middle = *divisor;
        if (i != 0) {
          MakeShiftLeftorRight(result, LEFT);
          MakeShiftLeftorRight(&middle, LEFT);
        }
      }
    }
  } else {
    *divisor = p1;
  }
}

/*      Функция может сдвинуть число на 1 бит            */
/*      влево и вправо, это зависит от входно-           */
/*      го параметра L_or_R. Чтобы правильно сдви-       */
/*      нуть число на 1 бит нужно сохранить краевые      */
/*      биты и после побитового сдвига поставить их      */
/*      на свое новое место.                             */

void MakeShiftLeftorRight(s21_decimal *p, char L_or_R) {
  if (L_or_R == 114) {
    int b31 = getBit(*p, 31);
    int b63 = getBit(*p, 63);
    for (int i = 0; i < 3; i++) p->bits[i] <<= 1;
    if (b31 == 1) {
      setBit(p, 32, ONE);
    }
    if (b63 == 1) {
      setBit(p, 64, ONE);
    }
  }
  if (L_or_R == 122) {
    // int b32 = getBit(*p, 32);
    // int b64 = getBit(*p, 64);
    // for (int i = 0; i < 3; i++)
    //     p->bits[i] >>= 1;
    // if (b32 == 1) { setBit(p, 31, ONE); }
    // if (b64 == 1) { setBit(p, 63, ONE); }
  }
}

/*      Функция возвращает длину decimal только      */
/*      со значащими битами. Например: 00000100      */
/*      Имеет 8 бит, но всего 3 значащих бита        */
/*      ConsiderableLength - значимая длина          */

int getConsiderableLength(s21_decimal p) {
  int result = 0;
  for (result = 95; result >= 0; result--)
    if (getBit(p, result) == 1) {
      break;
    }
  return result + 1;
}

/*     Функция сравнивает абсолютные значения двух decimal'ов     */
/*     Если p1 > p2   |   return  1                               */
/*     Если p1 < p2   |   return -1                               */
/*     Если p1 = p2   |   return  0                               */
int getAbsoluteComparison(s21_decimal p1, s21_decimal p2) {
  int result = EQUAL;
  int bit_counter = ZERO;
  for (int i = BIT_COUNT_MAX; i >= 0; i--) {
    if (getBit(p1, i) > getBit(p2, i)) {
      result = BIGGER;
      break;
    }
    if (getBit(p1, i) < getBit(p2, i)) {
      result = LESS;
      break;
    }
    if (getBit(p1, i) == getBit(p2, i)) {
      bit_counter += 1;
    }
  }
  if (bit_counter == 96) {
    result = EQUAL;
  }
  return result;
}

int getAbsoluteGreater(s21_decimal p1, s21_decimal p2) {
  int result = FALSE;
  for (int i = BIT_COUNT_MAX; i >= 0; i--) {
    if (getBit(p1, i) < getBit(p2, i)) break;
    if (getBit(p1, i) > getBit(p2, i)) {
      result = TRUE;
      break;
    }
  }
  return result;
}

int getAbsoluteGreaterOrEqual(s21_decimal p1, s21_decimal p2) {
  int result = FALSE;
  int equal_counter = 0;
  for (int i = BIT_COUNT_MAX; i >= 0; i--) {
    if (getBit(p1, i) < getBit(p2, i)) break;
    if (getBit(p1, i) > getBit(p2, i)) {
      result = TRUE;
      break;
    }
    if (getBit(p1, i) == getBit(p2, i)) equal_counter += 1;
  }
  if (equal_counter == 96) result = TRUE;
  return result;
}

/*     Функция был создана для уменьшения степени на один     */
/*     при переполнении bits.                                 */
/*     Изначально сохраним знак p1, p2 и их scale             */
/*     Создан новый децимал divisor - делитель                */
/*     на него делим каждый децимал и тем самый уменьшаем     */
/*     Записываем знак и новую уменьшенную степень в p1, p2   */

void MakeScaleLessOne(s21_decimal *p1, s21_decimal *p2) {
  s21_decimal divisor = {{10, 0, 0, 0}};
  int sign_p1 = getSign(*p1);
  int sign_p2 = getSign(*p2);
  int scale_p1 = getScale(*p1);
  int scale_p2 = getScale(*p2);
  getDiv(*p1, divisor, p1);
  getDiv(*p2, divisor, p2);
  setScale(p1, scale_p1 - 1);
  setScale(p2, scale_p2 - 1);
  setSign(p1, sign_p1);
  setSign(p2, sign_p2);
}

int CheckFloatCorrect(float f) {
  int f_result = CORRECT;
  if (f != f || f == -1.0 / 0.0 || f == 1.0 / 0.0) {
    f_result = 1;
  }
  return f_result;
}

/*      Рассмотрим первым случаем когда оба децимала положительные     */
/*       1) value1 == value2, тогда при разнице будет очевидно что     */
/*      получится положительное число и result = 0                     */
/*       2) value1 > value2, будет очевидно что отнимая от большего    */
/*      меньшее будет положительное число                              */
/*       3) value1 < value2, получится отрицательное число если от     */
/*      меньшего отнять большее                                        */
/*                                                                     */
/*      Рассмотрим первым случаем когда оба децимала отрицательные     */
/*       1) value1 == value2, тогда при разнице будет очевидно что     */
/*      получится положительное число и result = 0  -1 - (-1) = 0      */
/*       2) Если value1 > value2 по модулю, тогда результат будет      */
/*      отрицательным, например: v1 = -10, v2 = -6, |v1|=10, |v2|=6    */
/*      |v1| > |v2| ==> -10 - (-6) = -4                                */
/*       3) Если value1 < value2 по модулю, тогда результат будет      */
/*      положительный, например: v1 = -6, v2 = -10, |v1|=6, |v2|=10    */
/*      |v1| < |v2| ==> -6 - (-10) = 4                                 */
/*                                                                     */
/*      Рассмотрим ситуацию при разных знаках                          */
/*      Если value1 < 0 a value 2 >= 0, тогда при любом value2 и       */
/*      value1 результат будет отрицательным => -10 - 6 = -16 или      */
/*      можно сложить модули этих чисел и умножить на -1 ==>           */
/*      (10+6)*(-1) = -16                                              */

void CheckOperationsForSub(s21_decimal value1, s21_decimal value2,
                           s21_decimal *result) {
  int sign_1 = getSign(value1);
  int sign_2 = getSign(value2);

  if (sign_1 == 0 && sign_2 == 0) {
    if (s21_is_equal(value1, value2)) {
      getSub(value1, value2, result);
      setSign(result, PLUS);
    }
    if (getAbsoluteGreater(value1, value2)) {
      getSub(value1, value2, result);
      setSign(result, PLUS);
    }
    if (getAbsoluteGreater(value2, value1)) {
      getSub(value2, value1, result);
      setSign(result, MINUS);
    }
  }

  if (sign_1 == 1 && sign_2 == 1) {
    if (s21_is_equal(value1, value2)) {
      getSub(value1, value2, result);
      setSign(result, PLUS);
    }
    if (getAbsoluteComparison(value1, value2) == BIGGER) {
      getSub(value1, value2, result);
      setSign(result, MINUS);
    }
    if (getAbsoluteComparison(value2, value1) == BIGGER) {
      getSub(value2, value1, result);
      setSign(result, PLUS);
    }
  }

  if (sign_1 != sign_2) {
    if (sign_1 == 1) {
      getSum(value1, value2, result);
      setSign(result, MINUS);
    }
    if (sign_1 == 0) {
      getSum(value1, value2, result);
      setSign(result, PLUS);
    }
  }
}

void getMullCheckingSign(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result) {
  MakeZeroDecimal(result);
  if (getBit(value_2, 0) == 1) {
    *result = value_1;
  }
  for (int i = 1; i < getConsiderableLength(value_2); i++) {
    if (getBit(value_2, i) == 0) {
      MakeShiftLeftorRight(&value_1, LEFT);
    }
    if (getBit(value_2, i) == 1) {
      MakeShiftLeftorRight(&value_1, LEFT);
      getSum(*result, value_1, result);
    }
  }
  if (getSign(value_1) == getSign(value_2)) {
    setSign(result, 0);
  } else {
    setSign(result, 1);
  }
}

/*   Cоздание обратного кода для вычитания
        1 - Инверсируются 3 бита
        2 - Прибавляется 1 к инверсированному числу (готов обратный код)
        3 - Сложение обратного кода и value_1   */

void getInversionBits(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result) {
  s21_decimal tmp = {{1, 0, 0, 0}};
  MakeZeroDecimal(result);
  value_2.bits[0] = ~value_2.bits[0];
  value_2.bits[1] = ~value_2.bits[1];
  value_2.bits[2] = ~value_2.bits[2];
  getSum(value_2, tmp, &value_2);
  getSum(value_1, value_2, result);
}

#undef _S21_DECIMAL_CONSTANTS
