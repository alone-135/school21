#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void arg_check(int argc, char** argv, int* arg_check_log);
void err(int num);
void just_open(char** argv);
void flags_switcher(char sym);

int main(int argc, char** argv) {
    int arg_check_log[argc + 1];
    arg_check(argc, argv, arg_check_log);

    for (int i = 0; i < argc; i++) {
        printf("%d ", *arg_check_log);
    }

    for (int i = 1; i < argc; i++) {
        if (arg_check_log[i] == 1) {
            for (int j = 1; j < 1024; j++) {
                flags_switcher(argv[i][j]);
            }
        }
    }
    if (argc == 2) {
        just_open(argv);
    } else {
        // for (int i = 0; i < argc; i++) {
        //     printf("%d ", arg_check_log[i]);
        // }
    }

    return 0;
}

void arg_check(int argc, char** argv, int* arg_check_log) {
    if (argc < 2) {
        err(1);
    } else if (argc == 2 && argv[1][0] == 45) {
        err(1);
    }

    for (int i = 0; i < argc + 1; i++) {
        arg_check_log[i] = 0;
    }

    int flag = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == 45 && flag == 0) {
            if (argv[i - 1][0] != 45 && (i - 1 != 0 || i != 1)) {
                flag = 1;
                continue;
            }
            arg_check_log[i] = 1;
            printf("flag %d\n", *arg_check_log);
        } else if (argv[i][0] != 45) {
            arg_check_log[i] = 2;
            printf("file %d\n", *arg_check_log);
        }
    }
    for (int i = 0; i < argc; i++) {
        printf("%d ", *arg_check_log);
    }
    printf("\n");
}

void err(int num) {
    switch (num) {
        case 1:
            printf("\nERROR : FILE NOT SELECTED\n\n");
            exit(1);
            break;
        case 2:
            printf("\nERROR : NO SUCH FILE\n\n");
            break;
        case 3:
            printf("\nERROR : WRONG FLAGS\n\n");
            exit(3);
            break;
    }
}

void just_open(char** argv) {
    FILE* file = fopen(argv[1], "r");
    if (file != NULL) {
        char sym;
        while (1) {
            sym = getc(file);
            if (sym == EOF) {
                break;
            }
            printf("%c", sym);
        }
    } else {
        err(2);
    }
    fclose(file);
}

void flags_switcher(char sym) {
    printf("%c", sym);
    switch (sym) {
        case 'b':
            flags_state.b_flag = 1;
            break;
        case 'e':
            flags_state.e_flag = 1;
            break;
        case 'n':
            flags_state.n_flag = 1;
            break;
        case 's':
            flags_state.s_flag = 1;
            break;
        case 't':
            flags_state.t_flag = 1;
            break;
        default:
            err(3);
    }
}