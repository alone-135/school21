#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flag_list {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int just_find;
    char* template;
    int template_place;
    int file_count;
} flags;

int flag_reader(int argc, char** argv);
int file_name_checker(int argc, char** argv);
int open_file(char* file_name);
int file_size(FILE* file);

void just_find_func(FILE* file, char* file_name);
void e_flag_func(FILE* file, char* file_name);
void i_flag_func(FILE* file, char* file_name);
void v_flag_func(FILE* file, char* file_name);
void c_flag_func(FILE* file, char* file_name);
void l_flag_func(FILE* file, char* file_name);
void n_flag_func(FILE* file, char* file_name);

int eof_check(FILE* file);
int i_flag_helper(char sym, char temp);
char* copying_func(char* data, FILE* file, int* cur_seek);
void free_func(char* data);
int new_line_check(FILE* file);
int same_string_check(char* temp);
void file_name_printer(char* file_name);

int main(int argc, char** argv) {
    if (!flag_reader(argc, argv)) {
        if ((flags.file_count = file_name_checker(argc, argv))) {
            for (int i = 1; i < argc; i++) {
                if (argv[i][0] != '-' && i != flags.template_place) {
                    if (open_file(argv[i]) == 1) {
                        fprintf(stderr, "ERROR! : %s - NO SUCH FILE!\n",
                                argv[i]);
                    }
                }
            }
        } else {
            fprintf(stderr, "ERROR! : NO FILE!\n");
        }
        free(flags.template);
    }
    return 0;
}

int flag_reader(int argc, char** argv) {
    int err = 0;
    if (argc < 3) {
        fprintf(stderr,
                "ERROR! PLEASE ENTER: s21_grep [options] [search string] [file "
                "name]\n");
        err = 1;
    }
    flags.just_find = 1;
    for (int i = 1; i < argc && err == 0; i++) {
        if (argv[i][0] == '-') {
            flags.just_find = 0;
        }
    }
    for (int i = 1; i < argc && err == 0; i++) {
        if (argv[i][0] != '-') {
            int template_size = strlen(argv[i]);
            flags.template = (char*)malloc(template_size * sizeof(char) + 1);
            strcpy(flags.template, argv[i]);
            flags.template_place = i;
            break;
        }
    }
    for (int i = 1; i < argc && err == 0; i++) {
        if (argv[i][0] == '-' && err == 0) {
            for (int j = 1; j < (int)strlen(argv[i]) && err == 0; j++) {
                switch (argv[i][j]) {
                    case 'e':
                        flags.e = 1;
                        break;
                    case 'i':
                        flags.i = 1;
                        break;
                    case 'v':
                        flags.v = 1;
                        break;
                    case 'c':
                        flags.c = 1;
                        break;
                    case 'l':
                        flags.l = 1;
                        break;
                    case 'n':
                        flags.n = 1;
                        break;
                    default:
                        fprintf(stderr, "ERROR! : -%c IS THE WRONG FLAG!\n",
                                argv[i][j]);
                        err = 1;
                        break;
                }
            }
        }
    }
    return err;
}

int file_name_checker(int argc, char** argv) {
    int count = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-' && i != flags.template_place) {
            count++;
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
            if (flags.just_find == 1) {
                just_find_func(file, file_name);
            } else {
                if (flags.e == 1) {
                    e_flag_func(file, file_name);
                }
                if (flags.i == 1) {
                    i_flag_func(file, file_name);
                }
                if (flags.v == 1) {
                    v_flag_func(file, file_name);
                }
                if (flags.c == 1) {
                    c_flag_func(file, file_name);
                }
                if (flags.l == 1) {
                    l_flag_func(file, file_name);
                }
                if (flags.n == 1) {
                    n_flag_func(file, file_name);
                }
            }
        }
        fclose(file);
    }
    return err;
}

int file_size(FILE* file) {
    int size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    return size;
}

//  just_find_func
void just_find_func(FILE* file, char* file_name) {
    int cur_seek = 0;
    while (!feof(file)) {
        char* temp = NULL;
        temp = copying_func(temp, file, &cur_seek);
        if (same_string_check(temp)) {
            file_name_printer(file_name);
            printf("%s", temp);
        }
        free_func(temp);
    }
}

//  e_flag_func
void e_flag_func(FILE* file, char* file_name) {
    int cur_seek = 0;
    while (!eof_check(file)) {
        char* temp = NULL;
        temp = copying_func(temp, file, &cur_seek);
        if (same_string_check(temp)) {
            file_name_printer(file_name);
            printf("%s", temp);
        }
        free_func(temp);
    }
}

//  i_flag_func
void i_flag_func(FILE* file, char* file_name) {
    int cur_seek = 0;
    while (!eof_check(file)) {
        char* temp = NULL;
        temp = copying_func(temp, file, &cur_seek);

        int same = 0;
        for (int i = 0; i < (int)strlen(temp); i++) {
            if (same == (int)strlen(flags.template)) {
                file_name_printer(file_name);
                printf("%s", temp);
                break;
            }
            if (i_flag_helper(temp[i], flags.template[0])) {
                same++;
                for (int j = 1; j < (int)strlen(flags.template); j++) {
                    if (i_flag_helper(temp[j + i], flags.template[j])) {
                        same++;
                    } else {
                        same = 0;
                    }
                }
            }
        }

        free_func(temp);
    }
}

//  v_flag_func
void v_flag_func(FILE* file, char* file_name) {
    int cur_seek = 0;
    while (!eof_check(file)) {
        char* temp = NULL;
        temp = copying_func(temp, file, &cur_seek);
        if (!same_string_check(temp)) {
            file_name_printer(file_name);
            printf("%s", temp);
        }
        free_func(temp);
    }
}

//  c_flag_func
void c_flag_func(FILE* file, char* file_name) {
    int cur_seek = 0;
    int same_count = 0;
    while (!eof_check(file)) {
        char* temp = NULL;
        temp = copying_func(temp, file, &cur_seek);
        if (same_string_check(temp)) {
            same_count++;
        }
        free_func(temp);
    }
    file_name_printer(file_name);
    printf("%d\n", same_count);
}

//  l_flag_func
void l_flag_func(FILE* file, char* file_name) {
    int cur_seek = 0;
    while (!eof_check(file)) {
        char* temp = NULL;
        temp = copying_func(temp, file, &cur_seek);
        if (same_string_check(temp)) {
            printf("%s\n", file_name);
            free_func(temp);
            break;
        }
        free_func(temp);
    }
}

//  n_flag_func
void n_flag_func(FILE* file, char* file_name) {
    int string_count = 0;
    int cur_seek = 0;
    while (!eof_check(file)) {
        char* temp = NULL;
        temp = copying_func(temp, file, &cur_seek);
        string_count++;
        if (same_string_check(temp)) {
            file_name_printer(file_name);
            printf("%d:%s", string_count, temp);
        }
        free_func(temp);
    }
}

int eof_check(FILE* file) {
    int res = 0;
    if (fgetc(file) == EOF) {
        res = 1;
    }
    fseek(file, -1, SEEK_CUR);
    return res;
}

int i_flag_helper(char sym, char temp) {
    int res = 0;
    int int_sym = sym;
    int int_temp = temp;

    if (int_sym == int_temp) {
        res = 1;
    } else if ((int_temp > 65 && int_temp < 90) && int_sym == int_temp + 32) {
        res = 1;
    } else if ((int_temp > 97 && int_temp < 122) && int_sym == int_temp - 32) {
        res = 1;
    }

    return res;
}

char* copying_func(char* data, FILE* file, int* cur_seek) {
    int string_lenght = 2;
    while (fgetc(file) != '\n') {
        string_lenght++;
    }
    fseek(file, *cur_seek, SEEK_SET);
    *cur_seek = *cur_seek + string_lenght - 1;
    data = malloc(string_lenght * sizeof(char));
    fgets(data, string_lenght, file);

    return data;
}

void free_func(char* data) {
    free(data);
    data = NULL;
}

int new_line_check(FILE* file) {
    int res = 0;
    while (fgetc(file) != '\n') {
        res++;
    }
    fseek(file, res, SEEK_CUR);
    res++;

    return res;
}

int same_string_check(char* temp) {
    int same = 0;
    int res = 0;
    for (int i = 0; i < (int)strlen(temp); i++) {
        if (same == (int)strlen(flags.template)) {
            res = 1;
            break;
        }
        if (temp[i] == flags.template[0]) {
            same++;
            for (int j = 1; j < (int)strlen(flags.template); j++) {
                if (temp[i + j] == flags.template[j]) {
                    same++;
                } else {
                    same = 0;
                }
            }
        }
    }
    return res;
}

void file_name_printer(char* file_name) {
    if (flags.file_count > 1) {
        printf("%s:", file_name);
    }
}