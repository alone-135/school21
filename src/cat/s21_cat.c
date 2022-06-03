#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_cat_lib.h"

int flag_checker_func(int argc, char** argv, struct flag_list* flags);
int file_checker_func(int argc, char** argv);
void open_files(char* file_name, struct flag_list flags);
int empty_file_checker(FILE* file);
char* get_file_content(FILE* file);
int just_open(struct flag_list flags);
void print_str(char* str);
char* flag_handler(char* str, struct flag_list flags);

void b_func(char* str);
char* e_func(char* str);
char* s_func(char* str);
char* t_func(char* str);
void n_func(char* str);

int main(int argc, char** argv) {
    struct flag_list flags = {0};

    int flag_checker = flag_checker_func(argc, argv, &flags);
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

int flag_checker_func(int argc, char** argv, struct flag_list* flags) {
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
                                flags->n_flag = 0;
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
                                if (flags->b_flag != 1) {
                                    flags->n_flag = 1;
                                }
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
        printf("ERROR! : %s - NO SUCH FILE!\n", file_name);
    } else {
        if (!empty_file_checker(file)) {
            char* str = get_file_content(file);
            if (just_open(flags)) {
                print_str(str);
            } else {
                str = flag_handler(str, flags);
                print_str(str);
                free(str);
            }
        }
    }
    fclose(file);
}

void b_func(char* str) { printf("b_flag %c\n", str[0]); }

char* e_func(char* str) {
    int length = strlen(str);
    int newline_count = 0;
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] == '\n') {
            newline_count++;
        }
    }
    char* temp = calloc(newline_count * 2, sizeof(char));
    length = length + (newline_count * 2);
    for (int i = 0; i < length; i++) {
        if (str[i] == '\n') {
            temp[j] = '$';
            temp[j + 1] = '\n';
            j += 2;
        } else {
            temp[j] = str[i];
            j++;
        }
    }

    free(str);
    str = NULL;

    return temp;
}

char* s_func(char* str) {
    int length = strlen(str);
    char* temp = calloc(length + 1, sizeof(char));
    // int new_line_count = 0;

    for (int i = 0; i < length; i++) {
        temp[i] = str[i];
    }

    free(str);
    str = NULL;

    return temp;
}

char* t_func(char* str) {
    int length = strlen(str);
    int tab_count = 0;
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] == '\t') {
            tab_count++;
        }
    }
    char* temp = calloc(tab_count * 2, sizeof(char));
    length = length + (tab_count * 2);
    for (int i = 0; i < length; i++) {
        if (str[i] == '\t') {
            temp[j] = '^';
            temp[j + 1] = 'I';
            j += 2;
        } else {
            temp[j] = str[i];
            j++;
        }
    }

    free(str);
    str = NULL;

    return temp;
}

void n_func(char* str) { printf("n_flag %c\n", str[0]); }

char* flag_handler(char* str, struct flag_list flags) {
    // if (flags.b_flag) {
    //     b_func(str);
    // }

    if (flags.s_flag) {
        str = s_func(str);
    }
    if (flags.t_flag) {
        str = t_func(str);
    }
    if (flags.e_flag) {
        str = e_func(str);
    }
    // if (flags.n_flag) {
    //     n_func(str);
    // }

    return str;
}

char* get_file_content(FILE* file) {
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    rewind(file);

    char* str = malloc(file_size * sizeof(char) + 1);
    if (str != NULL) {
        fread(str, sizeof(char), file_size, file);
    }
    return str;
}

int just_open(struct flag_list flags) {
    int just;

    if (flags.b_flag == 0 && flags.e_flag == 0 && flags.s_flag == 0 &&
        flags.t_flag == 0 && flags.n_flag == 0) {
        just = 1;
    } else {
        just = 0;
    }

    return just;
}

int empty_file_checker(FILE* file) {
    int empty;

    if (fgetc(file) == EOF) {
        empty = 1;
    } else {
        empty = 0;
    }

    return empty;
}

void print_str(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        printf("%c", str[length]);
        length++;
    }
}
