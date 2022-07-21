#include "s21_calc.h"

// int main() {
//   double x = 25;
//   char str[1024] = "()";
//   double res = s21_parsing(str, x);
//   // double res = 2.33 * fmod(1);
//   printf("%lf", res);
//   return 0;
// }

double s21_parsing(char* str, double value_x) {
  calc_stack* smart_calc = NULL;
  double result = 0;
  int str_len = strlen(str);
  char tmp_str[256] = {'\0'};
  int k = 0;
  for (int i = 0; i <= str_len; i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      tmp_str[k] = str[i];
      k++;
    } else if (str[i] == '.') {
      tmp_str[k] = str[i];
      k++;
    } else if (str[i] == '+') {
      if (str[i - 1] == '(') {
        tmp_str[k] = str[i];
        k++;
      } else {
        s21_read_num(&smart_calc, tmp_str, &k);
        s21_push_back(&smart_calc, 0, LOW, PLUS);
        free_str(tmp_str);
      }
    } else if (str[i] == '-') {
      if (str[i - 1] == '(') {
        tmp_str[k] = str[i];
        k++;
      } else {
        s21_read_num(&smart_calc, tmp_str, &k);
        s21_push_back(&smart_calc, 0, LOW, MINUS);
      }
    } else if (str[i] == '*') {
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, MEDIUM, MULT);
    } else if (str[i] == '/') {
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, MEDIUM, DIV);
    } else if (str[i] == '^') {
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, POW);
    } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
      i += 2;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, MEDIUM, MOD);
    } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
      i += 2;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, SIN);
    } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
      i += 2;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, COS);
    } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
      i += 2;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, TAN);
    } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
               str[i + 3] == 'n') {
      i += 3;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, ASIN);
    } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
               str[i + 3] == 's') {
      i += 3;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, ACOS);
    } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
               str[i + 3] == 'n') {
      i += 3;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, ATAN);
    } else if (str[i] == 'l' && str[i + 1] == 'n') {
      i += 1;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, LN);
    } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
      i += 2;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, LOG);
    } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
               str[i + 3] == 't') {
      i += 3;
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, HIGH, SQRT);
    } else if (str[i] == '(') {
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, BRACKET, L_BRACKET);
    } else if (str[i] == ')') {
      s21_read_num(&smart_calc, tmp_str, &k);
      s21_push_back(&smart_calc, 0, BRACKET, R_BRACKET);
    } else if (str[i] == 'x') {
      s21_push_back(&smart_calc, value_x, 0, 0);
    } else {
      s21_read_num(&smart_calc, tmp_str, &k);
    }
  }
  free_str(tmp_str);
  if (!s21_check_empty_brackets(str, str_len)) {  /// ?????
    if (smart_calc != NULL) {
      smart_calc = s21_coup_list(smart_calc);
    }
    if (smart_calc != NULL) {
      smart_calc = s21_sort_station(smart_calc);
    }
    if (smart_calc != NULL) {
      smart_calc = s21_coup_list(smart_calc);
    }
    if (smart_calc != NULL) {
      result = s21_calculation(smart_calc);
    }
  } else {
    while (smart_calc) {
      calc_stack* for_free = smart_calc;
      smart_calc = smart_calc->next;
      free(for_free);
    }
  }
  return result;
}

calc_stack* s21_sort_station(calc_stack* head) {
  calc_stack* result = NULL;
  calc_stack* tmp = NULL;
  while (head) {
    if (head->priority == 0) {
      s21_push_back(&result, head->num, 0, 0);
    } else {
      if (tmp != NULL) {
        if ((head->priority > tmp->priority) || (head->type == L_BRACKET)) {
          s21_push_back(&tmp, 0, head->priority, head->type);
        } else {
          if (head->type == R_BRACKET) {
            while (tmp && (tmp->type != L_BRACKET)) {
              s21_push_back(&result, 0, tmp->priority, tmp->type);
              calc_stack* tmp1 = tmp;
              tmp = tmp->next;
              free(tmp1);
            }
          } else {
            s21_push_back(&result, 0, tmp->priority, tmp->type);
            calc_stack* for_free1 = s21_pop_back(&tmp);
            free(for_free1);
          }
          s21_push_back(&tmp, 0, head->priority, head->type);
          if (result->type < SIN) {
            if (tmp->type == R_BRACKET) {
              calc_stack* for_free2 = s21_pop_back(&tmp);
              free(for_free2);
            }
            if (tmp->type == L_BRACKET) {
              calc_stack* for_free3 = s21_pop_back(&tmp);
              free(for_free3);
            }
          }
        }
      } else {
        s21_push_back(&tmp, 0, head->priority, head->type);
      }
    }
    calc_stack* for_free = head;
    head = head->next;
    free(for_free);
  }
  while (tmp) {
    if (tmp->type != L_BRACKET && tmp->type != R_BRACKET) {
      s21_push_back(&result, 0, tmp->priority, tmp->type);
    }
    calc_stack* tmp3 = tmp;
    tmp = tmp->next;
    free(tmp3);
  }
  return result;
}

double s21_calculation(calc_stack* head) {
  calc_stack* tmp = NULL;
  double result = 0;
  int count = 2;
  double a = 0;
  double b = 0;
  while (head) {
    if (head->priority == 0) {
      s21_push_back(&tmp, head->num, 0, 0);
    } else if ((head->priority > 0) && (head->type < SIN && head->type > 0)) {
      while (tmp) {
        if (count == 2) {
          b = tmp->num;
        } else if (count == 1) {
          a = tmp->num;
        } else if (count == 0) {
          break;
        }
        count--;
        calc_stack* tmp1 = tmp;
        tmp = tmp->next;
        free(tmp1);
      }
      if (count == 0) {
        s21_push_back(&tmp, s21_arichmetics(a, b, head->type), 0, 0);
      }
      count = 2;
    } else if ((head->priority > 0) &&
               (head->type > MOD && head->type < L_BRACKET)) {
      while (tmp) {
        if (count == 2) {
          b = tmp->num;
        } else if (count == 1) {
          break;
        }
        count--;
        calc_stack* tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
      }
      if (count == 1) {
        s21_push_back(&tmp, s21_triganometric(b, head->type), 0, 0);
      }
      count = 2;
    }
    calc_stack* tmp3 = head;
    head = head->next;
    free(tmp3);
  }
  if (tmp != NULL) {
    result = tmp->num;
    free(tmp);
  }
  return result;
}

double s21_arichmetics(double a, double b, int sumbol) {
  double result = 0;
  if (sumbol == PLUS) {
    result = a + b;
  }
  if (sumbol == MINUS) {
    result = a - b;
  }
  if (sumbol == DIV) {
    result = a / b;
  }
  if (sumbol == MULT) {
    result = a * b;
  }
  if (sumbol == POW) {
    result = pow(a, b);
  }
  if (sumbol == MOD) {
    result = fmod(a, b);
  }
  return result;
}

double s21_triganometric(double a, int sumbol) {
  double result = 0;
  if (sumbol == SIN) {
    result = sin(a);
  }
  if (sumbol == COS) {
    result = cos(a);
  }
  if (sumbol == TAN) {
    result = tan(a);
  }
  if (sumbol == ASIN) {
    result = asin(a);
  }
  if (sumbol == ACOS) {
    result = acos(a);
  }
  if (sumbol == ATAN) {
    result = atan(a);
  }
  if (sumbol == SQRT) {
    result = sqrt(a);
  }
  if (sumbol == LN) {
    result = log(a);
  }
  if (sumbol == LOG) {
    result = log10(a);
  }
  return result;
}

calc_stack* s21_coup_list(calc_stack* head) {
  calc_stack* tmp = NULL;
  calc_stack* tmp1 = NULL;
  while (head != NULL) {
    tmp1 = head;
    s21_push_back(&tmp, head->num, head->priority, head->type);
    head = head->next;
    free(tmp1);
  }
  return tmp;
}

void s21_push_back(calc_stack** head, double num, int priority, int type) {
  calc_stack* tmp = calloc(1, sizeof(calc_stack));
  tmp->num = num;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = *head;
  *head = tmp;
}

calc_stack* s21_pop_back(calc_stack** head) {
  calc_stack* ptr = NULL;
  calc_stack* tmp = calloc(1, sizeof(calc_stack));
  ptr = *head;
  tmp->num = ptr->num;
  tmp->priority = ptr->priority;
  tmp->type = ptr->type;
  *head = (*head)->next;
  free(ptr);
  return tmp;
}

int s21_check_empty_brackets(char* str, int str_len) {
  int check = 0;
  for (int i = 0; i < str_len; i++) {
    if (str[i] == '(') {
      check = (str[i + 1] == ')' ? 1 : 0);
    }
    if (str[i] == ')') {
      check = (str[i + 1] == '(' ? 1 : check);
    }
  }
  return check;
}

void s21_read_num(calc_stack** smart_calc, char* tmp_str, int* k) {
  if (tmp_str[0] != '\0') {
    s21_push_back(smart_calc, atof(tmp_str), 0, 0);
    *k = 0;
    free_str(tmp_str);
  }
}

void free_str(char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = '\0';
  }
}
