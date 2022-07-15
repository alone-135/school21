#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int check = OK;
    if (rows > 0 && columns > 0) {
        result->columns = columns;
        result->rows = rows;
        if ((result->matrix = (double **) calloc(rows, sizeof(double*))) != NULL) {
            for (int i = 0; i < rows && check == 0; i++) {
                if ((result->matrix[i] = (double *) calloc(columns, sizeof(double))) == NULL) {
                    check = MATRIX_ERROR;
                }
            }
        } else {
            check = MATRIX_ERROR;
        }
    } else {
        check = MATRIX_ERROR;
    }
    return check;
}

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
        A->matrix = NULL;
    }
    A->columns = 0;
    A->rows = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int res = TRUE;
    if (A->rows == B->rows && A->columns == B->columns && A->rows > 0 &&
                        A->columns > 0 && B->rows > 0 && B->columns > 0) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; i < A->columns; i++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07 * fabs(B->matrix[i][j])) {
                    res = FALSE;
                    break;
                }
            }
            if (res == FALSE) break;
        }
    } else {
        res = FALSE;
    }
    return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = OK;
    if (s21_matrix_empty(*A) && s21_matrix_empty(*B)) {
        if (s21_rows_and_colums_eq_two(*A, *B)) {
            s21_create_matrix(A->rows, A->columns, result);
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                }
            }
        } else {
            res = CALC_ERROR;
        }
    } else {
        res = MATRIX_ERROR;
    }
    return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = OK;
    if (s21_matrix_empty(*A) && s21_matrix_empty(*B)) {
        if (s21_rows_and_colums_eq_two(*A, *B)) {
            s21_create_matrix(A->rows, A->columns, result);
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                }
            }
        } else {
            res = CALC_ERROR;
        }
    } else {
        res = MATRIX_ERROR;
    }
    return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int res = OK;
    if (s21_matrix_empty(*A)) {
        if (s21_create_matrix(A->rows, A->columns, result)) {
            res = CALC_ERROR;
        } else {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] * number;
                }
            }
        }
    } else {
        res = MATRIX_ERROR;
    }
    return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = OK;
    if (!A || !B || !A->matrix || !B->matrix || A->rows <= 0 ||
        B->rows <= 0 || A->columns <= 0 || B->columns <= 0 ||
        s21_create_matrix(A->rows, B->columns, result) != 0) {
        res = MATRIX_ERROR;
    } else if (A->columns != B->rows) {
        res = CALC_ERROR;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j ++) {
                for (int k = 0; k < A->columns; k++) {
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
    }
    return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int res = OK;
    if (s21_matrix_empty(*A)) {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    } else {
        res = MATRIX_ERROR;
    }
    return res;
}

void search_minor(int rows, int columns, matrix_t A, matrix_t *result) {
    s21_create_matrix(A.rows - 1, A.columns - 1, result);
    int i = 0, j = 0;
    for (int k = 0; k < A.rows; k++) {
        if (k == rows) continue;
        for (int l = 0; l < A.columns; l++) {
            if (l == columns) continue;
            result->matrix[i][j] = A.matrix[k][l];
            j++;
        }
        j = 0;
        i++;
    }
}

int s21_determinant(matrix_t *A, double *result) {
    int res = OK;
    if (!A || !A->matrix || A->columns <= 0 || A->rows <= 0 || !result) {
        res = MATRIX_ERROR;
    } else if (A->rows != A->columns) {
        res = CALC_ERROR;
    } else {
        if (A->columns != 1 && A->columns != 2) {
            *result = 0;
            for (int i = 0; i < A->rows; i++) {
                matrix_t minor;
                search_minor(0, i, *A, &minor);
                double det;
                s21_determinant(&minor, &det);
                s21_remove_matrix(&minor);
                double temp = pow(-1, i) * A->matrix[0][i] * det;
                *result += temp;
            }
        } else if (A->rows == 2) {
            *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
        } else if (A->rows == 1) {
            *result = A->matrix[0][0];
        }
    }
    return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int res = OK;
    if (!A || !A->matrix || A->columns <= 0 || A->rows <= 0 || !result) {
        res = MATRIX_ERROR;
    } else if (A->rows != A->columns) {
        res = CALC_ERROR;
    } else {
        s21_create_matrix(A->rows, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->rows; j++) {
                matrix_t minor;
                search_minor(i, j, *A, &minor);
                double det;
                s21_determinant(&minor, &det);
                s21_remove_matrix(&minor);
                det = det * pow(-1, i + j);
                result->matrix[i][j] = det;
            }
        }
    }
    return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int res = 0;
    if (!A || !A->matrix || A->columns <= 1 || A->rows <= 1 || !result) {
        res = MATRIX_ERROR;
    } else if (A->rows != A->columns) {
        res = CALC_ERROR;
    } else {
        double det = 0;
        s21_determinant(A, &det);
        if (fabs(det) <= 1e-7) {
            res = CALC_ERROR;
        } else {
            matrix_t minor;
            matrix_t trans;
            s21_calc_complements(A, &minor);
            s21_transpose(&minor, &trans);
            s21_remove_matrix(&minor);
            s21_mult_number(&trans, 1 / det, result);
            s21_remove_matrix(&trans);
        }
    }
    return res;
}

int s21_matrix_empty(matrix_t A) {
    int res = 0;
    if (A.matrix != NULL && A.columns > 0 && A.rows > 0) {
        res = TRUE;
    }
    return res;
}

int s21_rows_and_colums_eq_two(matrix_t A, matrix_t B) {
    int res = 0;
    if (A.columns == B.columns && A.rows == B.rows) {
        res = TRUE;
    }
    return res;
}
