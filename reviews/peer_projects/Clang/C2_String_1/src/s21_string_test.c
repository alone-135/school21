#include "s21_string.h"

#include <check.h>
#include <stdio.h>
#include <string.h>

char mass1[100] = {'\0'};
char mass2[100] = {'\0'};

void free_array(char *arr1, char *arr2) {
    for (int i = 0; i < 20; i++) {
        arr1[i] = '\0';
        arr2[i] = '\0';
    }
}

START_TEST(test_memchr1) {
    char mass1[100] = "1234", mass2[100] = "Nice", mass3[100] = "00000000",
         mass4[100] = "-1-2-3-4-5", mass5[100] = "daseqweqwe";
    fail_unless(s21_memchr(mass1, '4', 9) == memchr(mass1, '4', 9), "this should falled");
    fail_unless(s21_memchr(mass2, 'i', 9) == memchr(mass2, 'i', 9), "this should falled");
    fail_unless(s21_memchr(mass3, '0', 9) == memchr(mass3, '0', 9), "this should falled");
    fail_unless(s21_memchr(mass4, '-', 9) == memchr(mass4, '-', 9), "this should falled");
    fail_unless(s21_memchr(mass5, '1', 9) == memchr(mass5, '1', 9), "this should falled");
}
END_TEST

START_TEST(test_memcmp2) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "999010s";
    char mass21[100] = "1234", mass22[100] = "776asdqe1",
         mass23[100] = "-1213002%s", mass24[100] = "99901asdass";
    fail_unless(s21_memcmp(mass11, mass21, 4) == memcmp(mass11, mass21, 4), "this should falled");
    fail_unless(s21_memcmp(mass12, mass22, 3) == memcmp(mass12, mass22, 3), "this should falled");
    fail_unless(s21_memcmp(mass13, mass23, 10) == memcmp(mass11, mass21, 10), "this should falled");
    fail_unless(s21_memcmp(mass14, mass24, 4) == memcmp(mass14, mass24, 4), "this should falled");
    fail_unless(s21_memcmp(mass11, mass21, 0) == memcmp(mass11, mass21, 0), "this should falled");
}
END_TEST

START_TEST(test_memcpy3) {
    char mass11[100] = "1234", mass12[100] = "776832768178", mass13[100] = "-1213002%s", mass14[100] = "";
    char mass21[100] = "", mass22[100] = "776asdqe1", mass23[100] = "-1213002%s", mass24[100] = "";
    fail_unless(s21_memcpy(mass11, mass21, 4) == memcpy(mass11, mass21, 4), "this should falled");
    fail_unless(s21_memcpy(mass12, mass22, 4) == memcpy(mass12, mass22, 4), "this should falled");
    fail_unless(s21_memcpy(mass13, mass23, 10) == memcpy(mass13, mass23, 10), "this should falled");
    fail_unless(s21_memcpy(mass14, mass24, 4) == memcpy(mass14, mass24, 4), "this should falled");
    fail_unless(s21_memcpy(mass12, mass23, 0) == memcpy(mass12, mass23, 0), "this should falled");
}
END_TEST

START_TEST(test_memmove4) {
    char mass11[100] = "23", mass12[100] = "776832768178", mass13[100] = "423", mass14[100] = "";
    char mass21[100] = "1234", mass22[100] = "776asdqe1", mass23[100] = "3", mass24[100] = "123";
    fail_unless(s21_memmove(mass11, mass21, 0) == memmove(mass11, mass21, 0), "this should falled");
    fail_unless(s21_memmove(mass12, mass22, 5) == memmove(mass12, mass22, 5), "this should falled");
    fail_unless(s21_memmove(mass13, mass23, 23) == memmove(mass13, mass23, 23), "this should falled");
    fail_unless(s21_memmove(mass13, mass23, 2) == memmove(mass13, mass23, 2), "this should falled");
    fail_unless(s21_memmove(mass14, mass24, 0) == memmove(mass14, mass24, 0), "this should falled");
}
END_TEST

START_TEST(test_memset5) {
    char mass1[100] = "1234", mass2[100] = "Nice",
         mass3[100] = "00000000", mass4[100] = "-1-2-3-4-5", mass5[100] = "daseqweqwe";

    fail_unless(s21_memset(mass1, '4', 3) == memset(mass1, '4', 3), "this should falled");
    fail_unless(s21_memset(mass2, 's', 4) == memset(mass2, 's', 4), "this should falled");
    fail_unless(s21_memset(mass3, '-', 0) == memset(mass3, '-', 0), "this should falled");
    fail_unless(s21_memset(mass4, '0', 23) == memset(mass4, '0', 23), "this should falled");
    fail_unless(s21_memset(mass5, '%', 1) == memset(mass5, '%', 1), "this should falled");
}
END_TEST

START_TEST(test_strcat6) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "", mass15[100];
    char mass21[100] = "", mass22[100] = "776asdqe1",
         mass23[100] = "-1213002%s", mass24[100] = "", mass25[100] = "";
    fail_unless(s21_strcat(mass11, mass21) == strcat(mass11, mass21), "this should falled");
    fail_unless(s21_strcat(mass12, mass22) == strcat(mass12, mass22), "this should falled");
    fail_unless(s21_strcat(mass13, mass23) == strcat(mass13, mass23), "this should falled");
    fail_unless(s21_strcat(mass14, mass24) == strcat(mass14, mass24), "this should falled");
    fail_unless(s21_strcat(mass15, mass25) == strcat(mass15, mass25), "this should falled");
}
END_TEST

START_TEST(test_strncat7) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "", mass15[100] = "123";
    char mass21[100] = "", mass22[100] = "776asdqe1",
         mass23[100] = "-1213002%s", mass24[100] = "", mass25[100] = "456";
    fail_unless(s21_strncat(mass11, mass21, 2) == strncat(mass11, mass21, 2), "this should falled");
    fail_unless(s21_strncat(mass12, mass22, 30) == strncat(mass12, mass22, 30), "this should falled");
    fail_unless(s21_strncat(mass13, mass23, 0) == strncat(mass13, mass23, 0), "this should falled");
    fail_unless(s21_strncat(mass14, mass24, 2) == strncat(mass14, mass24, 2), "this should falled");
    fail_unless(s21_strncat(mass15, mass25, 3) == strncat(mass15, mass25, 3), "this should falled");
}
END_TEST

START_TEST(test_strchr8) {
    char mass1[100] = "1234", mass2[100] = "Nice",
         mass3[100] = "00000000", mass4[100] = "-1-2-3-4-5", mass5[100] = "";
    fail_unless(s21_strchr(mass1, '0') == strchr(mass1, '0'), "this should falled");
    fail_unless(s21_strchr(mass2, 'i') == strchr(mass2, 'i'), "this should falled");
    fail_unless(s21_strchr(mass3, '0') == strchr(mass3, '0'), "this should falled");
    fail_unless(s21_strchr(mass4, '-') == strchr(mass4, '-'), "this should falled");
    fail_unless(s21_strchr(mass5, '1') == strchr(mass5, '1'), "this should falled");
}
END_TEST

START_TEST(test_strcmp9) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "999010s";
    char mass21[100] = "1234", mass22[100] = "776asdqe1",
         mass23[100] = "-1213002%s", mass24[100] = "99901asdass";
    fail_unless(s21_strcmp(mass11, mass21) == strcmp(mass11, mass21), "this should falled");
    fail_unless(s21_strcmp(mass12, mass22) == strcmp(mass12, mass22), "this should falled");
    fail_unless(s21_strcmp(mass13, mass23) == strcmp(mass11, mass21), "this should falled");
    fail_unless(s21_strcmp(mass14, mass24) == strcmp(mass14, mass24), "this should falled");
    fail_unless(s21_strcmp(mass11, mass21) == strcmp(mass11, mass21), "this should falled");
}
END_TEST

START_TEST(test_strncmp10) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "999010s";
    char mass21[100] = "1234", mass22[100] = "776asdqe1",
         mass23[100] = "-1213002%s", mass24[100] = "99901asdass";
    fail_unless(s21_strncmp(mass11, mass21, 4) == strncmp(mass11, mass21, 4), "this should falled");
    fail_unless(s21_strncmp(mass12, mass22, 3) == strncmp(mass12, mass22, 3), "this should falled");
    fail_unless(s21_strncmp(mass13, mass23, 100) == strncmp(mass11, mass21, 100), "this should falled");
    fail_unless(s21_strncmp(mass14, mass24, 4) == strncmp(mass14, mass24, 4), "this should falled");
    fail_unless(s21_strncmp(mass11, mass21, 0) == strncmp(mass11, mass21, 0), "this should falled");
}
END_TEST

START_TEST(test_strcpy11) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "";
    char mass21[100] = "", mass22[100] = "776asdqe1",
         mass23[100] = "-1213002%s", mass24[100] = "";
    fail_unless(s21_strcpy(mass11, mass21) == strcpy(mass11, mass21), "this should falled");
    fail_unless(s21_strcpy(mass12, mass22) == strcpy(mass12, mass22), "this should falled");
    fail_unless(s21_strcpy(mass13, mass23) == strcpy(mass13, mass23), "this should falled");
    fail_unless(s21_strcpy(mass14, mass24) == strcpy(mass14, mass24), "this should falled");
    fail_unless(s21_strcpy(mass12, mass23) == strcpy(mass12, mass23), "this should falled");
}
END_TEST

START_TEST(test_strncpy12) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "";
    char mass21[100] = "", mass22[100] = "776asdqe1",
         mass23[100] = "-1213002%s", mass24[100] = "";
    fail_unless(s21_strncpy(mass11, mass21, 4) == strncpy(mass11, mass21, 4), "this should falled");
    fail_unless(s21_strncpy(mass12, mass22, 4) == strncpy(mass12, mass22, 4), "this should falled");
    fail_unless(s21_strncpy(mass13, mass23, 10) == strncpy(mass13, mass23, 10), "this should falled");
    fail_unless(s21_strncpy(mass14, mass24, 4) == strncpy(mass14, mass24, 4), "this should falled");
    fail_unless(s21_strncpy(mass12, mass23, 0) == strncpy(mass12, mass23, 0), "this should falled");
}
END_TEST

START_TEST(test_strcspn13) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "";
    char mass21[100] = "", mass22[100] = "776",
         mass23[100] = "-1213002%s", mass24[100] = "1234";
    fail_unless(s21_strcspn(mass11, mass21) == strcspn(mass11, mass21), "this should falled first test");
    fail_unless(s21_strcspn(mass12, mass22) == strcspn(mass12, mass22), "this should falled second test");
    fail_unless(s21_strcspn(mass13, mass23) == strcspn(mass13, mass23), "this should falled");
    fail_unless(s21_strcspn(mass14, mass24) == strcspn(mass14, mass24), "this should falled");
    fail_unless(s21_strcspn(mass12, mass23) == strcspn(mass12, mass23), "this should falled");
}
END_TEST

START_TEST(test_strerror14) {
    char *str1 = s21_strerror(0);
    char *str5 = strerror(0);
    ck_assert_str_eq(str1, str5);

    char *str6 = strerror(101);
    char *str2 = s21_strerror(101);
    ck_assert_str_eq(str2, str6);

    char *str3 = s21_strerror(200);
    char *str7 = strerror(200);
    ck_assert_str_eq(str3, str7);

    char *str4 = s21_strerror(-15);
    char *str8 = strerror(-15);
    ck_assert_str_eq(str4, str8);
}
END_TEST

START_TEST(test_strlen15) {
    char mass1[100] = "1234", mass2[100] = "Nice",
         mass3[100] = "00000000", mass4[100] = "-1-2-3-4-5", mass5[100] = "";
    fail_unless(s21_strlen(mass1) == strlen(mass1), "this should falled");
    fail_unless(s21_strlen(mass2) == strlen(mass2), "this should falled");
    fail_unless(s21_strlen(mass3) == strlen(mass3), "this should falled");
    fail_unless(s21_strlen(mass4) == strlen(mass4), "this should falled");
    fail_unless(s21_strlen(mass5) == strlen(mass5), "this should falled");
}
END_TEST

START_TEST(test_strpbrk16) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "";
    char mass21[100] = "", mass22[100] = "776",
         mass23[100] = "-1213002%s", mass24[100] = "";
    fail_unless(s21_strpbrk(mass11, mass21) == strpbrk(mass11, mass21), "this should falled first test");
    fail_unless(s21_strpbrk(mass12, mass22) == strpbrk(mass12, mass22), "this should falled second test");
    fail_unless(s21_strpbrk(mass13, mass23) == strpbrk(mass13, mass23), "this should falled");
    fail_unless(s21_strpbrk(mass14, mass24) == strpbrk(mass14, mass24), "this should falled");
    fail_unless(s21_strpbrk(mass12, mass23) == strpbrk(mass12, mass23), "this should falled");
}
END_TEST

START_TEST(test_strrchr17) {
    char mass1[100] = "1234", mass2[100] = "Nice",
         mass3[100] = "00000000", mass4[100] = "-1-2-3-4-5", mass5[100] = "";
    fail_unless(s21_strrchr(mass1, '0') == strrchr(mass1, '0'), "this should falled");
    fail_unless(s21_strrchr(mass2, 'i') == strrchr(mass2, 'i'), "this should falled");
    fail_unless(s21_strrchr(mass3, '0') == strrchr(mass3, '0'), "this should falled");
    fail_unless(s21_strrchr(mass4, '-') == strrchr(mass4, '-'), "this should falled");
    fail_unless(s21_strrchr(mass5, '1') == strrchr(mass5, '1'), "this should falled");
}
END_TEST

START_TEST(test_strspn18) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "";
    char mass21[100] = "", mass22[100] = "776",
         mass23[100] = "-1213002%s", mass24[100] = "1234";
    fail_unless(s21_strspn(mass11, mass21) == strspn(mass11, mass21), "this should falled first test");
    fail_unless(s21_strspn(mass12, mass22) == strspn(mass12, mass22), "this should falled second test");
    fail_unless(s21_strspn(mass13, mass23) == strspn(mass13, mass23), "this should falled");
    fail_unless(s21_strspn(mass14, mass24) == strspn(mass14, mass24), "this should falled");
    fail_unless(s21_strspn(mass12, mass23) == strspn(mass12, mass23), "this should falled");
}
END_TEST

START_TEST(test_strstr19) {
    char mass11[100] = "1234", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "";
    char mass21[100] = "", mass22[100] = "776",
         mass23[100] = "-1213002%s", mass24[100] = "1234";
    fail_unless(s21_strstr(mass11, mass21) == strstr(mass11, mass21), "this should falled first test");
    fail_unless(s21_strstr(mass12, mass22) == strstr(mass12, mass22), "this should falled second test");
    fail_unless(s21_strstr(mass13, mass23) == strstr(mass13, mass23), "this should falled");
    fail_unless(s21_strstr(mass14, mass24) == strstr(mass14, mass24), "this should falled");
    fail_unless(s21_strstr(mass12, mass23) == strstr(mass12, mass23), "this should falled");
}
END_TEST

START_TEST(test_strtok20) {
    char mass11[100] = "1/2/3/4", mass12[100] = "776832768178",
         mass13[100] = "-1213002%s", mass14[100] = "";
    char mass21[100] = "/", mass22[100] = "",
         mass23[100] = "-1213002%s", mass24[100] = "1234";
    fail_unless(s21_strtok(mass11, mass21) == strtok(mass11, mass21), "this should falled first test");
    fail_unless(s21_strtok(mass12, mass22) == strtok(mass12, mass22), "this should falled second test");
    fail_unless(s21_strtok(mass13, mass23) == strtok(mass13, mass23), "this should falled");
    fail_unless(s21_strtok(mass14, mass24) == strtok(mass14, mass24), "this should falled");
    fail_unless(s21_strtok(mass12, mass23) == strtok(mass12, mass23), "this should falled");
}
END_TEST

START_TEST(sprintfTest_s_string) {
    s21_sprintf(mass2, "% #", "Hello");

    sprintf(mass1, "%s", "Hello");
    s21_sprintf(mass2, "%s", "Hello");
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%.1s", "Hello");
    s21_sprintf(mass2, "%.1s", "Hello");
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%7s", "Hello");
    s21_sprintf(mass2, "%7s", "Hello");
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%-10s", "Hello");
    s21_sprintf(mass2, "%-10s", "Hello");
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(sprintfTest_c_string) {
    sprintf(mass1, "%1c %c", 'H', 'z');
    s21_sprintf(mass2, "%1c %c", 'H', 'z');
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%10c %2c", 'H', 'z');
    s21_sprintf(mass2, "%10c %2c", 'H', 'z');
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%-1c %-c", 'H', 'z');
    s21_sprintf(mass2, "%-1c %-c", 'H', 'z');
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(sprintfTest_f_string) {
    sprintf(mass1, "%f", 100000.4);
    s21_sprintf(mass2, "%f", 100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%0f", 100000.4);
    s21_sprintf(mass2, "%0f", 100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%f", -100000.4);
    s21_sprintf(mass2, "%f", -100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%+f %+f", -100000.4, 1000.231);
    s21_sprintf(mass2, "%+f %+f", -100000.4, 1000.231);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%-20f", 100000.4);
    s21_sprintf(mass2, "%-20f", 100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%-+20f", 100000.4);
    s21_sprintf(mass2, "%-+20f", 100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%-20f", -100000.4);
    s21_sprintf(mass2, "%-20f", -100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%+20f", 100000.4);
    s21_sprintf(mass2, "%+20f", 100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%+20f", -100000.4);
    s21_sprintf(mass2, "%+20f", -100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
    float key = 10000;
    sprintf(mass1, "%+20f", key);
    s21_sprintf(mass2, "%+20f", key);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(sprintfTest_d_string) {
    sprintf(mass1, "%d%%\n", 4);
    s21_sprintf(mass2, "%d%%\n", 4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%.10d%%\n", 4);
    s21_sprintf(mass2, "%.10d%%\n", 4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%0d%%\n", -4);
    s21_sprintf(mass2, "%0d%%\n", -4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%-+10d%%\n", 4);
    s21_sprintf(mass2, "%-+10d%%\n", 4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%-10d%%\n", -4);
    s21_sprintf(mass2, "%-10d%%\n", -4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%+10d%%\n", 4);
    s21_sprintf(mass2, "%+10d%%\n", 4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%+10d%%\n", -4);
    s21_sprintf(mass2, "%+10d%%\n", -4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%+10.5d%%\n", -4);
    s21_sprintf(mass2, "%+10.5d%%\n", -4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    long int var_long = 100;
    sprintf(mass1, "%ld%%\n", var_long);
    s21_sprintf(mass2, "%ld%%\n", var_long);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    short var_short = 123;
    sprintf(mass1, "%hd%%\n", var_short);
    s21_sprintf(mass2, "%hd%%\n", var_short);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(sprintfTest_u_string) {
    sprintf(mass1, "%02.5u%%\n", 4);
    s21_sprintf(mass2, "%02.5u%%\n", 4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%2.5u%%\n", -4);
    s21_sprintf(mass2, "%2.5u%%\n", -4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%10.5u%%\n", 4);
    s21_sprintf(mass2, "%10.5u%%\n", 4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    sprintf(mass1, "%-10u%%\n", 421);
    s21_sprintf(mass2, "%-10u%%\n", 421);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    short unsigned key_h = 421;
    sprintf(mass1, "%-10hu%%\n", key_h);
    s21_sprintf(mass2, "%-10hu%%\n", key_h);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);

    long unsigned key_l = 421;
    sprintf(mass1, "%-10lu%%\n", key_l);
    s21_sprintf(mass2, "%-10lu%%\n", key_l);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(to_upper) {
    char *mass1 = s21_to_upper("hello");
    char *mass2 = "HELLO";
    ck_assert_str_eq(mass1, mass2);
    free(mass1);

    char *mass3 = s21_to_upper("NOSOK");
    char *mass4 = "NOSOK";
    ck_assert_str_eq(mass3, mass4);
    free(mass3);

    char *mass5 = s21_to_upper("");
    char *mass6 = "";
    ck_assert_str_eq(mass5, mass6);
    free(mass5);

    char *mass7 = s21_to_upper("RasSoL");
    char *mass8 = "RASSOL";
    ck_assert_str_eq(mass7, mass8);
    free(mass7);

    char *mass9 = s21_to_upper("RasSoL12Upper");
    char *mass10 = "RASSOL12UPPER";
    ck_assert_str_eq(mass9, mass10);
    free(mass9);
}
END_TEST

START_TEST(to_lower) {
    char *mass1 = s21_to_lower("HELLO");
    char *mass2 = "hello";
    ck_assert_str_eq(mass1, mass2);
    free(mass1);

    char *mass3 = s21_to_lower("nosok");
    char *mass4 = "nosok";
    ck_assert_str_eq(mass3, mass4);
    free(mass3);

    char *mass5 = s21_to_lower("");
    char *mass6 = "";
    ck_assert_str_eq(mass5, mass6);
    free(mass5);

    char *mass7 = s21_to_lower("RasSoL");
    char *mass8 = "rassol";
    ck_assert_str_eq(mass7, mass8);
    free(mass7);

    char *mass9 = s21_to_lower("RasSoL12Upper");
    char *mass10 = "rassol12upper";
    ck_assert_str_eq(mass9, mass10);
    free(mass9);
}
END_TEST

START_TEST(insert) {
    char *mass1 = s21_insert("HELLO", "new", 2);
    char *mass2 = "HEnewLLO";
    ck_assert_str_eq(mass1, mass2);
    free(mass1);

    char *mass3 = s21_insert("nosok", "kot", 3);
    char *mass4 = "noskotok";
    ck_assert_str_eq(mass3, mass4);
    free(mass3);

    char *mass5 = s21_insert("", "new", 5);
    char *mass6 = NULL;
    fail_unless(mass5 == mass6);
    free(mass5);

    char *mass7 = s21_insert("1", "new", 1);
    char *mass8 = "1new";
    ck_assert_str_eq(mass7, mass8);
    free(mass7);

    char *mass9 = s21_insert("1", "new", 0);
    char *mass10 = "new1";
    ck_assert_str_eq(mass9, mass10);
    free(mass9);
}
END_TEST

START_TEST(trim) {
    char *mass1 = s21_trim("hello", "h");
    char *mass2 = "ello";
    ck_assert_str_eq(mass1, mass2);
    free(mass1);

    char *mass3 = s21_trim("nosok", "sok");
    char *mass4 = "n";
    ck_assert_str_eq(mass3, mass4);
    free(mass3);

    char *mass5 = s21_trim("", "123");
    char *mass6 = "";
    ck_assert_str_eq(mass5, mass6);
    free(mass5);

    char *mass7 = s21_trim("1", "new");
    char *mass8 = "1";
    ck_assert_str_eq(mass7, mass8);
    free(mass7);

    char *mass9 = s21_trim("1234", "14");
    char *mass10 = "23";
    ck_assert_str_eq(mass9, mass10);
    free(mass9);
}
END_TEST

int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_memchr1);
    tcase_add_test(tc1_1, test_memcmp2);
    tcase_add_test(tc1_1, test_memcpy3);
    tcase_add_test(tc1_1, test_memmove4);
    tcase_add_test(tc1_1, test_memset5);
    tcase_add_test(tc1_1, test_strcat6);
    tcase_add_test(tc1_1, test_strncat7);
    tcase_add_test(tc1_1, test_strchr8);
    tcase_add_test(tc1_1, test_strcmp9);
    tcase_add_test(tc1_1, test_strncmp10);
    tcase_add_test(tc1_1, test_strcpy11);
    tcase_add_test(tc1_1, test_strncpy12);
    tcase_add_test(tc1_1, test_strcspn13);
    tcase_add_test(tc1_1, test_strerror14);
    tcase_add_test(tc1_1, test_strlen15);
    tcase_add_test(tc1_1, test_strpbrk16);
    tcase_add_test(tc1_1, test_strrchr17);
    tcase_add_test(tc1_1, test_strspn18);
    tcase_add_test(tc1_1, test_strstr19);
    tcase_add_test(tc1_1, test_strtok20);

    tcase_add_test(tc1_1, sprintfTest_s_string);
    tcase_add_test(tc1_1, sprintfTest_c_string);
    tcase_add_test(tc1_1, sprintfTest_f_string);
    tcase_add_test(tc1_1, sprintfTest_d_string);
    tcase_add_test(tc1_1, sprintfTest_u_string);

    tcase_add_test(tc1_1, to_upper);
    tcase_add_test(tc1_1, to_lower);
    tcase_add_test(tc1_1, insert);
    tcase_add_test(tc1_1, trim);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
