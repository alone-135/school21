// our
#include "s21_decimal.h"

#include <check.h>
#include <string.h>

enum bits { LOW, MID, HIGH, SCALE };

START_TEST(CV___FROM_INT_TO_DECIMAL) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal test_value_3 = {{5, 4, 2, 2147483652}};

    s21_from_int_to_decimal(1899, &test_value_1);
    ck_assert_int_eq(test_value_1.bits[0], 1899);
    ck_assert_int_eq(test_value_1.bits[1], 0);
    ck_assert_int_eq(test_value_1.bits[2], 0);
    ck_assert_int_eq(test_value_1.bits[3], 0);

    s21_from_int_to_decimal(-2147000123, &test_value_2);
    ck_assert_int_eq(test_value_2.bits[0], 2147000123);
    ck_assert_int_eq(test_value_2.bits[1], 0);
    ck_assert_int_eq(test_value_2.bits[2], 0);
    ck_assert_int_eq(test_value_2.bits[3], -2147483648);

    s21_from_int_to_decimal(0, &test_value_3);
    ck_assert_int_eq(test_value_3.bits[1], 0);
    ck_assert_int_eq(test_value_3.bits[2], 0);
    ck_assert_int_eq(test_value_3.bits[3], 0);
    ck_assert_int_eq(test_value_3.bits[0], 0);
}
END_TEST

START_TEST(CV___FROM_FLOAT_TO_DECIMAL) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal test_value_3 = {{5, 4, 2, 2147483652}};
    s21_decimal test_value_4 = {{0, 0, 0, 0}};

    s21_from_float_to_decimal(1899.152369, &test_value_1);
    ck_assert_int_eq(test_value_1.bits[0], 18991524); /* выдаёт 18991524 */
    ck_assert_int_eq(test_value_1.bits[1],
                     0); /* округляет до 4 знаков после запятой, а не до 6 */
    ck_assert_int_eq(test_value_1.bits[2], 0);
    ck_assert_int_eq(test_value_1.bits[3], 262144);
    /* 393216 = 10^(-6) */ /* выдаёт 262144 = 10^(-4) */

    s21_from_float_to_decimal(-2147.123654, &test_value_2);
    ck_assert_int_eq(test_value_2.bits[0], 2147124); /* выдаёт 2147124 */
    ck_assert_int_eq(test_value_2.bits[1],
                     0); /* округляет до 3 знаков после запятой, а не до 6 */
    ck_assert_int_eq(test_value_2.bits[2], 0);
    ck_assert_int_eq(test_value_2.bits[3], -2147287040);

    s21_from_float_to_decimal(0.0000, &test_value_3);
    ck_assert_int_eq(test_value_3.bits[0], 0);
    ck_assert_int_eq(test_value_3.bits[1], 0);
    ck_assert_int_eq(test_value_3.bits[2], 0);
    ck_assert_int_eq(test_value_3.bits[3], 0);

    s21_from_float_to_decimal(0.123456, &test_value_4);
    ck_assert_int_eq(test_value_4.bits[0], 123456);
    ck_assert_int_eq(test_value_4.bits[1], 0);
    ck_assert_int_eq(test_value_4.bits[2], 0);
    ck_assert_int_eq(test_value_4.bits[3], 393216);
}
END_TEST

START_TEST(CV___FROM_DECIMAL_TO_INT) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{2000, 0, 0, 0}};
    s21_decimal test_value_3 = {{2111222338, 0, 0, 2147483648}};
    int dst_1 = 0;
    int dst_2 = 0;
    int dst_3 = 0;

    s21_from_decimal_to_int(test_value_1, &dst_1);
    ck_assert_int_eq(dst_1, 0);

    s21_from_decimal_to_int(test_value_2, &dst_2);
    ck_assert_int_eq(dst_2, 2000);

    s21_from_decimal_to_int(test_value_3, &dst_3);
    ck_assert_int_eq(dst_3, -2111222338);
}
END_TEST

START_TEST(CV___FROM_DECIMAL_TO_FLOAT) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {
        {4123456, 0, 0, 393216}};  //  393216 = 10^(-6)  //  196608 = 10^(-3)
    s21_decimal test_value_3 = {{32781, 0, 0, 2147745792}};
    float dst_1 = 0;
    float dst_2 = 0;
    float dst_3 = 0;

    s21_from_decimal_to_float(test_value_1, &dst_1);
    ck_assert_float_eq(dst_1, 0.000000);

    s21_from_decimal_to_float(test_value_2, &dst_2);
    ck_assert_float_eq_tol(dst_2, 4.123456, 1e-6);

    s21_from_decimal_to_float(test_value_3, &dst_3);
    ck_assert_float_eq(dst_3, -3.2781);
}
END_TEST

START_TEST(CM___LESS) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};

    s21_from_int_to_decimal(10, &test_value_1);
    s21_from_int_to_decimal(15, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(2147483647, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(1, &test_value_1);
    s21_from_int_to_decimal(1, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-1, &test_value_1);
    s21_from_int_to_decimal(-1, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(-2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(-2147483648, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(10.457, &test_value_1);
    s21_from_float_to_decimal(15.245, &test_value_2);
    ck_assert_float_eq(s21_is_less(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(1.000, &test_value_1);
    s21_from_float_to_decimal(1.0, &test_value_2);
    ck_assert_float_eq(s21_is_less(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-1.01, &test_value_1);
    s21_from_float_to_decimal(-1.01, &test_value_2);
    ck_assert_float_eq(s21_is_less(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-19993.05162, &test_value_1);
    s21_from_float_to_decimal(-19993, &test_value_2);
    ck_assert_float_eq(s21_is_less(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-6739.165156, &test_value_1);
    s21_from_float_to_decimal(-2107483647.56516156156, &test_value_2);
    ck_assert_float_eq(s21_is_less(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-6739, &test_value_1);
    s21_from_float_to_decimal(2147483647.0, &test_value_2);
    ck_assert_float_eq(s21_is_less(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(6739.020202, &test_value_1);
    s21_from_float_to_decimal(-2147483648.0, &test_value_2);
    ck_assert_float_eq(s21_is_less(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(CM___LESS_OR_EQUAL) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};

    s21_from_int_to_decimal(10, &test_value_1);
    s21_from_int_to_decimal(15, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(2147483647, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(1, &test_value_1);
    s21_from_int_to_decimal(1, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-1, &test_value_1);
    s21_from_int_to_decimal(-1, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(-2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(-2147483648, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(10.457, &test_value_1);
    s21_from_float_to_decimal(15.245, &test_value_2);
    ck_assert_float_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(1.000, &test_value_1);
    s21_from_float_to_decimal(1.0, &test_value_2);
    ck_assert_float_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-1.0, &test_value_1);
    s21_from_float_to_decimal(-1.0000, &test_value_2);
    ck_assert_float_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-19993.05162, &test_value_1);
    s21_from_float_to_decimal(-19993, &test_value_2);
    ck_assert_float_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-6739.165156, &test_value_1);
    s21_from_float_to_decimal(-2147483647.56516156156, &test_value_2);
    ck_assert_float_eq(s21_is_less_or_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-6739, &test_value_1);
    s21_from_float_to_decimal(2147483647.0, &test_value_2);
    ck_assert_float_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(6739.020202, &test_value_1);
    s21_from_float_to_decimal(-2147483648.0, &test_value_2);
    ck_assert_float_eq(s21_is_less_or_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(CM___GREATER) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};

    s21_from_int_to_decimal(10, &test_value_1);
    s21_from_int_to_decimal(15, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(2147483647, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(1, &test_value_1);
    s21_from_int_to_decimal(1, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-1, &test_value_1);
    s21_from_int_to_decimal(-1, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(-2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(-2147483648, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(10.457, &test_value_1);
    s21_from_float_to_decimal(15.245, &test_value_2);
    ck_assert_float_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(1.000, &test_value_1);
    s21_from_float_to_decimal(1.0, &test_value_2);
    ck_assert_float_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-1.0, &test_value_1);
    s21_from_float_to_decimal(-1.0, &test_value_2);
    ck_assert_float_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-19993.05162, &test_value_1);
    s21_from_float_to_decimal(-19993, &test_value_2);
    ck_assert_float_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-6739, &test_value_1);
    s21_from_float_to_decimal(2147483647.0, &test_value_2);
    ck_assert_float_eq(s21_is_greater(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(6739.020202, &test_value_1);
    s21_from_float_to_decimal(-2147483648.0, &test_value_2);
    ck_assert_float_eq(s21_is_greater(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(CM___GREATER_OR_EQUAL) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};

    s21_from_int_to_decimal(10, &test_value_1);
    s21_from_int_to_decimal(15, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(2147483647, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(1, &test_value_1);
    s21_from_int_to_decimal(1, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-1, &test_value_1);
    s21_from_int_to_decimal(-1, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(-2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(-2147483648, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(10.457, &test_value_1);
    s21_from_float_to_decimal(15.245, &test_value_2);
    ck_assert_float_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(1.000, &test_value_1);
    s21_from_float_to_decimal(1.0, &test_value_2);
    ck_assert_float_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-1.0, &test_value_1);
    s21_from_float_to_decimal(-1.0, &test_value_2);
    ck_assert_float_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-19993.05162, &test_value_1);
    s21_from_float_to_decimal(-19993, &test_value_2);
    ck_assert_float_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-6739.165156, &test_value_1);
    s21_from_float_to_decimal(-1147483647.56516156156, &test_value_2);
    ck_assert_float_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-6739, &test_value_1);
    s21_from_float_to_decimal(2147483647.0, &test_value_2);
    ck_assert_float_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(6739.020202, &test_value_1);
    s21_from_float_to_decimal(-2147483648.0, &test_value_2);
    ck_assert_float_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(CM___EQUAL) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};

    s21_from_int_to_decimal(10, &test_value_1);
    s21_from_int_to_decimal(15, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(2147483647, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(1, &test_value_1);
    s21_from_int_to_decimal(1, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-1, &test_value_1);
    s21_from_int_to_decimal(-1, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(-2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(-2147483648, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(10.457, &test_value_1);
    s21_from_float_to_decimal(15.245, &test_value_2);
    ck_assert_float_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(2147483647.0000, &test_value_1);
    s21_from_float_to_decimal(19993.26556, &test_value_2);
    ck_assert_float_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(1.000, &test_value_1);
    s21_from_float_to_decimal(1.0, &test_value_2);
    ck_assert_float_eq(s21_is_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-1.0, &test_value_1);
    s21_from_float_to_decimal(-1.0, &test_value_2);
    ck_assert_float_eq(s21_is_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-19993.05162, &test_value_1);
    s21_from_float_to_decimal(-19993, &test_value_2);
    ck_assert_float_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-6739.165156, &test_value_1);
    s21_from_float_to_decimal(-2147483647.56516156156, &test_value_2);
    ck_assert_float_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-6739, &test_value_1);
    s21_from_float_to_decimal(2147483647.0, &test_value_2);
    ck_assert_float_eq(s21_is_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(6739.020202, &test_value_1);
    s21_from_float_to_decimal(-2147483648.0, &test_value_2);
    ck_assert_float_eq(s21_is_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(CM___NOT_EQUAL) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};

    s21_from_int_to_decimal(10, &test_value_1);
    s21_from_int_to_decimal(15, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(2147483647, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(1, &test_value_1);
    s21_from_int_to_decimal(1, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-1, &test_value_1);
    s21_from_int_to_decimal(-1, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 0);

    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(-2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(-6739, &test_value_1);
    s21_from_int_to_decimal(2147483647, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(-2147483648, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(10.457, &test_value_1);
    s21_from_float_to_decimal(15.245, &test_value_2);
    ck_assert_float_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(2147483647.0000, &test_value_1);
    s21_from_float_to_decimal(19993.26556, &test_value_2);
    ck_assert_float_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(1.000, &test_value_1);
    s21_from_float_to_decimal(1.0, &test_value_2);
    ck_assert_float_eq(s21_is_not_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-1.0, &test_value_1);
    s21_from_float_to_decimal(-1.0, &test_value_2);
    ck_assert_float_eq(s21_is_not_equal(test_value_1, test_value_2), 0);

    s21_from_float_to_decimal(-19993.05162, &test_value_1);
    s21_from_float_to_decimal(-19993, &test_value_2);
    ck_assert_float_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-6739.165156, &test_value_1);
    s21_from_float_to_decimal(-2147483647.56516156156, &test_value_2);
    ck_assert_float_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(-6739, &test_value_1);
    s21_from_float_to_decimal(2147483647.0, &test_value_2);
    ck_assert_float_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    s21_from_float_to_decimal(6739.020202, &test_value_1);
    s21_from_float_to_decimal(-2147483648.0, &test_value_2);
    ck_assert_float_eq(s21_is_not_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(R___FLOOR) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal test_value_3 = {{0, 0, 0, 0}};
    s21_decimal test_value_4 = {{0, 0, 0, 0}};

    s21_decimal result_dec_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec_3 = {{0, 0, 0, 0}};
    s21_decimal result_dec_4 = {{0, 0, 0, 0}};

    float result_1 = 0.0;
    float result_2 = 0.0;
    float result_3 = 0.0;
    float result_4 = 0.0;

    s21_from_float_to_decimal(-1452.980202308, &test_value_1);
    s21_floor(test_value_1, &result_dec_1);
    s21_from_decimal_to_float(result_dec_1, &result_1);
    ck_assert_float_eq(result_1, -1453);

    s21_from_float_to_decimal(1452.980202308, &test_value_2);
    s21_floor(test_value_2, &result_dec_2);
    s21_from_decimal_to_float(result_dec_2, &result_2);
    ck_assert_float_eq(result_2, 1452);

    s21_from_float_to_decimal(1452, &test_value_3);
    s21_floor(test_value_3, &result_dec_3);
    s21_from_decimal_to_float(result_dec_3, &result_3);
    ck_assert_float_eq(result_3, 1452);

    s21_from_float_to_decimal(-1452, &test_value_4);
    s21_floor(test_value_4, &result_dec_4);
    s21_from_decimal_to_float(result_dec_4, &result_4);
    ck_assert_float_eq(result_4, -1452);
}
END_TEST

START_TEST(R___ROUND) {
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal test_value_3 = {{0, 0, 0, 0}};
    s21_decimal test_value_4 = {{0, 0, 0, 0}};

    s21_decimal result_dec_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec_3 = {{0, 0, 0, 0}};
    s21_decimal result_dec_4 = {{0, 0, 0, 0}};

    float result_2 = 0.0;
    float result_3 = 0.0;
    float result_4 = 0.0;

    s21_from_float_to_decimal(1452.980202308, &test_value_2);
    s21_round(test_value_2, &result_dec_2);
    s21_from_decimal_to_float(result_dec_2, &result_2);
    ck_assert_float_eq(result_2, 1453);

    s21_from_float_to_decimal(1452, &test_value_3);
    s21_round(test_value_3, &result_dec_3);
    s21_from_decimal_to_float(result_dec_3, &result_3);
    ck_assert_float_eq(result_3, 1452);

    s21_from_float_to_decimal(-1452, &test_value_4);
    s21_round(test_value_4, &result_dec_4);
    s21_from_decimal_to_float(result_dec_4, &result_4);
    ck_assert_float_eq(result_4, -1452);
}
END_TEST

START_TEST(R___TRUNCATE) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal test_value_3 = {{0, 0, 0, 0}};
    s21_decimal test_value_4 = {{0, 0, 0, 0}};
    s21_decimal result_dec_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec_3 = {{0, 0, 0, 0}};
    s21_decimal result_dec_4 = {{0, 0, 0, 0}};
    float result_1 = 0.0;
    float result_2 = 0.0;
    float result_3 = 0.0;
    float result_4 = 0.0;

    s21_from_float_to_decimal(-1452.180202308, &test_value_1);
    s21_truncate(test_value_1, &result_dec_1);
    s21_from_decimal_to_float(result_dec_1, &result_1);
    ck_assert_float_eq(result_1, -1452);

    s21_from_float_to_decimal(1452.980202308, &test_value_2);
    s21_truncate(test_value_2, &result_dec_2);
    s21_from_decimal_to_float(result_dec_2, &result_2);
    ck_assert_float_eq(result_2, 1452);

    s21_from_float_to_decimal(1452, &test_value_3);
    s21_truncate(test_value_3, &result_dec_3);
    s21_from_decimal_to_float(result_dec_3, &result_3);
    ck_assert_float_eq(result_3, 1452);

    s21_from_float_to_decimal(-1452, &test_value_4);
    s21_truncate(test_value_4, &result_dec_4);
    s21_from_decimal_to_float(result_dec_4, &result_4);
    ck_assert_float_eq(result_4, -1452);
}
END_TEST

START_TEST(R___NEGATE) {
    s21_decimal test_value_3 = {{0, 0, 0, 0}};
    s21_decimal test_value_4 = {{0, 0, 0, 0}};
    s21_decimal result_dec_3 = {{0, 0, 0, 0}};
    s21_decimal result_dec_4 = {{0, 0, 0, 0}};
    float result_3 = 0.0;
    float result_4 = 0.0;

    s21_from_float_to_decimal(1452, &test_value_3);
    s21_negate(test_value_3, &result_dec_3);
    s21_from_decimal_to_float(result_dec_3, &result_3);
    ck_assert_float_eq(result_3, -1452);

    s21_from_float_to_decimal(0, &test_value_4);
    s21_negate(test_value_4, &result_dec_4);
    s21_from_decimal_to_float(result_dec_4, &result_4);
    ck_assert_float_eq(result_4, 0);
}
END_TEST

s21_decimal value_0 = {{0, 0, 0, 0}};
s21_decimal value_1 = {{1, 0, 0, 0}};
s21_decimal value_2 = {{1, 1, 0, 0}};
s21_decimal value_3 = {{1, 1, 1, 0}};

s21_decimal value_11 = {{4294967295, 0, 0, 0}};
s21_decimal value_21 = {{4294967295, 4294967295, 0, 0}};
s21_decimal value_31 = {{4294967295, 4294967295, 4294967295, 0}};

s21_decimal value_12 = {{2147483648, 0, 0, 0}};
s21_decimal value_22 = {{2147483648, 2000000000, 0, 0}};
s21_decimal value_32 = {{2147483648, 2000000000, 2000000000, 0}};

s21_decimal value_01 = {{28000000, 6, 18, 0}};
s21_decimal value_02 = {{4000000, 3, 3, 0}};
s21_decimal value_03 = {{18999, 0, 0, 0}};
s21_decimal value_04 = {{1001, 0, 0, 0}};

s21_decimal value_41 = {{22222, 0, 0, 196608}};
s21_decimal value_42 = {{444, 0, 0, 131072}};

// negative
s21_decimal value_0_n = {{0, 0, 0, 2147483648}};
s21_decimal value_1_n = {{1, 0, 0, 2147483648}};
s21_decimal value_2_n = {{1, 1, 0, 2147483648}};
s21_decimal value_3_n = {{1, 1, 1, 2147483648}};
s21_decimal value_11_n = {{4294967295, 0, 0, 2147483648}};
s21_decimal value_21_n = {{4294967295, 4294967295, 0, 2147483648}};
s21_decimal value_31_n = {{4294967295, 4294967295, 4294967295, 2147483648}};
s21_decimal value_12_n = {{2147483648, 0, 0, 2147483648}};
s21_decimal value_22_n = {{2147483648, 2000000000, 0, 2147483648}};
s21_decimal value_32_n = {{2147483648, 2000000000, 2000000000, 2147483648}};

s21_decimal value_01_n = {{28000000, 6, 18, 2147483648}};
s21_decimal value_02_n = {{4000000, 3, 3, 2147483648}};
s21_decimal value_03_n = {{18999, 0, 0, 2147483648}};
s21_decimal value_04_n = {{1001, 0, 0, 2147483648}};

s21_decimal result = {{0, 0, 0, 0}};

START_TEST(s21_add_test) {
    int result_int;

    ck_assert_uint_eq(s21_add(value_0, value_0, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, 0);

    ck_assert_uint_eq(s21_add(value_0, value_1, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, 1);

    ck_assert_uint_eq(s21_add(value_0, value_2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_add(value_41, value_42, &result), 0);
    ck_assert_uint_eq(result.bits[0], 26662);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 196608);

    ck_assert_uint_eq(s21_add(value_0, value_3, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_add(value_11, value_1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_add(value_11, value_2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 2);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_add(value_11, value_3, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 2);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], 0);
    //
    ck_assert_uint_eq(s21_add(value_21, value_1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_add(value_21, value_2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_add(value_21, value_3, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 2);
    ck_assert_uint_eq(result.bits[3], 0);
    //
    ck_assert_uint_eq(s21_add(value_31, value_1, &result), 1);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);
    //
    ck_assert_uint_eq(s21_add(value_01, value_02, &result), 0);
    ck_assert_uint_eq(result.bits[0], 32000000);
    ck_assert_uint_eq(result.bits[1], 9);
    ck_assert_uint_eq(result.bits[2], 21);
    ck_assert_uint_eq(result.bits[3], 0);

    //// neg

    ck_assert_uint_eq(s21_add(value_0_n, value_0_n, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, 0);

    ck_assert_uint_eq(s21_add(value_0_n, value_1_n, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, -1);

    ck_assert_uint_eq(s21_add(value_0_n, value_2_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_add(value_0_n, value_3_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_add(value_11_n, value_1_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_add(value_11_n, value_2_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 2);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_add(value_11_n, value_3_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 2);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    //
    ck_assert_uint_eq(s21_add(value_21_n, value_1_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_add(value_21_n, value_2_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_add(value_21_n, value_3_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 2);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    //
    ck_assert_uint_eq(s21_add(value_31_n, value_1_n, &result), 1);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    //
    ck_assert_uint_eq(s21_add(value_01_n, value_02_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 32000000);
    ck_assert_uint_eq(result.bits[1], 9);
    ck_assert_uint_eq(result.bits[2], 21);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    // +-
    ck_assert_uint_eq(s21_add(value_0, value_0_n, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, 0);

    ck_assert_uint_eq(s21_add(value_1, value_2_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_add(value_1, value_3_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_add(value_11_n, value_2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_add(value_11, value_3_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_add(value_21_n, value_3, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);
    //
    ck_assert_uint_eq(s21_add(value_01_n, value_02, &result), 0);
    ck_assert_uint_eq(result.bits[0], 24000000);
    ck_assert_uint_eq(result.bits[1], 3);
    ck_assert_uint_eq(result.bits[2], 15);
    ck_assert_uint_eq(result.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_sub_test) {
    int result_int;

    ck_assert_uint_eq(s21_sub(value_0, value_0, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, 0);

    ck_assert_uint_eq(s21_sub(value_0, value_1, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, -1);

    ck_assert_uint_eq(s21_sub(value_0, value_2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_sub(value_0, value_3, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    //
    ck_assert_uint_eq(s21_sub(value_12, value_1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2147483647);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_sub(value_11, value_2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_sub(value_11, value_3, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    //
    ck_assert_uint_eq(s21_sub(value_22, value_1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2147483647);
    ck_assert_uint_eq(result.bits[1], 2000000000);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_sub(value_22, value_2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2147483647);
    ck_assert_uint_eq(result.bits[1], 1999999999);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_sub(value_21, value_3, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    // //
    ck_assert_uint_eq(s21_sub(value_32, value_1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2147483647);
    ck_assert_uint_eq(result.bits[1], 2000000000);
    ck_assert_uint_eq(result.bits[2], 2000000000);
    ck_assert_uint_eq(result.bits[3], 0);
    //
    ck_assert_uint_eq(s21_sub(value_01, value_02, &result), 0);
    ck_assert_uint_eq(result.bits[0], 24000000);
    ck_assert_uint_eq(result.bits[1], 3);
    ck_assert_uint_eq(result.bits[2], 15);
    ck_assert_uint_eq(result.bits[3], 0);
    //// neg
    ck_assert_uint_eq(s21_sub(value_0_n, value_0_n, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, 0);

    ck_assert_uint_eq(s21_sub(value_0_n, value_1_n, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, 1);

    ck_assert_uint_eq(s21_sub(value_0_n, value_2_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_sub(value_0_n, value_3_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 1);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_sub(value_12_n, value_1_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2147483647);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_sub(value_11_n, value_2_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_sub(value_11_n, value_3_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], 0);
    //
    ck_assert_uint_eq(s21_sub(value_22_n, value_1_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2147483647);
    ck_assert_uint_eq(result.bits[1], 2000000000);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_sub(value_22_n, value_2_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2147483647);
    ck_assert_uint_eq(result.bits[1], 1999999999);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_sub(value_21_n, value_3_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);
    //
    ck_assert_uint_eq(s21_sub(value_32_n, value_1_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2147483647);
    ck_assert_uint_eq(result.bits[1], 2000000000);
    ck_assert_uint_eq(result.bits[2], 2000000000);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    //
    ck_assert_uint_eq(s21_sub(value_01_n, value_02_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 24000000);
    ck_assert_uint_eq(result.bits[1], 3);
    ck_assert_uint_eq(result.bits[2], 15);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    // +-
    ck_assert_uint_eq(s21_sub(value_0, value_0_n, &result), 0);
    s21_from_decimal_to_int(result, &result_int);
    ck_assert_uint_eq(result_int, 0);

    ck_assert_uint_eq(s21_sub(value_1, value_2_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_sub(value_1_n, value_3, &result), 0);
    ck_assert_uint_eq(result.bits[0], 2);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_sub(value_11, value_1_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_sub(value_11_n, value_2, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 2);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_sub(value_11, value_3_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 2);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], 0);
    //
    ck_assert_uint_eq(s21_sub(value_21_n, value_1, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_sub(value_21, value_2_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 1);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_sub(value_21_n, value_3, &result), 0);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 1);
    ck_assert_uint_eq(result.bits[2], 2);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    //
    ck_assert_uint_eq(s21_sub(value_31_n, value_1, &result), 1);
    ck_assert_uint_eq(result.bits[0], 0);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);
    //
    ck_assert_uint_eq(s21_sub(value_01_n, value_02, &result), 0);
    ck_assert_uint_eq(result.bits[0], 32000000);
    ck_assert_uint_eq(result.bits[1], 9);
    ck_assert_uint_eq(result.bits[2], 21);
    ck_assert_uint_eq(result.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test) {
    ck_assert_uint_eq(s21_mul(value_03, value_04, &result), 0);
    ck_assert_uint_eq(result.bits[0], 19017999);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_div_test) {
    ck_assert_uint_eq(s21_div(value_01, value_02, &result), 0);
    ck_assert_uint_eq(result.bits[0], 5);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_div(value_01_n, value_02_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 5);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_div(value_01, value_02_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 5);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_div(value_01_n, value_02, &result), 0);
    ck_assert_uint_eq(result.bits[0], 5);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_div(value_01, value_0, &result), 3);
}
END_TEST

START_TEST(s21_mod_test) {
    ck_assert_uint_eq(s21_mod(value_03, value_04, &result), 0);
    ck_assert_uint_eq(result.bits[0], 981);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_mod(value_03_n, value_04_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 981);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);

    ck_assert_uint_eq(s21_mod(value_03, value_04_n, &result), 0);
    ck_assert_uint_eq(result.bits[0], 981);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);

    ck_assert_uint_eq(s21_mod(value_03_n, value_04, &result), 0);
    ck_assert_uint_eq(result.bits[0], 981);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], -2147483648);
}
END_TEST

int main() {
    Suite *s1 = suite_create("s21_decimal: ");
    SRunner *sr = srunner_create(s1);

    TCase *s21_from_int_to_decimal = tcase_create("___");
    suite_add_tcase(s1, s21_from_int_to_decimal);
    tcase_add_test(s21_from_int_to_decimal, CV___FROM_INT_TO_DECIMAL);

    TCase *s21_from_float_to_decimal = tcase_create("___");
    suite_add_tcase(s1, s21_from_float_to_decimal);
    tcase_add_test(s21_from_float_to_decimal, CV___FROM_FLOAT_TO_DECIMAL);

    TCase *s21_from_decimal_to_int = tcase_create("___");
    suite_add_tcase(s1, s21_from_decimal_to_int);
    tcase_add_test(s21_from_decimal_to_int, CV___FROM_DECIMAL_TO_INT);

    TCase *s21_from_decimal_to_float = tcase_create("___");
    suite_add_tcase(s1, s21_from_decimal_to_float);
    tcase_add_test(s21_from_decimal_to_float, CV___FROM_DECIMAL_TO_FLOAT);

    TCase *s21_is_less = tcase_create("___");
    suite_add_tcase(s1, s21_is_less);
    tcase_add_test(s21_is_less, CM___LESS);

    TCase *s21_is_less_or_equal = tcase_create("___");
    suite_add_tcase(s1, s21_is_less_or_equal);
    tcase_add_test(s21_is_less_or_equal, CM___LESS_OR_EQUAL);

    TCase *s21_is_greater = tcase_create("___");
    suite_add_tcase(s1, s21_is_greater);
    tcase_add_test(s21_is_greater, CM___GREATER);

    TCase *s21_is_greater_or_equal = tcase_create("___");
    suite_add_tcase(s1, s21_is_greater_or_equal);
    tcase_add_test(s21_is_greater_or_equal, CM___GREATER_OR_EQUAL);

    TCase *s21_is_equal = tcase_create("___");
    suite_add_tcase(s1, s21_is_equal);
    tcase_add_test(s21_is_equal, CM___EQUAL);

    TCase *s21_is_not_equal = tcase_create("___");
    suite_add_tcase(s1, s21_is_not_equal);
    tcase_add_test(s21_is_not_equal, CM___NOT_EQUAL);

    TCase *s21_floor = tcase_create("___");
    suite_add_tcase(s1, s21_floor);
    tcase_add_test(s21_floor, R___FLOOR);

    TCase *s21_round = tcase_create("___");
    suite_add_tcase(s1, s21_round);
    tcase_add_test(s21_round, R___ROUND);

    TCase *s21_truncate = tcase_create("___");
    suite_add_tcase(s1, s21_truncate);
    tcase_add_test(s21_truncate, R___TRUNCATE);

    TCase *s21_negate = tcase_create("___");
    suite_add_tcase(s1, s21_negate);
    tcase_add_test(s21_negate, R___NEGATE);

    TCase *s21_add = tcase_create("s21_add");
    suite_add_tcase(s1, s21_add);
    tcase_add_test(s21_add, s21_add_test);

    TCase *s21_sub = tcase_create("s21_sub");
    suite_add_tcase(s1, s21_sub);
    tcase_add_test(s21_sub, s21_sub_test);

    TCase *s21_mul = tcase_create("s21_mul");
    suite_add_tcase(s1, s21_mul);
    tcase_add_test(s21_mul, s21_mul_test);

    TCase *s21_div = tcase_create("s21_div");
    suite_add_tcase(s1, s21_div);
    tcase_add_test(s21_div, s21_div_test);

    TCase *s21_mod = tcase_create("s21_mod");
    suite_add_tcase(s1, s21_mod);
    tcase_add_test(s21_mod, s21_mod_test);

    srunner_run_all(sr, CK_VERBOSE);
    srunner_free(sr);
    return 0;
}
