#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

/*===============================================================/
/                                                                /
/                  S21_DECIMAL PROJECT SCHOOL 21                 /
/                               by                               /
/     tonitaga jerlenem nenitawi zoomdeni clotilde marselit      /
/                                                                /
/===============================================================*/

/*     Libraries     */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { OK, INF, N_INF, N_NAN, DOP_CODE } value_type_t;
enum { LOW, MID, HIGH, SCALE };

/*     The main struct of project     */

typedef struct {
    unsigned int bits[4];
} s21_decimal;

/*      MAIN FUNCTIONS       */

/*===============================================================/
/                                                                /
/             БЛОК ФУНКЦИЙ МАТЕМАТИЧЕСКИХ ОПЕРАЦИЙ               /
/                                                                /
/===============================================================*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*===============================================================/
/                                                                /
/             БЛОК ФУНКЦИЙ СРАВНЕНИЯ ДВУХ ДЕЦИМАЛОВ              /
/                                                                /
/===============================================================*/

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

//================================================================/
//                БЛОК ФУНКЦИЙ ПРЕОБРАЗОВАНИЯ ТИПОВ               /
//================================================================/

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/*===============================================================/
/                                                                /
/               БЛОК ФУНКЦИЙ ОКРУГЛЕНИЯ ДЕЦИМАЛА                 /
/                                                                /
/===============================================================*/

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/*      SUPPORT FUNCTIONS OF PROJECT     */
#if defined _SUPPORT_FUNCTIONS_
void MakeZeroDecimal(s21_decimal *p);
int CheckDecimal_isZero(s21_decimal p);
int getBit(s21_decimal p, int Bit_Index);
void setBit(s21_decimal *p, int S_Index, int R_Index);
int getSign(s21_decimal p);
void setSign(s21_decimal *p, int R_Index);
int getScale(s21_decimal p);
void setScale(s21_decimal *p, int Scale);
void getBinaryStringFromFloat(float f, char *str);
int getExpFloat(char *str);
void getSum(s21_decimal p1, s21_decimal p2, s21_decimal *result);
void getSub(s21_decimal p1, s21_decimal p2, s21_decimal *result);
void getMul(s21_decimal p1, s21_decimal p2, s21_decimal *result);
void getDiv(s21_decimal p1, s21_decimal p2, s21_decimal *result);
void getDivMod(s21_decimal p1, s21_decimal p2, s21_decimal *result,
               s21_decimal *divisor);
void MakeShiftLeftorRight(s21_decimal *p1, char L_or_R);
int getConsiderableLength(s21_decimal p1);
int getAbsoluteComparison(s21_decimal p1, s21_decimal p2);
int getAbsoluteGreater(s21_decimal p1, s21_decimal p2);
int getAbsoluteGreaterOrEqual(s21_decimal p1, s21_decimal p2);
void MakeScaleLessOne(s21_decimal *p1, s21_decimal *p2);
void MakeScaleEqual(s21_decimal *p1, s21_decimal *p2);
void MakeScaleEqualMod(s21_decimal *p1, s21_decimal *p2);
int CheckFloatCorrect(float f);
void CheckOperationsForSub(s21_decimal p1, s21_decimal p2, s21_decimal *r);
void getMullCheckingSign(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result);
void getInversionBits(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result);
#endif  // _SUPPORT_FUNCTIONS_

/*      Define _S21_DECIMAL_CONSTANTS           */
/*      to make these constants available.      */
#if defined _S21_DECIMAL_CONSTANTS
#define BITS_MAX 4294967295
#define BIT_COUNT_MAX 95
#define ONE 1
#define ZERO 0
#define PLUS 0
#define MINUS 1
/*   For MakeShiftLeftorRight function   */
#define LEFT 114
#define RIGHT 122
/*   For getAbsoluteСomparison function   */
#define EQUAL 0
#define LESS -1
#define BIGGER 1
/*   For main Comparison functions   */
#define TRUE 1
#define FALSE 0
/*   Converters   */
#define CORRECT 0
#define CONVERSION_ERROR 1
#endif  // _S21_DECIMAL_CONSTANTS

#endif  // SRC_S21_DECIMAL_H_
