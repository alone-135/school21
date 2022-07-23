#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int res = INCORRECT_MATRIX;
    if ((rows > 0 && columns > 0) || (rows == 0 && columns > 0) ||
        (rows > 0 && columns == 0))
        res = OK;
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int a = 0; a < rows; ++a) {
        result->matrix[a] = (double *)calloc(columns, sizeof(double));
    }
    return res;
}
void s21_remove_matrix(matrix_t *A) {
    if (A->matrix != NULL) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
    }
    A->columns = 0;
    A->rows = 0;
}
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int res = SUCCESS;
    if (A->rows == B->rows && A->columns == B->columns) {
        for (int i = 0; i < A->rows && res == SUCCESS; i++) {
            for (int j = 0; j < A->columns && res == SUCCESS; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
                    res = FAILURE;
                }
            }
        }
    } else {
        res = FAILURE;
    }
    return res;
}
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = 0;
    if (A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL &&
        A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
        if (A->rows == B->rows && A->columns == B->columns) {
            int rows_number = A->rows;
            int columns_number = A->columns;
            s21_create_matrix(rows_number, columns_number, result);
            for (int i = 0; i < rows_number; i++) {
                for (int j = 0; j < columns_number; j++) {
                    result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                }
            }
        } else {
            res = CALC_ERROR;
        }
    } else {
        res = INCORRECT_MATRIX;
    }
    return res;
}
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = 0;
    if (A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL &&
        A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
        if (A->rows == B->rows && A->columns == B->columns) {
            int rows_number = A->rows;
            int columns_number = A->columns;
            s21_create_matrix(rows_number, columns_number, result);
            for (int i = 0; i < rows_number; i++) {
                for (int j = 0; j < columns_number; j++) {
                    result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                }
            }
        } else {
            res = CALC_ERROR;
        }
    } else {
        res = INCORRECT_MATRIX;
    }
    return res;
}
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int res = OK;
    if (A->rows > 0 && A->columns > 0) {
        res = s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    } else {
        res = INCORRECT_MATRIX;
    }
    return res;
}
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (s21_check_matrix(A) || s21_check_matrix(B)) return INCORRECT_MATRIX;
    if (A->columns != B->rows) return CALC_ERROR;
    int res = s21_create_matrix(A->rows, B->columns, result);
    if (res == OK) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                result->matrix[i][j] = 0;
                for (int m = 0; m < B->rows; m++)
                    result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
            }
        }
    }
    return res;
}
int s21_check_matrix(matrix_t *m) {
    int res = OK;
    if (!m || m->rows < 1 || m->columns < 1) {
        res = INCORRECT_MATRIX;
    }
    return res;
}
int s21_transpose(matrix_t *A, matrix_t *result) {
    int res = s21_create_matrix(A->columns, A->rows, result);
    if (res == OK) {
        for (int i = 0; i < A->columns; i++) {
            for (int j = 0; j < A->rows; j++) {
                result->matrix[i][j] = A->matrix[j][i];
            }
        }
    }
    return res;
}
int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int res = 0;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        if (A->columns == A->rows) {
            int matrix_size = A->columns;
            int minor_matrix_size = matrix_size - 1;
            s21_create_matrix(matrix_size, matrix_size, result);
            for (int i = 0; i < matrix_size; i++) {
                for (int j = 0; j < matrix_size; j++) {
                    double determinant = 0;
                    matrix_t minor_matrix;
                    s21_create_matrix(minor_matrix_size, minor_matrix_size,
                                      &minor_matrix);
                    s21_fill_minor_matrix(A, &minor_matrix, i, j);
                    s21_determinant(&minor_matrix, &determinant);
                    result->matrix[i][j] = pow(-1, i + j) * determinant;
                    s21_remove_matrix(&minor_matrix);
                }
            }
        } else {
            res = CALC_ERROR;
        }
    } else {
        res = INCORRECT_MATRIX;
    }
    return res;
}

void s21_fill_minor_matrix(matrix_t *src, matrix_t *dst, int i, int j) {
    int matrix_size = src->columns;
    int minor_matrix_size = dst->columns;
    int minor_matrix_i = 0;
    int minor_matrix_j = 0;

    for (int k = 0; k < matrix_size; k++) {
        for (int l = 0; l < matrix_size; l++) {
            if (k != i && l != j) {
                dst->matrix[minor_matrix_i][minor_matrix_j] = src->matrix[k][l];

                if (minor_matrix_j + 1 != minor_matrix_size) {
                    minor_matrix_j++;
                } else {
                    minor_matrix_i++;
                    minor_matrix_j = 0;
                }
            }
        }
    }
}

int s21_determinant(matrix_t *A, double *result) {
    int res = 0;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        if (A->columns == A->rows) {
            int matrix_size = A->columns;
            int number_of_iterations = matrix_size;
            double buffer = 0;
            if (matrix_size == 1) {
                *result = A->matrix[0][0];
            } else if (matrix_size == 2 || matrix_size == 3) {
                if (matrix_size == 2) {
                    number_of_iterations = matrix_size - 1;
                }
                for (int i = 0; i < number_of_iterations; i++) {
                    double main_diagonal = 1;
                    double second_diagonal = 1;
                    for (int j = 0; j < matrix_size; j++) {
                        main_diagonal *=
                            A->matrix[j % matrix_size][(j + i) % matrix_size];
                    }
                    for (int j = 0; j < matrix_size; j++) {
                        second_diagonal *=
                            A->matrix[j % matrix_size]
                                     [(matrix_size - 1 - j + i) % matrix_size];
                    }
                    buffer += main_diagonal - second_diagonal;
                }
                *result = buffer;
            } else {
                for (int i = 0; i < matrix_size; i++) {
                    double determinant = 0;
                    matrix_t matrix_buffer;
                    s21_create_matrix(matrix_size - 1, matrix_size - 1,
                                      &matrix_buffer);
                    s21_fill_minor_matrix(A, &matrix_buffer, i, 0);
                    s21_determinant(&matrix_buffer, &determinant);
                    determinant *= A->matrix[i][0];
                    if (i % 2 == 1) {
                        *result -= determinant;
                    } else {
                        *result += determinant;
                    }
                    s21_remove_matrix(&matrix_buffer);
                }
            }
        } else {
            res = CALC_ERROR;
        }
    } else {
        res = INCORRECT_MATRIX;
    }
    return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int res = 0;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        if (A->columns == A->rows) {
            double determinant = 0;
            s21_determinant(A, &determinant);
            if (fabs(determinant) > 1e-7) {
                matrix_t buffer;
                matrix_t buffer2;
                s21_calc_complements(A, &buffer);
                s21_transpose(&buffer, &buffer2);
                s21_mult_number(&buffer2, 1.0 / determinant, result);
                s21_remove_matrix(&buffer);
                s21_remove_matrix(&buffer2);
            } else {
                res = CALC_ERROR;
            }
        } else {
            res = CALC_ERROR;
        }
    } else {
        res = INCORRECT_MATRIX;
    }
    return res;
}

void s21_fill(matrix_t *matrixStruct, double value) {
    for (int i = 0; i < matrixStruct->rows; i++) {
        for (int j = 0; j < matrixStruct->columns; j++) {
            matrixStruct->matrix[i][j] = value;
        }
    }
}
