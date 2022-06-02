#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_cat_lib.h"

int flag_switcher(int argc, char** argv, struct flag_list* flags);
int file_checker_func(int argc, char** argv);
void open_files(char* file_name, struct flag_list flags);

int main(int argc, char** argv) {
    struct flag_list flags = {0};

    int flag_checker = flag_switcher(argc, argv, &flags);
    int file_checker = file_checker_func(argc, argv);

    if (flag_checker == 0) {
        if (file_checker != 0) {
            for (int i = 1; i < argc; i++) {
                if (argv[i][0] != '-') {
                    open_files(argv[i], flags);
                }
            }
        } else {
            printf("ERROR! : NO FILE!\n");
        }
    }
    return 0;
}

int flag_switcher(int argc, char** argv, struct flag_list* flags) {
    int err = 0;
    if (argc < 2) {
        printf("ERROR! : NO FLAGS AND FILES!\n");
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

int file_checker_func(int argc, char** argv) {
    int count = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            count++;
        }
    }
    return count;
}

void open_files(char* file_name, struct flag_list flags) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("ERROR! : NO SUCH FILE!\n");
        fclose(file);
    } else {
        fseek(file, 0, SEEK_END);
        int file_size = ftell(file);
        rewind(file);
        int num_str = 0;

        char* str = malloc(file_size * sizeof(char) + 1);
        if (str != NULL) {
            fread(str, sizeof(char), file_size, file);
        }
        if (str[0] != '\0') {
            num_str++;
        }
        for (int i = 0; i < file_size; i++) {
            if ((flags.n_flag && num_str != 0 &&
                 (str[i - 1] == '\n' || i == 0))) {
                printf("%6d\t", num_str);
            }
            if (str[i] == '\n') {
                num_str++;
            }
            if (flags.e_flag && str[i] == '\n') {
                printf("$\n");
            } else if (flags.t_flag && str[i] == '\t') {
                printf("^I");
            } else {
                printf("%c", str[i]);
            }
        }
        free(str);
        fclose(file);
    }
}
