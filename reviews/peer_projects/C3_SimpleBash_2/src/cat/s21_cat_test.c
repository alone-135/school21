#include "s21_cat_test.h"

int main(void) {
    start_tests();
    return 0;
}

void start_tests() {
    int len = 64;
    char buff[64][32];
    for (int i = 0; i < len; i++) {
        memset(buff[i], '\0', 32);
        if (i >> 0 & 1) strcat(buff[i], s21_mac_flags[0]);
        if (i >> 1 & 1) strcat(buff[i], s21_mac_flags[1]);
        if (i >> 2 & 1) strcat(buff[i], s21_mac_flags[2]);
        if (i >> 3 & 1) strcat(buff[i], s21_mac_flags[3]);
        if (i >> 4 & 1) strcat(buff[i], s21_mac_flags[4]);
        if (i >> 5 & 1) strcat(buff[i], s21_mac_flags[5]);
    }
    for (int i = 0; i < 64; i++) {
        file_gen();
        char command1[512] = {'\0'};
        char command2[512] = {'\0'};
        strcat(command1, "cat");
        strcat(command2, "./s21_cat");
        strcat(command1, buff[i]);
        strcat(command2, buff[i]);
        strcat(command1, "../common/test_1.txt > ../common/test_1_ed.txt");
        strcat(command2, "../common/test_2.txt > ../common/test_2_ed.txt");
        printf("%s\n", command1);
        printf("%s\n", command2);
        system(command1);
        system(command2);
        if (system("diff ../common/test_1_ed.txt ../common/test_2_ed.txt"))
            printf("%sFAIL%s\n", RED, RESET);
        else
            printf("%sOK!%s\n", GRN, RESET);
    }
}

void file_gen(void) {
    int len = rand() % 10000;
    FILE *fd1 = fopen("../common/test_1.txt", "w");
    FILE *fd2 = fopen("../common/test_2.txt", "w");
    if (fd1 && fd2) {
        for (int i = 0; i < len; i++) {
            unsigned char c = rand() % 127;
            fputc(c, fd1);
            fputc(c, fd2);
        }
        fclose(fd1);
        fclose(fd2);
    } else {
        perror("");
    }
}
