// Copyright 2022 <merlinli>
#include "s21_matrix.h"
#include <math.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    // cjplftv vfnhbwe
    int error_code = 0;
    result->rows = rows;
    result->columns = columns;
    if (rows < 1 || columns < 1) {
        // матрица в одну строку
        result->matrix = NULL;
        error_code  = 1;
    } else {
        // выделяем память
        double **n_rows = calloc(rows, sizeof(double *));
        double *result_array = calloc(rows * columns, sizeof(double));
        for (int i = 0; i < rows; i++) {
            n_rows[i] = result_array + columns * i;
    }
    result->matrix = n_rows;
    }
    return error_code;
}

void s21_remove_matrix(matrix_t *A) {
    // очистка матрицы
    if (A->matrix) {
        if (A->matrix[0]) {
            free(A->matrix[0]);
        }
        free(A->matrix);
        A->matrix = NULL;
    }
    if (A->columns || A->rows) {
        A->columns = 0;
        A->rows = 0;
    }
}

int s21_check_matrix(matrix_t *m) {
    // проверяем допустимая ли матрица
    int code = 0;

    if (!m || m->rows < 1 || m->columns < 1) {
        code = 1;
    }

    return code;
}
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int error_code = SUCCESS;
    if (s21_check_matrix(A) != 0 || s21_check_matrix(B) != 0 ||
        A->rows != B->rows || A->columns != B->columns) {
        // сравнение по размерам
        error_code = FAILURE;
    } else {
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++) {
            // сравнение по значениям
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > S21_EPS) {
                error_code = FAILURE;
            }
        }
    error_code = SUCCESS;
    }
    return error_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int  error_code = s21_create_matrix(A->rows, A->columns, result);
    if (A->rows != B->rows || A->columns != B->columns)
        // неподходящие размеры
        error_code = 2;
    if (error_code == 0) {
        for (int i = 0; i < A->rows; i++)
            for (int j = 0; j < A->columns; j++)
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
    return error_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int error_code = s21_create_matrix(A->rows, A->columns, result);
    if (A->rows != B->rows || A->columns != B->columns)
        error_code = 2;
    if (error_code == 0) {
        for (int i = 0; i < A->rows; i++)
            for (int j = 0; j < A->columns; j++)
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
       }
    return error_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    // матрица на число
    int error_code = 0;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = number * A->matrix[i][j];
            }
        }
    } else {
        error_code = 1;
    }
    return error_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    // матрица на матрицу
    int error_code = s21_create_matrix(A->rows, B->columns, result);
    if (s21_check_matrix(A) || s21_check_matrix(B) || (A->columns != B->rows))
        error_code = 2;
    if (error_code == 0) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                result->matrix[i][j] = 0;
                for (int m = 0; m < B->rows; m++)
                    result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
            }
        }
    }
    return error_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    // замена строк столбцами
    int error_code = 0;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->columns; i++) {
            for (int j = 0; j < A->rows; j++) {
                result->matrix[i][j] = A->matrix[j][i];
            }
        }
    } else {
        error_code = 1;
    }
    return error_code;
}

void s21_minor(matrix_t *A, int index_row, int index_column, matrix_t *result) {
    // минор индексов
    int result_i = 0;
    for (int i = 0; i < result->rows; i++) {
        if (i == index_row) {
            result_i = 1;
        }
    int result_j = 0;
    for (int j = 0; j < result->columns; j++) {
        if (j == index_column) {
            result_j = 1;
        }
        result->matrix[i][j] = A->matrix[i + result_i][j + result_j];
        }
    }
}

int s21_determinant(matrix_t *A, double *result) {
    // определитель
    int error_code = 0;
    double determinant = 0.0;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows != A->columns) {
        // определитель только у квадратных матриц
        error_code = 2;
    } else if (A->rows == 1) {
        *result = A->matrix[0][0];
    } else if (A->rows == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] -
                   A->matrix[1][0] * A->matrix[0][1];
    } else {
        for (int j = 0; j < A->columns; j++) {
            matrix_t minor = {NULL, 0, 0};
            s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
            s21_minor(A, 0, j, &minor);
            s21_determinant(&minor, &determinant);
            *result += determinant * A->matrix[0][j] * pow(-1, 2 + j);
            determinant = 0;
            s21_remove_matrix(&minor);
        }
    }
    } else {
        error_code = 1;
    }
    return error_code;
}



int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int error_code = 0;
    double det = 0.0;
    matrix_t minor = {NULL, 0, 0};
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        s21_create_matrix(A->rows, A->columns, result);
    if (A->rows != A->columns) {
        error_code = 1;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
                s21_minor(A, i, j, &minor);
                s21_determinant(&minor, &det);
                result->matrix[i][j] = pow(-1, i + j) * det;
                det = 0.0;
                s21_remove_matrix(&minor);
            }
        }
    }
    } else {
        error_code = 1;
    }
    return error_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    // обратная матрица
    int error_code = 0;
    double determinant = 0.0;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows != A->columns) {
        error_code = 2;
    } else {
        s21_determinant(A, &determinant);
        if (determinant == 0) {
            error_code = 2;
        } else {
            matrix_t new = {NULL, 0, 0};
            s21_calc_complements(A, &new);
            matrix_t transform = {NULL, 0, 0};
            s21_transpose(&new, &transform);
            s21_mult_number(&transform, 1 / determinant, result);
            s21_remove_matrix(&new);
            s21_remove_matrix(&transform);
        }
    }
    } else {
        error_code = 1;
    }
    return error_code;
}
