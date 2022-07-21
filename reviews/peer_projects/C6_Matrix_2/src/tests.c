#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"

#define IDENTITY_MATRIX 2

START_TEST(s21_eq_matrix_test_1) {
    matrix_t result1;
    matrix_t result2;
    s21_create_matrix(41, 41, &result1);
    s21_create_matrix(41, 41, &result2);
    s21_fill(&result1, 1);
    s21_fill(&result2, 1);
    int expected_result = SUCCESS;
    int actual_result = s21_eq_matrix(&result1, &result2);
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
}
END_TEST

START_TEST(s21_eq_matrix_test_2) {
    matrix_t result1;
    matrix_t result2;
    s21_create_matrix(83, 83, &result1);
    s21_create_matrix(83, 83, &result2);
    s21_fill(&result1, 7);
    s21_fill(&result2, 9);
    int expected_result = FAILURE;
    int actual_result = s21_eq_matrix(&result1, &result2);
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
}
END_TEST

START_TEST(s21_eq_matrix_test_3) {
    matrix_t result1;
    matrix_t result2;
    s21_create_matrix(32, 32, &result1);
    s21_create_matrix(27, 27, &result2);
    s21_fill(&result1, 42);
    s21_fill(&result2, 42);
    int expected_result = FAILURE;
    int actual_result = s21_eq_matrix(&result1, &result2);
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
}
END_TEST

START_TEST(s21_eq_matrix_test_4) {
    matrix_t result1;
    matrix_t result2;
    s21_create_matrix(22, 22, &result1);
    s21_create_matrix(22, 22, &result2);
    s21_fill(&result1, 13);
    s21_fill(&result2, 12);
    int expected_result = FAILURE;
    int actual_result = s21_eq_matrix(&result1, &result2);
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
}
END_TEST

START_TEST(s21_sum_matrix_test_1) {
    matrix_t result;
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(4, 4, &result1);
    s21_create_matrix(4, 4, &result2);
    s21_fill(&result1, 3);
    s21_fill(&result2, 4);
    s21_create_matrix(4, 4, &result);
    s21_fill(&result, 7);
    s21_sum_matrix(&result1, &result2, &result3);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ck_assert_double_eq(result.matrix[i][j], result3.matrix[i][j]);
        }
    }
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
    matrix_t result;
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(2, 2, &result1);
    s21_create_matrix(4, 4, &result2);
    int expected_result = s21_create_matrix(2, 2, &result3);
    int actual_result = s21_sum_matrix(&result1, &result2, &result);
    ck_assert_int_ne(expected_result, actual_result);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result3);
}
END_TEST

START_TEST(s21_sum_matrix_test_3) {
    matrix_t result;
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(4, 4, &result1);
    s21_create_matrix(4, 4, &result2);
    s21_fill(&result1, 0);
    result2.matrix[0][0] = 1;
    result2.matrix[1][1] = 1;
    result2.matrix[2][2] = 1;
    result2.matrix[3][3] = 1;
    int expected_result = s21_create_matrix(4, 4, &result3);
    result3.matrix[0][0] = 1;
    result3.matrix[1][1] = 1;
    result3.matrix[2][2] = 1;
    result3.matrix[3][3] = 1;
    int actual_result = s21_sum_matrix(&result1, &result2, &result);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ck_assert_double_eq(result3.matrix[i][j], result.matrix[i][j]);
        }
    }
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_1) {
    matrix_t result;
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(4, 4, &result1);
    s21_create_matrix(4, 4, &result2);
    s21_fill(&result1, 4);
    s21_fill(&result2, 3);
    s21_create_matrix(4, 4, &result);
    s21_fill(&result, 1);
    int sum_m = s21_sub_matrix(&result1, &result2, &result3);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ck_assert_double_eq(result.matrix[i][j], result3.matrix[i][j]);
        }
    }
    ck_assert_uint_eq(sum_m, 0);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_2) {
    matrix_t result;
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(2, 2, &result1);
    s21_create_matrix(4, 4, &result2);
    int expected_result = s21_create_matrix(2, 2, &result3);
    int actual_result = s21_sum_matrix(&result1, &result2, &result);
    ck_assert_int_ne(expected_result, actual_result);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result3);
}
END_TEST

START_TEST(s21_sub_matrix_test_3) {
    matrix_t result;
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(4, 4, &result1);
    s21_create_matrix(4, 4, &result2);
    s21_fill(&result2, 0);
    result1.matrix[0][0] = 1;
    result1.matrix[1][1] = 1;
    result1.matrix[2][2] = 1;
    result1.matrix[3][3] = 1;
    int expected_result = s21_create_matrix(4, 4, &result3);
    result3.matrix[0][0] = 1;
    result3.matrix[1][1] = 1;
    result3.matrix[2][2] = 1;
    result3.matrix[3][3] = 1;
    int actual_result = s21_sub_matrix(&result1, &result2, &result);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ck_assert_double_eq(result3.matrix[i][j], result.matrix[i][j]);
        }
    }
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_1) {
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(4, 4, &result1);
    s21_fill(&result1, 3);
    int expected_result = s21_create_matrix(4, 4, &result2);
    s21_fill(&result2, 30);
    int actual_result = s21_mult_number(&result1, 10, &result3);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ck_assert_double_eq(result3.matrix[i][j], result2.matrix[i][j]);
        }
    }
    ck_assert_int_eq(expected_result, actual_result);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result3);
}
END_TEST

START_TEST(s21_mult_number_test_2) {
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(2, 2, &result1);
    int expected_result = s21_create_matrix(2, 2, &result2);
    int actual_result = s21_mult_number(&result1, 3, &result3);
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_mult_matrix_test_1) {
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    matrix_t result4;
    s21_create_matrix(4, 4, &result1);
    s21_create_matrix(4, 4, &result2);
    s21_fill(&result1, 3);
    s21_fill(&result2, 3);
    int expected_result = s21_create_matrix(4, 4, &result3);
    s21_fill(&result3, 36);
    int actual_result = s21_mult_matrix(&result1, &result2, &result4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ck_assert_double_eq(result3.matrix[i][j], result4.matrix[i][j]);
        }
    }
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result4);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_mult_matrix_test_2) {
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    matrix_t result4;
    s21_create_matrix(4, 4, &result1);
    s21_create_matrix(3, 3, &result2);
    s21_fill(&result1, 3);
    s21_fill(&result2, 3);
    int expected_result = s21_create_matrix(4, 4, &result3);
    expected_result = INCORRECT_MATRIX;
    int actual_result = s21_mult_matrix(&result1, &result2, &result4);
    ck_assert_uint_ne(expected_result, actual_result);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_transpose_test_1) {
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(4, 4, &result1);
    result1.matrix[0][0] = 1;
    result1.matrix[0][1] = 2;
    result1.matrix[0][2] = 3;
    result1.matrix[0][3] = 4;

    result1.matrix[1][0] = 1;
    result1.matrix[1][1] = 2;
    result1.matrix[1][2] = 3;
    result1.matrix[1][3] = 4;

    result1.matrix[2][0] = 1;
    result1.matrix[2][1] = 2;
    result1.matrix[2][2] = 3;
    result1.matrix[2][3] = 4;

    result1.matrix[3][0] = 1;
    result1.matrix[3][1] = 2;
    result1.matrix[3][2] = 3;
    result1.matrix[3][3] = 4;

    int expected_result = s21_create_matrix(4, 4, &result2);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result2.matrix[j][i] = result1.matrix[i][j];
        }
    }
    expected_result = 0;

    int actual_result = s21_transpose(&result1, &result3);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ck_assert_double_eq(result2.matrix[i][j], result3.matrix[i][j]);
        }
    }
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_transpose_test_2) {
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(-1, 4, &result1);
    ;
    int expected_result = s21_create_matrix(-1, 4, &result2);
    int actual_result = s21_transpose(&result1, &result3);
    ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(s21_calc_complements_test_1) {
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(3, 3, &result1);
    result1.matrix[0][0] = 1;
    result1.matrix[0][1] = 2;
    result1.matrix[0][2] = 3;

    result1.matrix[1][0] = 0;
    result1.matrix[1][1] = 4;
    result1.matrix[1][2] = 2;

    result1.matrix[2][0] = 5;
    result1.matrix[2][1] = 2;
    result1.matrix[2][2] = 1;
    int expected_result = s21_create_matrix(3, 3, &result2);
    result2.matrix[0][0] = 0;
    result2.matrix[0][1] = 10;
    result2.matrix[0][2] = -20;

    result2.matrix[1][0] = 4;
    result2.matrix[1][1] = -14;
    result2.matrix[1][2] = 8;

    result2.matrix[2][0] = -8;
    result2.matrix[2][1] = -2;
    result2.matrix[2][2] = 4;
    s21_create_matrix(3, 3, &result3);
    int actual_result = s21_calc_complements(&result1, &result3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ck_assert_double_eq(result2.matrix[i][j], result3.matrix[i][j]);
        }
    }
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result1);
}

START_TEST(s21_calc_complements_test_2) {
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(3, -1, &result1);
    int expected_result = s21_create_matrix(-1, 4, &result2);
    int actual_result = s21_calc_complements(&result1, &result3);
    ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(s21_determinant_test_1) {
    matrix_t result1;
    double result2;
    s21_create_matrix(3, 3, &result1);
    result1.matrix[0][0] = 1;
    result1.matrix[0][1] = 2;
    result1.matrix[0][2] = 3;

    result1.matrix[1][0] = 4;
    result1.matrix[1][1] = 5;
    result1.matrix[1][2] = 6;

    result1.matrix[2][0] = 7;
    result1.matrix[2][1] = 8;
    result1.matrix[2][2] = 9;
    double expected_result = 0;
    s21_determinant(&result1, &result2);
    ck_assert_ldouble_eq(expected_result, result2);
    s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_determinant_test_2) {
    matrix_t result1;
    double result3;
    s21_create_matrix(3, 4, &result1);
    int actual_result = IDENTITY_MATRIX;
    int expected_result = s21_determinant(&result1, &result3);
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_inverse_matrix_test_1) {
    matrix_t result1;
    matrix_t result2;
    matrix_t result3;
    s21_create_matrix(3, 3, &result1);
    result1.matrix[0][0] = 2;
    result1.matrix[0][1] = 5;
    result1.matrix[0][2] = 7;

    result1.matrix[1][0] = 6;
    result1.matrix[1][1] = 3;
    result1.matrix[1][2] = 4;

    result1.matrix[2][0] = 5;
    result1.matrix[2][1] = -2;
    result1.matrix[2][2] = -3;

    int expected_result = s21_create_matrix(3, 3, &result2);

    result2.matrix[0][0] = 1;
    result2.matrix[0][1] = -1;
    result2.matrix[0][2] = 1;

    result2.matrix[1][0] = -38;
    result2.matrix[1][1] = 41;
    result2.matrix[1][2] = -34;

    result2.matrix[2][0] = 27;
    result2.matrix[2][1] = -29;
    result2.matrix[2][2] = 24;
    s21_create_matrix(3, 3, &result3);
    int actual_result = s21_inverse_matrix(&result1, &result3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ck_assert_double_eq(result2.matrix[i][j], result3.matrix[i][j]);
        }
    }
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result2);
    s21_remove_matrix(&result1);
}

START_TEST(s21_inverse_matrix_test_2) {
    matrix_t result1;
    matrix_t result3;
    s21_create_matrix(3, 3, &result1);
    s21_create_matrix(3, 3, &result3);
    result1.matrix[0][0] = 1;
    result1.matrix[0][1] = 2;
    result1.matrix[0][2] = 3;

    result1.matrix[1][0] = 4;
    result1.matrix[1][1] = 5;
    result1.matrix[1][2] = 6;

    result1.matrix[2][0] = 7;
    result1.matrix[2][1] = 8;
    result1.matrix[2][2] = 9;
    int expected_result = IDENTITY_MATRIX;
    int actual_result = s21_inverse_matrix(&result1, &result3);
    ck_assert_uint_eq(expected_result, actual_result);
    s21_remove_matrix(&result3);
    s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_create_matrix_test_1) {
    matrix_t result1;
    int actual_result = s21_create_matrix(-88, -88, &result1);
    int expected_result = INCORRECT_MATRIX;
    ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_s21_matrix = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_s21_matrix);
    tcase_add_test(tc1_s21_matrix, s21_eq_matrix_test_1);
    tcase_add_test(tc1_s21_matrix, s21_eq_matrix_test_2);
    tcase_add_test(tc1_s21_matrix, s21_eq_matrix_test_3);
    tcase_add_test(tc1_s21_matrix, s21_eq_matrix_test_4);
    tcase_add_test(tc1_s21_matrix, s21_sum_matrix_test_1);
    tcase_add_test(tc1_s21_matrix, s21_sum_matrix_test_2);
    tcase_add_test(tc1_s21_matrix, s21_sum_matrix_test_3);
    tcase_add_test(tc1_s21_matrix, s21_sub_matrix_test_1);
    tcase_add_test(tc1_s21_matrix, s21_sub_matrix_test_2);
    tcase_add_test(tc1_s21_matrix, s21_sub_matrix_test_3);
    tcase_add_test(tc1_s21_matrix, s21_mult_number_test_1);
    tcase_add_test(tc1_s21_matrix, s21_mult_number_test_2);
    tcase_add_test(tc1_s21_matrix, s21_mult_matrix_test_1);
    tcase_add_test(tc1_s21_matrix, s21_mult_matrix_test_2);
    tcase_add_test(tc1_s21_matrix, s21_transpose_test_1);
    tcase_add_test(tc1_s21_matrix, s21_transpose_test_2);
    tcase_add_test(tc1_s21_matrix, s21_calc_complements_test_1);
    tcase_add_test(tc1_s21_matrix, s21_calc_complements_test_2);
    tcase_add_test(tc1_s21_matrix, s21_determinant_test_1);
    tcase_add_test(tc1_s21_matrix, s21_determinant_test_2);
    tcase_add_test(tc1_s21_matrix, s21_inverse_matrix_test_1);
    tcase_add_test(tc1_s21_matrix, s21_inverse_matrix_test_2);
    tcase_add_test(tc1_s21_matrix, s21_create_matrix_test_1);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);
    return nf == 0 ? 0 : 1;
}
