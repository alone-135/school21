#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2
#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
void* s21_check_null(void* ptr);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_check_matrix(matrix_t *m);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
void s21_fill_minor_matrix(matrix_t *src, matrix_t *dst, int i, int j);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void matrix_init_0(matrix_t *A);
void s21_fill(matrix_t *matrixStruct, double value);

#endif  // SRC_S21_MATRIX_H_
