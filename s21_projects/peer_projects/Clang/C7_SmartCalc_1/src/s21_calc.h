#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

///
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///

typedef enum { LOW = 1, MEDIUM = 2, HIGH = 3, BRACKET = -1 } priority_t;

typedef enum {
  NUM = 1,
  X = 2,
  PLUS = 3,
  MINUS = 4,
  MULT = 5,
  DIV = 6,
  POW = 7,
  MOD = 9,
  SIN = 10,
  COS = 11,
  TAN = 12,
  ASIN = 13,
  ACOS = 14,
  ATAN = 15,
  LN = 16,
  LOG = 17,
  SQRT = 18,
  L_BRACKET = 19,
  R_BRACKET = 20
} type_t;

typedef struct calc_stack {
  double num;
  priority_t priority;
  struct calc_stack* next;
  type_t type;
} calc_stack;

double s21_parsing(char* str, double value_x);
calc_stack* s21_sort_station(calc_stack* head);
double s21_calculation(calc_stack* head);
double s21_arichmetics(double a, double b, int sumbol);
double s21_triganometric(double a, int sumbol);
calc_stack* s21_coup_list(calc_stack* head);
void s21_push_back(calc_stack** head, double num, int priority, int type);
calc_stack* s21_pop_back(calc_stack** head);
int s21_check_empty_brackets(char* str, int str_len);
void s21_read_num(calc_stack** smart_calc, char* tmp_str, int* k);
void free_str(char* str);

#endif  // SRC_S21_CALC_H_make