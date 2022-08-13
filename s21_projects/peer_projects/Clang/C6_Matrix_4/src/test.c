#include <check.h>
#include "s21_matrix.h"
void s21_matrix_creator(matrix_t *A, double n) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++, n++) {
      A->matrix[i][j] = n;
    }
  }
}
START_TEST(matrix_test) {
  matrix_t test1;
  matrix_t test2;
  matrix_t test3;
  s21_create_matrix(5, 5, &test1);
  s21_create_matrix(5, 5, &test2);
  s21_create_matrix(2, 0, &test3);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), SUCCESS);
  ck_assert_int_eq(s21_create_matrix(2, 0, &test3), 1);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&test3);
}
END_TEST

START_TEST(matrix_test_2) {
  matrix_t test1;
  matrix_t test2;
  s21_create_matrix(5, 5, &test1);
  s21_create_matrix(1, 5, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST
START_TEST(sum_matrix_test) {
  matrix_t test1;
  matrix_t test2;
  matrix_t result_by_func;
  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 2, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 1.0);
  s21_sum_matrix(&test1, &test2, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(2, 2, &result_by_hands);
  result_by_hands.matrix[0][0] = 2.;
  result_by_hands.matrix[0][1] = 4.;
  result_by_hands.matrix[1][0] = 6.;
  result_by_hands.matrix[1][1] = 8.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(sub_matrix_test) {
  matrix_t test1;
  matrix_t test2;
  matrix_t result_by_func;
  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 2, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 1.0);
  s21_sub_matrix(&test1, &test2, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(2, 2, &result_by_hands);
  result_by_hands.matrix[0][0] = 0.;
  result_by_hands.matrix[0][1] = 0.;
  result_by_hands.matrix[1][0] = 0.;
  result_by_hands.matrix[1][1] = 0.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(mult_number_test) {
  matrix_t test1;
  matrix_t result_by_func;
  s21_create_matrix(3, 3, &test1);
  s21_matrix_creator(&test1, 1.0);
  double number = 2;
  s21_mult_number(&test1, number, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 2.;
  result_by_hands.matrix[0][1] = 4.;
  result_by_hands.matrix[0][2] = 6.;
  result_by_hands.matrix[1][0] = 8.;
  result_by_hands.matrix[1][1] = 10.;
  result_by_hands.matrix[1][2] = 12.;
  result_by_hands.matrix[2][0] = 14.;
  result_by_hands.matrix[2][1] = 16.;
  result_by_hands.matrix[2][2] = 18.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(mult_matrix_test) {
  matrix_t test1;
  matrix_t test2;
  matrix_t result_by_func;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 3, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 2.0);
  s21_mult_matrix(&test1, &test2, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 36.;
  result_by_hands.matrix[0][1] = 42.;
  result_by_hands.matrix[0][2] = 48.;
  result_by_hands.matrix[1][0] = 81.;
  result_by_hands.matrix[1][1] = 96.;
  result_by_hands.matrix[1][2] = 111.;
  result_by_hands.matrix[2][0] = 126.;
  result_by_hands.matrix[2][1] = 150.;
  result_by_hands.matrix[2][2] = 174.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(transpose_test) {
  matrix_t test1;
  matrix_t result_by_func;
  s21_create_matrix(3, 3, &test1);
  s21_matrix_creator(&test1, 1.0);
  s21_transpose(&test1, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 1.;
  result_by_hands.matrix[0][1] = 4.;
  result_by_hands.matrix[0][2] = 7.;
  result_by_hands.matrix[1][0] = 2.;
  result_by_hands.matrix[1][1] = 5.;
  result_by_hands.matrix[1][2] = 8.;
  result_by_hands.matrix[2][0] = 3.;
  result_by_hands.matrix[2][1] = 6.;
  result_by_hands.matrix[2][2] = 9.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(calc_complements_test) {
  matrix_t test, result_by_hands, result_by_func;
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  s21_calc_complements(&test, &result_by_func);
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 0;
  result_by_hands.matrix[0][1] = 10;
  result_by_hands.matrix[0][2] = -20;
  result_by_hands.matrix[1][0] = 4;
  result_by_hands.matrix[1][1] = -14;
  result_by_hands.matrix[1][2] = 8;
  result_by_hands.matrix[2][0] = -8;
  result_by_hands.matrix[2][1] = -2;
  result_by_hands.matrix[2][2] = 4;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result_by_hands);
  s21_remove_matrix(&result_by_func);
}
END_TEST

START_TEST(determinant_test) {
    const int rows = 3;
    const int cols = 3;
    matrix_t m1 = {0};

    s21_create_matrix(rows, cols, &m1);
    int m = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m1.matrix[i][j] = m++;
        }
    }
    m1.matrix[2][2] = 0;
    double result = 0;
    int got = s21_determinant(&m1, &result);
    ck_assert_double_eq_tol(result, 27, 1e-6);
    ck_assert_int_eq(got, 0);
    s21_remove_matrix(&m1);
} END_TEST
START_TEST(determinant_test2) {
    const int rows = 5;
    const int cols = 5;
    matrix_t m1 = {0};
    s21_create_matrix(rows, cols, &m1);
    int m = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m1.matrix[i][j] = m++;
        }
    }
    double result = 0;
    int got = s21_determinant(&m1, &result);
    ck_assert_double_eq_tol(result, 0, 1e-6);
    ck_assert_int_eq(got, 0);
    s21_remove_matrix(&m1);
}
END_TEST
START_TEST(inverse_matrix_test) {
  matrix_t test, result_by_hands, result_by_func;
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 2;
  test.matrix[0][1] = 4;
  test.matrix[0][2] = 10;
  test.matrix[1][0] = 10;
  test.matrix[1][1] = 8;
  test.matrix[1][2] = 6;
  test.matrix[2][0] = 10;
  test.matrix[2][1] = 6;
  test.matrix[2][2] = 12;
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = -0.1875;
  result_by_hands.matrix[0][1] = -0.0375;
  result_by_hands.matrix[0][2] = 0.175;
  result_by_hands.matrix[1][0] = 0.1875;
  result_by_hands.matrix[1][1] = 0.2375;
  result_by_hands.matrix[1][2] = -0.275;
  result_by_hands.matrix[2][0] = 0.0625;
  result_by_hands.matrix[2][1] = -0.0875;
  result_by_hands.matrix[2][2] = 0.075;
  s21_inverse_matrix(&test, &result_by_func);
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result_by_hands);
  s21_remove_matrix(&result_by_func);
}
END_TEST
int main(void) {
    Suite *s = suite_create("Core");
    TCase *tc_core = tcase_create("Core");
    SRunner *sr = srunner_create(s);
    int number_fail = 0;
    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, matrix_test);
    tcase_add_test(tc_core, matrix_test_2);
    tcase_add_test(tc_core, sum_matrix_test);
    tcase_add_test(tc_core, sub_matrix_test);
    tcase_add_test(tc_core, mult_number_test);
    tcase_add_test(tc_core, mult_matrix_test);
    tcase_add_test(tc_core, transpose_test);
    tcase_add_test(tc_core, calc_complements_test);
    tcase_add_test(tc_core, determinant_test);
    tcase_add_test(tc_core, determinant_test2);
    tcase_add_test(tc_core, inverse_matrix_test);
    srunner_run_all(sr, CK_NORMAL);
    number_fail = srunner_ntests_failed(sr);
    srunner_free(sr);
    number_fail = (number_fail != 0) ? 1 : 0;
    return number_fail;
}
