#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

enum returns { OK, MATRIX_ERROR, CALC_ERROR };

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
void search_minor(int rows, int columns, matrix_t A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int s21_rows_and_colums_eq_two(matrix_t A, matrix_t B);
int s21_matrix_empty(matrix_t A);

#endif  // SRC_S21_MATRIX_H_
