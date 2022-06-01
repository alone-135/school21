#include <stdio.h>
#include <string.h>

#include "s21_cat_lib.h"

int flag_switcher(int argc, char** argv, struct flag_list* flags);
void readFile(char* file_name, struct flag_list flags);

int main(int argc, char** argv) {
    // инициализациия и обнуление структуры
    struct flag_list flags = {0};
    // вызов функции проверки и переключения флагов, возврат ошибки функции
    int flag_checker = flag_switcher(argc, argv, &flags);
    // проверка на наличие ошибок в функции проверки флагов
    if (flag_checker == 0) {
        for (int i = 0; i < argc; i++) {
            if (argv[i][0] != '-') {
                readFile(argv[i], flags);
            }
        }
    }

    return 0;
}

int flag_switcher(int argc, char** argv, struct flag_list* flags) {
    int err = 0;
    if (argc < 2) {
        printf("ERROR! : NO FLAGS AND FILES!");
        err = 1;
    } else {
        for (int i = 1; i < argc && err == 0; i++) {
            if (argv[i][0] == '-') {
                if (argv[i][1] != '-' && err == 0) {
                    for (size_t j = 1; j < strlen(argv[i]) && err == 0; j++) {
                        switch (argv[i][j]) {
                            case 'b':
                                flags->b_flag = 1;
                                break;
                            case 'e':
                                flags->e_flag = 1;
                                break;
                            case 's':
                                flags->s_flag = 1;
                                break;
                            case 't':
                                flags->t_flag = 1;
                                break;
                            case 'n':
                                flags->n_flag = 1;
                                break;
                            case 'v':
                                flags->v_flag = 1;
                                break;
                            case 'E':
                                flags->e_flag = 1;
                                break;
                            case 'T':
                                flags->t_flag = 1;
                                break;
                            default:
                                printf("ERROR! : -%c IS THE WRONG FLAG!\n",
                                       argv[i][j]);
                                err = 1;
                        }
                    }
                }
                if (argv[i][1] == '-' && err == 0) {
                    if (strcmp(argv[i], "--number-nonblank") == 0) {
                        flags->b_flag = 1;
                    } else if (strcmp(argv[i], "--number") == 0) {
                        flags->n_flag = 1;
                    } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
                        flags->s_flag = 1;
                    } else {
                        err = 1;
                        printf("ERROR! : %s IS THE WRONG FLAG!\n", argv[i]);
                    }
                }
            }
        }
    }
    return err;
}

void readFile(char* file_name, struct flag_list flags) {
    FILE* file;
    file = fopen(file_name, "r");

    if (file == NULL) {
        printf("cat: %s: No such file or directory", file_name);
    } else {
        int stroka_1 = 0, delete_str = 0;
        int counter = 1;
        char simvol = fgetc(file);
        stroka_1 = (simvol == '\n') ? 1 : 0;
        int not_printing = 0;
        int enter = 0;
        enter = (stroka_1 == 1) ? 1 : 0;
        while (!feof(file)) {
            char temp;
            temp = simvol;
            if (flags.b_flag == 1 && (stroka_1 || counter == 1) &&
                simvol != '\n') {
                printf("%6d\t", counter);
                counter++;
            }
            if (flags.n_flag == 1 && flags.b_flag != 1 &&
                (stroka_1 || counter == 1)) {
                if (delete_str != -1) {
                    printf("%6d\t", counter);
                    counter++;
                }
            }
            if (flags.e_flag == 1 && simvol == '\n') {
                if (delete_str != -1) printf("$");
            }
            if (flags.t_flag == 1 && simvol == '\t') {
                printf("^");
                simvol = 'I';
            }
            if (flags.v_flag == 1) {
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
                    if (simvol == 'J' && (flags.b_flag || flags.n_flag)) {
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
            simvol = fgetc(file);
            if (enter == 1 && simvol == '\n' && flags.s_flag == 1) {
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
        fclose(file);
    }
}
