#include <check.h>
#include "s21_decimal.h"

START_TEST(s21_is_greater_1) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_2) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_greater_3) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_4) {
    s21_decimal value_1 = {{0, 0, 0, 0}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_5) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_6) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_set_scale(&value_2, 10);
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_7) {
    s21_decimal value_1 = {{234, 0, 0, 0}};
    s21_decimal value_2 = {{2, 0, 0, 0}};
    s21_set_scale(&value_1, 2);
    int return_value = s21_is_greater(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_equal_1) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
    int return_value = s21_is_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_equal_2) {
    s21_decimal value_1 = {{123453u, 654u, 0xFFFFFFFF, 80000000}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
    int return_value = s21_is_equal(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_equal_3) {
    s21_decimal value_1 = {{2, 0, 0, 0}};
    s21_decimal value_2 = {{20, 0, 0, 0}};
    s21_set_scale(&value_2, 1);
    int return_value = s21_is_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_1) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    int return_value = s21_is_greater_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_2) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    int return_value = s21_is_greater_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_3) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_greater_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_4) {
    s21_decimal value_1 = {{0, 0, 0, 0}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_greater_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_5) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_greater_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_6) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_set_scale(&value_2, 2);
    int return_value = s21_is_greater_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_7) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    int return_value = s21_is_greater_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_8) {
    s21_decimal value_1 = {{12345, 0, 0, 0}};
    s21_set_scale(&value_1, 4);
    s21_decimal value_2 = {{12u, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    int return_value = s21_is_greater_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_1) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    int return_value = s21_is_less(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_2) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    int return_value = s21_is_less(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_3) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_less(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_4) {
    s21_decimal value_1 = {{0, 0, 0, 0}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_less(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_5) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_less(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_6) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_set_scale(&value_2, 2);
    int return_value = s21_is_less(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_1) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    int return_value = s21_is_less_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
    s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    int return_value = s21_is_less_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_less_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    s21_set_sign(&value_2, 1);
    int return_value = s21_is_less_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_set_scale(&value_2, 2);
    int return_value = s21_is_less_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    int return_value = s21_is_less_or_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_not_equal_1) {
    s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
    int return_value = s21_is_not_equal(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
    s21_decimal value_1 = {{123453u, 654u, 0xFFFFFFFF, 80000000}};
    s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
    int return_value = s21_is_not_equal(value_1, value_2);
    ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
    s21_decimal value_1 = {{0, 0, 0, 80000000}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    int return_value = s21_is_not_equal(value_1, value_2);
    ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_add_1) {
    s21_decimal value_1 = {{13, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_decimal value_2 = {{286, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_decimal result;
    s21_decimal check = {{416, 0, 0, 0}};
    s21_set_scale(&check, 2);
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_2) {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_2, 1);
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_3) {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_decimal value_2 = {{2, 0, 0, 0}};
    s21_set_scale(&value_2, 1);
    s21_decimal result;
    s21_decimal check = {{0x1, 0x0, 0x1, 0}};
    s21_set_scale(&check, 1);
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_4) {
    s21_decimal value_1 = {{13, 0, 0, 0}};
    s21_set_scale(&value_1, 2);
    s21_decimal value_2 = {{286, 0, 0, 0}};
    s21_set_scale(&value_2, 1);
    s21_decimal result;
    s21_decimal check = {{2873, 0, 0, 0}};
    s21_set_scale(&check, 2);
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_5) {
    s21_decimal value_1 = {{1, 0, 0, 0}};
    s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_set_scale(&value_2, 1);
    s21_decimal result;
    s21_decimal check = {{0x9999999a, 0x99999999, 0x19999999, 0}};
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_6) {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_set_scale(&value_1, 1);
    s21_decimal value_2 = {{1, 0, 0, 0}};
    s21_decimal result;
    s21_decimal check = {{0x9999999a, 0x99999999, 0x19999999, 0}};
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_7) {
    s21_decimal value_1 = {{1, 0, 0, 0}};
    s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal result;
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, BIG_NUM);
}
END_TEST

START_TEST(s21_add_8) {
    s21_decimal value_1 = {{13, 0, 0, 0}};
    s21_set_scale(&value_1, 2);
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{286, 0, 0, 0}};
    s21_set_scale(&value_2, 1);
    s21_decimal result;
    s21_decimal check = {{2847, 0, 0, 0}};
    s21_set_scale(&check, 2);
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_9) {
    s21_decimal value_1 = {{13, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{286, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_set_sign(&value_2, 1);
    s21_decimal result;
    s21_decimal check = {{416, 0, 0, 0}};
    s21_set_scale(&check, 2);
    s21_set_sign(&check, 1);
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_10) {
    s21_decimal value_1 = {{1614, 0, 0, 0}};
    s21_set_scale(&value_1, 3);
    s21_decimal value_2 = {{46071, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_decimal result;
    s21_decimal check = {{462324, 0, 0, 0}};
    s21_set_scale(&check, 3);
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_11) {
    s21_decimal src1, src2;
    src1.bits[3] = 0x300000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xF;
    src1.bits[0] = 0x67E4FEEF;
    src2.bits[3] = 0x300000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFF;
    src2.bits[0] = 0x67E4FFFF;
    s21_decimal result_origin;
    result_origin.bits[3] = 0x300000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x10E;
    result_origin.bits[0] = 0xCFC9FEEE;
    s21_decimal result_our;
    s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_add_12) {
    s21_decimal src1, src2;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x70000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
    s21_decimal result_our;
    s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_sub_1) {
    s21_decimal value_1 = {{13, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{286, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_set_sign(&value_2, 1);
    s21_decimal result;
    s21_decimal check = {{156, 0, 0, 0}};
    s21_set_scale(&check, 2);
    int return_value = s21_sub(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_sub_2) {
    s21_decimal value_1 = {{13, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{286, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_decimal result;
    s21_decimal check = {{416, 0, 0, 0}};
    s21_set_scale(&check, 2);
    s21_set_sign(&check, 1);
    int return_value = s21_sub(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_sub_3) {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{2, 0, 0, 0}};
    s21_decimal result;
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_sub(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, SMALL_NUM);
}
END_TEST

START_TEST(s21_sub_4) {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{2, 0, 0, 0}};
    s21_set_sign(&value_2, 1);
    s21_decimal result;
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, SMALL_NUM);
}
END_TEST

START_TEST(s21_sub_5) {
    s21_decimal value_1 = {{64071, 0, 0, 0}};
    s21_set_scale(&value_1, 4);
    s21_decimal value_2 = {{5919, 0, 0, 0}};
    s21_set_scale(&value_2, 1);
    s21_decimal result;
    s21_decimal check = {{5854929, 0, 0, 0}};
    s21_set_scale(&check, 4);
    s21_set_sign(&check, 1);
    int return_value = s21_sub(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_sub_6) {
    s21_decimal src1, src2;
    src1.bits[3] = 0b00000000000000010000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000000000110011011110000;
    src2.bits[3] = 0b00000000000000110000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00000000000001000101000111010110;
    s21_decimal result_origin;
    result_origin.bits[3] = 0b00000000000000110000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00000000001000111110001111101010;
    s21_decimal result_our;
    s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_mul_1) {
    s21_decimal value_1 = {{5, 0, 0, 0}};
    s21_decimal value_2 = {{7, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{35, 0, 0, 0}};
    int return_value = s21_mul(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mul_2) {
    s21_decimal value_1 = {{0xFFFFFFFF, 0, 0, 0}};
    s21_decimal value_2 = {{0xFFFFFFFF, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{1, 0xFFFFFFFE, 0, 0}};
    int return_value = s21_mul(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mul_3) {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{2, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_mul(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, BIG_NUM);
}
END_TEST

START_TEST(s21_mul_4) {
    s21_decimal value_1 = {{123456u, 123u, 0, 0}};
    s21_decimal value_2 = {{654321u, 654u, 0, 0}};
    s21_set_sign(&value_2, 1);
    s21_set_scale(&value_1, 2);
    s21_set_scale(&value_2, 3);
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{0xcedabe40, 0x99c0c5d, 0x13a3a, 0x80050000}};
    int return_value = s21_mul(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mul_5) {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {{2, 0, 0, 0}};
    s21_set_sign(&value_2, 1);
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_mul(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, SMALL_NUM);
}
END_TEST

START_TEST(s21_div_1) {
    s21_decimal value_1 = {{35, 0, 0, 0}};
    s21_decimal value_2 = {{5, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{70, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_set_scale(&value_2, 2);
    int return_value = s21_div(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_div_2) {
    s21_decimal value_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
    s21_decimal value_2 = {{0x2, 0, 0, 0}};
    s21_set_sign(&value_2, 1);
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
    s21_set_sign(&check, 1);
    int return_value = s21_div(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_div_3) {
    s21_decimal value_1 = {{10, 0, 0, 0}};
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{8, 0, 0, 0}};
    s21_set_sign(&value_2, 1);
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{125, 0, 0, 0}};
    s21_set_scale(&check, 2);
    int return_value = s21_div(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_div_4) {
    s21_decimal value_1 = {{15, 0, 0, 0}};
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{0, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_div(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, DIVISION_BY_ZERO);
}
END_TEST

START_TEST(s21_div_5) {
    s21_decimal value_1 = {{10, 0, 0, 0}};
    s21_decimal value_2 = {{1, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal check = {{1000u, 0, 0, 0}};
    int return_value = s21_div(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mod_1) {
    s21_decimal value_1 = {{46, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_decimal value_2 = {{123, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_decimal check = {{91, 0, 0, 0}};
    s21_set_scale(&check, 2);
    s21_decimal result;
    int return_value = s21_mod(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mod_3) {
    s21_decimal value_1 = {{46, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_decimal value_2 = {{123, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_set_sign(&value_2, 1);
    s21_decimal check = {{91, 0, 0, 0}};
    s21_set_scale(&check, 2);
    s21_decimal result;
    int return_value = s21_mod(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mod_4) {
    s21_decimal value_1 = {{46, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{123, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_decimal check = {{91, 0, 0, 0}};
    s21_set_scale(&check, 2);
    s21_set_sign(&check, 1);
    s21_decimal result;
    int return_value = s21_mod(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mod_5) {
    s21_decimal value_1 = {{46, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_set_sign(&value_1, 1);
    s21_decimal value_2 = {{123, 0, 0, 0}};
    s21_set_scale(&value_2, 2);
    s21_set_sign(&value_2, 1);
    s21_decimal check = {{91, 0, 0, 0}};
    s21_set_scale(&check, 2);
    s21_set_sign(&check, 1);
    s21_decimal result;
    int return_value = s21_mod(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mod_6) {
    s21_decimal src1, src2, res_mod;
    int a = -98765;
    int b = 1234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_7) {
    s21_decimal src1, src2, res_mod;
    float a = 1.2;
    float b = 0.3;
    float res_origin = fmod(a, b);
    float res = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_mod(src1, src2, &res_mod);
    s21_from_decimal_to_float(res_mod, &res);
    ck_assert_float_eq(res_origin, res);
}
END_TEST

START_TEST(s21_from_int_to_decimal_1) {
    int src = 49135648;
    s21_decimal check = {{49135648, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_from_int_to_decimal(src, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
    int src = -49135648;
    s21_decimal check = {{49135648, 0, 0, 0}};
    s21_set_sign(&check, 1);
    s21_decimal result;
    int return_value = s21_from_int_to_decimal(src, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
    int src = -49135648;
    s21_decimal check = {{49135648, 0, 0, 0}};
    s21_set_sign(&check, 1);
    s21_decimal result;
    int return_value = s21_from_int_to_decimal(src, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_int_1) {
    s21_decimal value = {{49135648, 0, 0, 0}};
    s21_set_sign(&value, 1);
    s21_set_scale(&value, 1);
    int dst;
    int check = -4913564;
    int return_value = s21_from_decimal_to_int(value, &dst);
    ck_assert_int_eq(dst, check);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
    s21_decimal value = {{49135648, 0, 0, 0}};
    s21_set_scale(&value, 1);
    int dst;
    int check = 4913564;
    int return_value = s21_from_decimal_to_int(value, &dst);
    ck_assert_int_eq(dst, check);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
    s21_decimal value = {{2, 3, 0, 0}};
    int dst;
    int check = 0;
    int return_value = s21_from_decimal_to_int(value, &dst);
    ck_assert_int_eq(dst, check);
    ck_assert_int_eq(return_value, ERROR);
}
END_TEST

START_TEST(s21_truncate_1) {
    s21_decimal value_1 = {{35, 0, 0, 0}};
    s21_decimal check = {{3, 0, 0, 0}};
    s21_set_scale(&value_1, 1);
    s21_truncate(value_1, &value_1);
    ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(s21_truncate_2) {
    s21_decimal value_1 = {{123456, 0, 0, 0}};
    s21_set_scale(&value_1, 3);
    s21_set_sign(&value_1, 1);
    s21_decimal check = {{123, 0, 0, 0}};
    s21_set_sign(&check, 1);
    s21_truncate(value_1, &value_1);
    ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(s21_truncate_3) {
    s21_decimal src1;
    src1.bits[3] = 0x000A0000;
    src1.bits[2] = 0x0;
    src1.bits[1] = 0xFFFFFFFF;
    src1.bits[0] = 0xFFFFFFFF;
    s21_decimal result;
    result.bits[3] = 0x0;
    result.bits[2] = 0x0;
    result.bits[1] = 0x0;
    result.bits[0] = 0x6DF37F67;
    s21_decimal res_od;
    s21_truncate(src1, &res_od);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_4) {
    s21_decimal src1;
    src1.bits[0] = 0b00000000000000000000000001101101;
    src1.bits[1] = 0b00000000000011000110010101011011;
    src1.bits[2] = 0b00000000000000000011000000111001;
    src1.bits[3] = 0b00000000000011100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b10000111101111000001011000011110;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res_od;
    s21_truncate(src1, &res_od);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_negate_1) {
    s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
    s21_set_sign(&value_1, 1);
    s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
    s21_decimal result;
    int return_value = s21_negate(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_negate_2) {
    s21_decimal value_1 = {{1, 1, 1, 0}};
    s21_decimal check = {{1, 1, 1, 0x80000000}};
    s21_decimal result;
    int return_value = s21_negate(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_1) {
    s21_decimal value_1 = {{7464923, 0, 0, 0}};
    s21_set_scale(&value_1, 5);
    s21_decimal check = {{75, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_round(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_2) {
    s21_decimal value_1 = {{7444923, 0, 0, 0}};
    s21_set_scale(&value_1, 5);
    s21_decimal check = {{74, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_round(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_3) {
    s21_decimal value_1 = {{7464923, 0, 0, 0}};
    s21_set_sign(&value_1, 1);
    s21_set_scale(&value_1, 5);
    s21_decimal check = {{75, 0, 0, 0}};
    s21_set_sign(&check, 1);
    s21_decimal result;
    int return_value = s21_round(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_4) {
    s21_decimal value_1 = {{7444923, 0, 0, 0}};
    s21_set_sign(&value_1, 1);
    s21_set_scale(&value_1, 5);
    s21_decimal check = {{74, 0, 0, 0}};
    s21_set_sign(&check, 1);
    s21_decimal result;
    int return_value = s21_round(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_5) {
    s21_decimal src1;
    src1.bits[0] = 0b01010101001110101110101110110001;
    src1.bits[1] = 0b00001101101101001101101001011111;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000100100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000001;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res_od;
    s21_round(src1, &res_od);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_6) {
    s21_decimal src1;
    src1.bits[0] = 0b10010111011100111001111111111111;
    src1.bits[1] = 0b00111100000010000011000110001101;
    src1.bits[2] = 0b00000000000000000000000000000001;
    src1.bits[3] = 0b10000000000001110000000000000000;
    s21_decimal res_od;
    s21_round(src1, &res_od);
    s21_decimal result;
    result.bits[3] = 0b10000000000000000000000000000000;
    result.bits[2] = 0;
    result.bits[1] = 0b00000000000000000000001000010010;
    result.bits[0] = 0b00110110101101101000110001000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_1) {
    s21_decimal value_1 = {{7444923, 0, 0, 0}};
    s21_set_scale(&value_1, 5);
    s21_decimal check = {{74, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_floor(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_floor_2) {
    s21_decimal value_1 = {{7444923, 0, 0, 0}};
    s21_set_scale(&value_1, 5);
    s21_set_sign(&value_1, 1);
    s21_decimal check = {{75, 0, 0, 0}};
    s21_set_sign(&check, 1);
    s21_decimal result;
    int return_value = s21_floor(value_1, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_floor_3) {
    s21_decimal src1;
    src1.bits[0] = 0b00001111111111111111111111111111;
    src1.bits[1] = 0b00111110001001010000001001100001;
    src1.bits[2] = 0b00100000010011111100111001011110;
    src1.bits[3] = 0b10000000000010100000000000000000;
    s21_decimal res_od;
    s21_floor(src1, &res_od);
    s21_decimal result;
    result.bits[0] = 0b10100111011001000000000000000000;
    result.bits[1] = 0b00001101111000001011011010110011;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_1) {
    float f = 0.03;
    s21_decimal result;
    s21_decimal check = {{3, 0, 0, 0}};
    s21_set_scale(&check, 2);
    int return_value = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
    float f = -128.023;
    s21_decimal result;
    s21_decimal check = {{12802299, 0, 0, 0}};
    s21_set_scale(&check, 5);
    s21_set_sign(&check, 1);
    int return_value = s21_from_float_to_decimal(f, &result);
    // ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
    float f = 1.0 / 0.0;
    s21_decimal result;
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, ERROR);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
    float f = 0.0 / 0.0;
    s21_decimal result;
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, ERROR);
}
END_TEST

START_TEST(s21_from_decimal_to_float_1) {
    s21_decimal value = {{1812, 0, 0, 0}};
    s21_set_sign(&value, 1);
    float result;
    float check = -1812;
    int return_value = s21_from_decimal_to_float(value, &result);
    ck_assert_float_eq(result, check);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
    s21_decimal value = {{18122, 0, 0, 0}};
    s21_set_scale(&value, 3);
    s21_set_sign(&value, 1);
    float result;
    float check = -18.122;
    int return_value = s21_from_decimal_to_float(value, &result);
    ck_assert_float_eq(result, check);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
    s21_decimal value = {{0xFFFFFF, 0, 0, 0}};
    float result;
    float check = 16777215;
    int return_value = s21_from_decimal_to_float(value, &result);
    ck_assert_float_eq(result, check);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
    s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
    float result;
    float check = 0xFFFFFFFFFFFFFFFF;
    int return_value = s21_from_decimal_to_float(value, &result);
    ck_assert_float_eq(result, check);
    ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.bits[0] = 23450987;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147745792;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, -2345.0987);
    ck_assert_int_eq(result, 0);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, s21_is_greater_1);
    tcase_add_test(tc1_1, s21_is_greater_2);
    tcase_add_test(tc1_1, s21_is_greater_3);
    tcase_add_test(tc1_1, s21_is_greater_4);
    tcase_add_test(tc1_1, s21_is_greater_5);
    tcase_add_test(tc1_1, s21_is_greater_6);
    tcase_add_test(tc1_1, s21_is_greater_7);
    tcase_add_test(tc1_1, s21_is_equal_1);
    tcase_add_test(tc1_1, s21_is_equal_2);
    tcase_add_test(tc1_1, s21_is_equal_3);
    tcase_add_test(tc1_1, s21_is_greater_or_equal_1);
    tcase_add_test(tc1_1, s21_is_greater_or_equal_2);
    tcase_add_test(tc1_1, s21_is_greater_or_equal_3);
    tcase_add_test(tc1_1, s21_is_greater_or_equal_4);
    tcase_add_test(tc1_1, s21_is_greater_or_equal_5);
    tcase_add_test(tc1_1, s21_is_greater_or_equal_6);
    tcase_add_test(tc1_1, s21_is_greater_or_equal_7);
    tcase_add_test(tc1_1, s21_is_greater_or_equal_8);
    tcase_add_test(tc1_1, s21_is_less_1);
    tcase_add_test(tc1_1, s21_is_less_2);
    tcase_add_test(tc1_1, s21_is_less_3);
    tcase_add_test(tc1_1, s21_is_less_4);
    tcase_add_test(tc1_1, s21_is_less_5);
    tcase_add_test(tc1_1, s21_is_less_6);
    tcase_add_test(tc1_1, s21_is_less_or_equal_1);
    tcase_add_test(tc1_1, s21_is_less_or_equal_2);
    tcase_add_test(tc1_1, s21_is_less_or_equal_3);
    tcase_add_test(tc1_1, s21_is_less_or_equal_4);
    tcase_add_test(tc1_1, s21_is_less_or_equal_5);
    tcase_add_test(tc1_1, s21_is_less_or_equal_6);
    tcase_add_test(tc1_1, s21_is_not_equal_1);
    tcase_add_test(tc1_1, s21_is_not_equal_2);
    tcase_add_test(tc1_1, s21_is_not_equal_3);
    tcase_add_test(tc1_1, s21_add_1);
    tcase_add_test(tc1_1, s21_add_2);
    tcase_add_test(tc1_1, s21_add_3);
    tcase_add_test(tc1_1, s21_add_4);
    tcase_add_test(tc1_1, s21_add_5);
    tcase_add_test(tc1_1, s21_add_6);
    tcase_add_test(tc1_1, s21_add_7);
    tcase_add_test(tc1_1, s21_add_8);
    tcase_add_test(tc1_1, s21_add_9);
    tcase_add_test(tc1_1, s21_add_10);
    tcase_add_test(tc1_1, s21_add_11);
    tcase_add_test(tc1_1, s21_add_12);
    tcase_add_test(tc1_1, s21_sub_1);
    tcase_add_test(tc1_1, s21_sub_2);
    tcase_add_test(tc1_1, s21_sub_3);
    tcase_add_test(tc1_1, s21_sub_4);
    tcase_add_test(tc1_1, s21_sub_5);
    tcase_add_test(tc1_1, s21_sub_6);
    tcase_add_test(tc1_1, s21_mul_1);
    tcase_add_test(tc1_1, s21_mul_2);
    tcase_add_test(tc1_1, s21_mul_3);
    tcase_add_test(tc1_1, s21_mul_4);
    tcase_add_test(tc1_1, s21_mul_5);
    tcase_add_test(tc1_1, s21_div_1);
    tcase_add_test(tc1_1, s21_div_2);
    tcase_add_test(tc1_1, s21_div_3);
    tcase_add_test(tc1_1, s21_div_4);
    tcase_add_test(tc1_1, s21_div_5);
    tcase_add_test(tc1_1, s21_mod_1);
    tcase_add_test(tc1_1, s21_mod_3);
    tcase_add_test(tc1_1, s21_mod_4);
    tcase_add_test(tc1_1, s21_mod_5);
    tcase_add_test(tc1_1, s21_mod_6);
    tcase_add_test(tc1_1, s21_mod_7);
    tcase_add_test(tc1_1, s21_from_int_to_decimal_1);
    tcase_add_test(tc1_1, s21_from_int_to_decimal_2);
    tcase_add_test(tc1_1, s21_from_int_to_decimal_3);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_1);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_2);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_3);
    tcase_add_test(tc1_1, s21_truncate_1);
    tcase_add_test(tc1_1, s21_truncate_2);
    tcase_add_test(tc1_1, s21_truncate_3);
    tcase_add_test(tc1_1, s21_truncate_4);
    tcase_add_test(tc1_1, s21_negate_1);
    tcase_add_test(tc1_1, s21_negate_2);
    tcase_add_test(tc1_1, s21_round_1);
    tcase_add_test(tc1_1, s21_round_2);
    tcase_add_test(tc1_1, s21_round_3);
    tcase_add_test(tc1_1, s21_round_4);
    tcase_add_test(tc1_1, s21_round_5);
    tcase_add_test(tc1_1, s21_round_6);
    tcase_add_test(tc1_1, s21_floor_1);
    tcase_add_test(tc1_1, s21_floor_2);
    tcase_add_test(tc1_1, s21_floor_3);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_1);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_2);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_2);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_3);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_4);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_1);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_2);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_3);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_4);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_5);

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);
    return 0;
}
