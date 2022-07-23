#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum type {
    cosin = 0,
    sinus,
    tang,
    acosin,
    asinus,
    atang,
    sqrtt,
    ln,
    lg10,
    mod,

    number,

    open_br,
    close_br,

    add,
    sub,
    mult,
    division,
    pw
} type_t;

typedef struct Node {
    double value;
    int priority;
    type_t type;
    struct Node *next;
} spisok;

int start_calc(char* str, double *result, double *x);
int calculate(spisok *for_RPN, double *result);
spisok *list_new(double value, int priority, type_t type);
void print_list(spisok *tmp);
void list_add_front(spisok **lst, spisok *ne);
spisok *list_last(spisok *lst);
void list_add_back(spisok **lst, spisok *ne);
int find_func_valid(char *str, int *i, int *code_pov_mod);
int check_validnost(char* str);
type_t get_type_func(char* str, int* i);
void skip_num(char *str, int *i);
spisok* make_leksem(char *str, double x);
void pop_list(spisok **head);
spisok* push(spisok *st, spisok *ne);
void unload_stack(spisok **output_queue, spisok *stack);
void remove_list(spisok* stack);
spisok* list_for_notation(spisok *list);
int parse_dot(char* str, int *i);

//  *** BONUS PART ***  //
double monthly_payment_annuitent(double S, double perc, double n);
double overpayment_and_total_annuitent(double S, double n, double montly_pay, double *total);
double monthly_payment_and_overpay_difference(double S, double perc, double n, double *monthly_payment);
double get_deposit_perc(double P, double perc, int time, double nalog, double *sum_nalog,
            int kap, double *final_sum, int n, double sum_pop, double sum_snyat);
