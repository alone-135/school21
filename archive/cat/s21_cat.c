#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flag_list {
    int b_flag;
    int e_flag;
    int n_flag;
    int s_flag;
    int t_flag;
    int v_flag;
    int T_flag;
    int E_flag;
} flags;

int flags_reader(int argc, char** argv);
int file_name_checker(int argc, char** argv);
int open_file(char* file_name);
int just_open();
void flag_handler(FILE* file);
int file_size(FILE* file);

int main(int argc, char** argv) {
    if (argc > 1) {
        if (!flags_reader(argc, argv)) {
            if (file_name_checker(argc, argv)) {
                for (int i = 1; i < argc; i++) {
                    if (argv[i][0] != '-') {
                        if (open_file(argv[i])) {
                            fprintf(stderr, "ERROR! : %s - NO SUCH FILE!\n",
                                    argv[i]);
                        }
                    }
                }
            } else {
                fprintf(stderr, "ERROR! : NO FILE!\n");
            }
        }
    } else {
        fprintf(stderr, "ERROR! : NO FLAGS AND FILES!\n");
    }
    return 0;
}

int flags_reader(int argc, char** argv) {
    int err = 0;
    if (argc < 2) {
        err = 1;
    } else {
        for (int i = 1; i < argc && err == 0; i++) {
            if (argv[i][0] == '-') {
                if (argv[i][1] != '-' && err == 0) {
                    for (size_t j = 1; j < strlen(argv[i]) && err == 0; j++) {
                        switch (argv[i][j]) {
                            case 'b':
                                flags.b_flag = 1;
                                if (flags.n_flag == 1) {
                                    flags.n_flag = 0;
                                }
                                break;
                            case 'e':
                                flags.e_flag = 1;
                                flags.v_flag = 1;
                                break;
                            case 's':
                                flags.s_flag = 1;
                                break;
                            case 't':
                                flags.t_flag = 1;
                                flags.v_flag = 1;
                                break;
                            case 'n':
                                if (flags.b_flag != 1) {
                                    flags.n_flag = 1;
                                }
                                break;
                            case 'v':
                                if (flags.E_flag != 1 && flags.T_flag != 0) {
                                    flags.v_flag = 1;
                                }
                                break;
                            case 'E':
                                flags.E_flag = 1;
                                flags.e_flag = 1;
                                flags.v_flag = 0;
                                break;
                            case 'T':
                                flags.T_flag = 1;
                                flags.t_flag = 1;
                                flags.v_flag = 0;
                                break;
                            default:
                                fprintf(stderr,
                                        "ERROR! : -%c IS THE WRONG FLAG!\n",
                                        argv[i][j]);
                                err = 1;
                        }
                    }
                }
                if (argv[i][1] == '-' && err == 0) {
                    if (strcmp(argv[i], "--number-nonblank") == 0) {
                        flags.b_flag = 1;
                    } else if (strcmp(argv[i], "--number") == 0) {
                        flags.n_flag = 1;
                    } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
                        flags.s_flag = 1;
                    } else {
                        err = 1;
                        fprintf(stderr, "ERROR! : %s IS THE WRONG FLAG!\n",
                                argv[i]);
                    }
                }
            }
        }
    }
    return err;
}

int file_name_checker(int argc, char** argv) {
    int count = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            count++;
            break;
        }
    }
    return count;
}

int open_file(char* file_name) {
    int err = 0;
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        err = 1;
    } else {
        if (file_size(file) > 0) {
            if (just_open(flags)) {
                int size = file_size(file);
                for (int i = 0; i < size; i++) {
                    printf("%c", fgetc(file));
                }
            } else {
                flag_handler(file);
            }
        }
        fclose(file);
    }
    return err;
}

int just_open() {
    int just;
    if (flags.b_flag == 0 && flags.e_flag == 0 && flags.s_flag == 0 &&
        flags.t_flag == 0 && flags.n_flag == 0 && flags.v_flag == 0) {
        just = 1;
    } else {
        just = 0;
    }
    return just;
}

int file_size(FILE* file) {
    int size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    return size;
}

void flag_handler(FILE* file) {
    int new_line_counter = 0;
    int line_counter = 1;
    int flag;
    int file_counter = 0;

    char first_sym = fgetc(file);
    rewind(file);

    int size = file_size(file);

    for (int i = 0; i < size; i++) {
        char sym = fgetc(file);
        int temp = sym;
        if (temp == EOF) {
            break;
        }

        if (flags.v_flag) {
            if (temp < 32 && temp != 10 && temp != 9) {
                putchar('^');
                sym += 64;
            } else if (temp == 127) {
                putchar('^');
                sym = '?';
            }
        }

        file_counter++;

        if ((flags.n_flag && new_line_counter > 0 && flag != 1) ||
            (flags.n_flag && line_counter == 1)) {
            printf("%6d\t", line_counter);
            line_counter++;
        }

        if ((flags.b_flag && sym != '\n' && new_line_counter > 0) ||
            (flags.b_flag && line_counter == 1 && sym != '\n')) {
            printf("%6d\t", line_counter);
            line_counter++;
        }

        if (sym == '\n') {
            new_line_counter++;
        } else {
            new_line_counter = 0;
            flag = 0;
        }

        if (flags.s_flag == 1 && first_sym == '\n' && sym == '\n') {
            while (first_sym == '\n') {
                first_sym = fgetc(file);
            }
            fseek(file, -1, SEEK_CUR);
        }

        if (flags.s_flag && new_line_counter > 2) {
            flag = 1;
            new_line_counter--;
            continue;
        }

        if (flags.e_flag && sym == '\n') {
            putchar('$');
        }

        if (flags.t_flag && sym == '\t') {
            putchar('^');
            putchar('I');
        } else {
            putchar(sym);
        }
    }
}
