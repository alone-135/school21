#include "s21_calc.h"
// #include <unistd.h>

char function_name[11][6] = {
"cos",
"sin",
"tan",
"acos",
"asin",
"atan",
"sqrt",
"ln",
"log",
"mod",
"pow",
};
//****************************************************************************//

spisok *list_new(double value, int priority, type_t type) {
    spisok *new;
    new = calloc(1, sizeof(spisok));
    if (new == NULL)
        return (NULL);
    new->value = value;
    new->priority = priority;
    new->type = type;
    new->next = NULL;
    return (new);
}

// void print_list(spisok *tmp) {
//     while (tmp != NULL) {
//         printf("\nvalue = %lf \n", tmp -> value);
//         if (tmp -> type == add)
//             printf("type = +\n");
//         if (tmp -> type == division)
//             printf("type = /\n");
//         if (tmp -> type == open_br)
//             printf("type = (\n");
//         if (tmp -> type == close_br)
//             printf("type = )\n");
//         if (tmp -> type == sub)
//             printf("type = -\n");
//         printf("type = %d \n", tmp -> type);
//         printf("priority = %d \n", tmp -> priority);
//         printf("next = %p \n\n", tmp -> next);

//         tmp = tmp -> next;
//     }
// }

void list_add_front(spisok **lst, spisok *new) {
    if (lst && new) {
        if (!*lst) {
            *lst = new;
        } else {
            new->next = (*lst);
            (*lst) = new;
        }
    }
}

// spisok *list_last(spisok *lst) {
//     if (lst == NULL)
//         return (NULL);
//     while (lst->next != NULL)
//         lst = lst->next;
//     return (lst);
// }

void list_add_back(spisok **lst, spisok *new) {
    if (lst && new) {
        if (!*lst) {
            *lst = new;
        } else {
            spisok *tmp = *lst;
            while (tmp->next) {
                tmp = tmp->next;
            }
            tmp->next = new;
        }
    }
}

void pop_list(spisok **head) {
    if ((*head)->next) {
        spisok *tmp = (*head)->next;
        (*head)->next = NULL;
        free(*head);
        (*head) = tmp;
    } else {
        (*head)->next = NULL;
        free(*head);
        *head = NULL;
    }
}

spisok *push(spisok *st, spisok *new) {
    list_add_back(&st, list_new(new->value, new->priority, new->type));
    return (st);
}

void unload_stack(spisok **output_queue, spisok *stack) {
    while (stack) {
        *output_queue = push(*output_queue, stack);
        pop_list(&stack);
    }
}

void push_back(spisok **output_queue, spisok *list) {
    list_add_back(output_queue, list_new(list->value, list->priority, list->type));
}

void push_front(spisok **output_queue, spisok *list) {
    list_add_front(output_queue, list_new(list->value, list->priority, list->type));
}

// ***************************************************************************

int find_func_valid(char *str, int *i, int *code_pov_mod) {
    int exit_code = 0;
    if (strstr(str+*i, "acos")) {
        *i+=3;
    } else if ((strstr(str+*i, "asin"))) {
        *i+=3;
    } else if ((strstr(str+*i, "atan"))) {
        *i+=3;
    } else if ((strstr(str+*i, "cos"))) {
        *i+=2;
    } else if ((strstr(str+*i, "sin"))) {
        *i+=2;
    } else if ((strstr(str+*i, "tan"))) {
        *i+=2;
    } else if ((strstr(str+*i, "sqrt"))) {
        *i+=3;
    } else if ((strstr(str+*i, "log"))) {
        *i+=2;
    } else if ((strstr(str+*i, "ln"))) {
        *i+=1;
    } else if ((strstr(str+*i, "mod"))) {
        *i+=2;
        *code_pov_mod = 1;
    } else if ((strstr(str+*i, "pow"))) {
        *i+=2;
        *code_pov_mod = 1;
    } else if ((strstr(str+*i, "x"))) {
        *i+=1;
    } else {
        exit_code = 1;
    }
    return exit_code;
}

int parse_dot(char* str, int *i) {
    int error = 0;
    while ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '.') {
        if (str[*i] == '.')
            error += 1;
        *i = *i+1;
    }
    *i = *i-1;
    error -= 1;
    return (error);
}

int check_validnost(char* str) {
    int error_code = 0;
    int open_brackets = 0;
    int close_brackets = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'x') {
            if (str[i+1] == 'x') {
                error_code = 1;
            }
        }
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'x') {  // цифры + x
            if (str[i+1] == '.') {
                if (str[i+2] < '0' || str[i+2] > '9') {
                    error_code = 1;
                    // printf("invalid number\n");
                    break;
                }
            }
        } else if (str[i] == ',') {
            // printf("Please put a dot instead of a comma\n");
            error_code = 1;
            break;
        } else if (str[i] == '.') {
            if (str[i-1] < '0' || str[i-1] > '9') {
                error_code = 1;
                // printf("invalid dot\n");
                break;
            } else {
                error_code = parse_dot(str, &i);
            }
        } else if (str[i] == '*' || str[i] == '+' || str[i] == '-' \
                || str[i] == '/' || str[i] == '^') {  // арифметика
                if ((str[i+1] < '0' || str[i+1] > '9')) {
                    if (str[i+1] == '(' || str[i-1] == ')') {
                    } else if (str[i+1] == 'x') {
                    } else {
                        error_code = 1;
                        // printf("invalid ariphmetics 1 (\"%c\")\n", str[i]);
                        break;
                    }
                } else if ((i != 0 && (str[i-1] < '0' || str[i-1] > '9')) && str[i-1] != 41) {
                    if (str[i-1] == '(' || str[i-1] == 'x') {
                    } else {
                        error_code = 1;
                        // printf("invalid ariphmetics 2 (\"%c\")\n", str[i]);
                        break;
                    }
                }
        } else if (str[i] == '(') {  // скобки
            if (str[i-1] >= '0' && str[i-1] <= '9') {
                    error_code = 1;
                    // printf("invalid brackets 2\n");
                    break;
            } else {
            open_brackets += 1;
            }
        } else if (str[i] == ')') {  // скобки
            if (str[i+1] >= '0' && str[i+1] <= '9') {
                    error_code = 1;
                    // printf("invalid brackets 1\n");
                    break;
            } else {
            close_brackets += 1;
            }
        } else if (strchr("cstalmp", str[i])) {
            int code_pov_mod = 0;
            error_code = find_func_valid(str, &i, &code_pov_mod);
            if (code_pov_mod == 0 && str[i+1] != '(') {
                error_code = 1;
            }
            if (error_code != 0) {
                // printf("error func name\n");
                break;
            }
        } else {
            error_code = 1;
        }
    }
    if (close_brackets != open_brackets) {
        error_code = 1;
        // printf("invalid brackets\n");
    }
    return error_code;
}

type_t get_type_func(char* str, int* i) {
    char type[5] = {0};
    int type_code = 0;
    for (int j = 0; str[*i] >= 'a' && str[*i] <= 'z'; j++, *i += 1) {
        type[j] = str[*i];
    }
    for (type_code = 0; !strstr(function_name[type_code], type); type_code++) {}
    *i = *i-1;
    if (type_code == 10) {
        type_code = pw;
    }
    return (type_code);
}

void skip_num(char *str, int *i) {
    while ((str[*i+1] >= '0' && str[*i+1] <= '9') || str[*i+1] == '.') {
        *i += 1;
    }
}

spisok *make_leksem(char *str, double x) {  // заполняет список лексемами
    spisok* for_RPN = NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        double value = 0.0;
        int priority = 0;
        type_t type = -1;

        if (str[i] >= '0' && str[i] <= '9') {  // numbers
            value = atof(str+i);
            type = 10;
            skip_num(str, &i);
        } else if (str[i] >= 'a' && str[i] <= 'x') {  // functions
            priority = 4;
            if (str[i] == 'x') {
                priority = 0;
                value = x;
                type = number;
            } else {
                type = get_type_func(str, &i);
                if (type == mod || type == pw) {  // for func 'mod' 'pow'
                    priority = 2;
                }
            }
        } else if (str[i] == '(' || str[i] == ')') {
            type = (str[i] == '(') ? 11 : 12;
        } else if (str[i] == '+' || str[i] == '-') {
            if (i == 0 || str[i-1] == '(') {  // unary
                list_add_back(&for_RPN, list_new(value, priority, 10));
            }
            priority = 1;
            type = (str[i] == '+') ? 13 : 14;
        } else if (str[i] == '*' || str[i] == '/') {
            priority = 2;
            type = (str[i] == '*') ? 15 : 16;
        } else if (str[i] == '^') {
            priority = 3;
            type = 17;
        }
        list_add_back(&for_RPN, list_new(value, priority, type));
    }
    return for_RPN;
}

spisok* list_for_notation(spisok *list) {
    spisok *output_queue = NULL;
    spisok *stack = NULL;

    while (list) {
        if (list->type == number) {
            push_back(&output_queue, list);
        } else if (list->type == open_br || (list->type >= cosin && list->type <= lg10)) {
            push_front(&stack, list);
        } else if (list->type == mod || (list->type >= add && list->type <= pw )) {
                while (stack && stack->priority >= list->priority) {
                    push_back(&output_queue, stack);
                    pop_list(&stack);
                }
            push_front(&stack, list);
        } else if (list->type == close_br) {
            while (stack && stack->type != open_br) {
                push_back(&output_queue, stack);
                pop_list(&stack);
            }
            pop_list(&stack);
        } else {
            while (stack) {
                push_back(&output_queue, stack);
            }
        }
        list = list->next;
    }
    unload_stack(&output_queue, stack);

    return output_queue;
}

double get_result(int operand, double v1, double v2) {
    double res = 0.0;
    if (operand == add) res = (v1 + v2);
    else if (operand == sub) res = (v1 - v2);
    else if (operand == division) res = (v1 / v2);
    else if (operand == mult) res = (v1 * v2);
    else if (operand == mod) res = fmod(v1, v2);
    else if (operand == pw) res = pow(v1, v2);

    else if (operand == cosin) res = cos(v1);
    else if (operand == sinus) res = sin(v1);
    else if (operand == tang) res = tan(v1);
    else if (operand == acosin) res = acos(v1);
    else if (operand == asinus) res = asin(v1);
    else if (operand == atang) res = atan(v1);

    else if (operand == sqrtt) res = sqrt(v1);
    else if (operand == ln) res = log(v1);
    else if (operand == lg10) res = log10(v1);

    return res;
}

int calculate(spisok *for_RPN, double *result) {
    spisok* stack = calloc(1, sizeof(spisok));
    int error_code = 0;
    double res = 0.0;
    double v1 = 0.0;
    double v2 = 0.0;

    while (for_RPN) {
        if (for_RPN->type == number) {
            push_front(&stack, for_RPN);
        } else if ((for_RPN->type >= add && for_RPN->type <= pw)|| for_RPN->type == mod) {
            v2 = stack->value;
            pop_list(&stack);
            v1 = stack->value;
            pop_list(&stack);
            res = get_result(for_RPN->type, v1, v2);
            list_add_front(&stack, list_new(res, 0, number));
        } else if (for_RPN->type >= cosin && for_RPN->type <= lg10) {
            v1 = stack->value;
            pop_list(&stack);
            res = get_result(for_RPN->type, v1, v2);
            list_add_front(&stack, list_new(res, 0, number));
        }
        for_RPN = for_RPN->next;
    }
    *result = stack->value;
    while (stack) {
         pop_list(&stack);
    }
    return (error_code);
}

int start_calc(char* str, double *result, double *x) {
    int error_code = 0;
    spisok *for_RPN = NULL;

    error_code = check_validnost(str);
    if (error_code == 0) {
        for_RPN = list_for_notation(make_leksem(str, *x));
        error_code = calculate(for_RPN, result);
    }
    return error_code;
}

// int main() {
//     char* str = "x";
//     int error_code = 0;
// //    spisok *for_RPN;
//     double x = -10.0;
//     double result = 0.0;
//     error_code = start_calc(str, &result, &x);
//     printf("RESULT IS %lf\n", result);
// //    error_code = check_validnost(str);
// //    if (error_code != 0) {
// //        printf("======= str is NOT OK ========\n");
// //    } else {
// //        printf("---------str is OK----------\n");
// //        for_RPN = list_for_notation(make_leksem(str, x));
// //        // print_list(for_RPN);
// //        result = calculate(for_RPN);
// //    }
//   return 0;
// }
