#include "s21_cat.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    TFlags flags;
    int checkFlag;
    obnulenie_struct(&flags);

    checkFlag = opredelenie_flags(argc, argv, &flags);

    if (checkFlag != -1) {
        for (int i = 1; i < argc; ++i) {
            if (argv[i][0] != '-') readFile(argv[i], flags);
        }
    }
    return 0;
}

void obnulenie_struct(TFlags* flags) {
    flags->b = 0;
    flags->e = 0;
    flags->n = 0;
    flags->s = 0;
    flags->t = 0;
    flags->v = 0;
}

int opredelenie_flags(int argc, char** argv, TFlags* flags) {
    int error = 0;
    char ill_opt;
    for (int i = 1; (i < argc) && (error != -1); i++) {
        if (argv[i][0] == '-' && argv[i][1] == '-') {
            if (strcmp(argv[i], "--number-nonblank") == 0) {
                flags->b = 1;
            } else if (strcmp(argv[i], "--number") == 0) {
                flags->n = 1;
            } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
                flags->s = 1;
            } else {
                ill_opt = argv[i][1];
                printf(
                    "cat: illegal option -- %c\n"
                    "usage: cat [-benstuv] [file ...]\n",
                    ill_opt);
                error = -1;
            }
        }
        if (argv[i][0] == '-' && argv[i][1] != '-' && error != -1) {
            for (size_t j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'b') {
                    flags->b = 1;
                } else if (argv[i][j] == 'e') {
                    flags->e = 1;
                    flags->v = 1;
                } else if (argv[i][j] == 'n') {
                    flags->n = 1;
                } else if (argv[i][j] == 's') {
                    flags->s = 1;
                } else if (argv[i][j] == 't') {
                    flags->t = 1;
                    flags->v = 1;
                } else if (argv[i][j] == 'v') {
                    flags->v = 1;
                } else if (argv[i][j] == 'T') {
                    flags->t = 1;
                } else if (argv[i][j] == 'E') {
                    flags->e = 1;
                } else if (error != -1) {
                    ill_opt = argv[i][1];
                    printf(
                        "cat: illegal option -- %c\n"
                        "usage: cat [-benstuv] [file ...]\n",
                        ill_opt);
                    error = -1;
                }
            }
        }
    }
    return error;
}
void readFile(char* whatIsfile, TFlags flags) {
    FILE* fp;
    fp = fopen(whatIsfile, "rt");

    if (fp == NULL) {
        printf("cat: %s: No such file or directory", whatIsfile);
    } else {
        int stroka_1 = 0, delete_str = 0;
        int counter = 1;
        char simvol = fgetc(fp);
        stroka_1 = (simvol == '\n') ? 1 : 0;
        int not_printing = 0;
        int enter = 0;
        enter = (stroka_1 == 1) ? 1 : 0;
        while (!feof(fp)) {
            char temp;
            temp = simvol;
            if (flags.b == 1 && (stroka_1 || counter == 1) && simvol != '\n') {
                printf("%6d\t", counter);
                counter++;
            }
            if (flags.n == 1 && flags.b != 1 && (stroka_1 || counter == 1)) {
                if (delete_str != -1) {
                    printf("%6d\t", counter);
                    counter++;
                }
            }
            if (flags.e == 1 && simvol == '\n') {
                if (delete_str != -1) printf("$");
            }
            if (flags.t == 1 && simvol == '\t') {
                printf("^");
                simvol = 'I';
            }
            if (flags.v == 1) {
                int ch = (int)simvol;
                if (simvol < 0) {
                    simvol &= 127;
                    ch = (int)simvol;
                    ch += 128;
                }
                if (ch != 9 && ch != 10 && ch < 32) {
                    printf("^");
                    simvol += 64;
                } else if (ch == 127) {
                    printf("^");
                    simvol = '?';
                } else if (ch > 127 && ch < 160) {
                    printf("M-^");
                    simvol = ch - 64;
                    if (simvol == 'J' && (flags.b || flags.n)) {
                        printf("%c", simvol);
                        printf("%6d\t", counter);
                        counter += 1;
                        not_printing = 1;
                    }
                } else if (ch >= 160 && ch <= 255) {
                    simvol -= 128;
                }
            }

            if (delete_str != -1 && not_printing != 1) {
                printf("%c", simvol);
            }
            stroka_1 = (simvol == '\n') ? 1 : 0;
            simvol = fgetc(fp);
            if (enter == 1 && simvol == '\n' && flags.s == 1) {
                delete_str = -1;
            } else {
                delete_str = 0;
            }
            if (temp == '\n' && simvol == '\n') {
                enter = 1;
            } else {
                enter = 0;
            }
            not_printing = 0;
        }
        fclose(fp);
    }
}
