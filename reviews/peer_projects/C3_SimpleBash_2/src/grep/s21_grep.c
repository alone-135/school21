#include "s21_grep.h"

int main(int argc, char **argv) {
    if (argc > 2)
        s21_grep(argc, argv);
    else
        printf("Not arguments\n");

    return 0;
}

void init_patterns(TPattern *patterns, int size) {
    for (int i = 0; i < size; i++) {
        patterns[i].is_default = 0;
        patterns[i].is_file = 0;
        patterns[i].file_name = NULL;
        patterns[i].name = NULL;
    }
}

void s21_grep(int argc, char **argv) {
    int kLen = argc;
    TPattern patterns[kLen];
    init_patterns(patterns, argc);
    int pcount = 0;
    TFlags flags = {0};
    set_flags(&flags, patterns, &pcount, argc, argv);
    scan_files(argc, argv, patterns, pcount, flags);
}

void scan_files(int argc, char **argv, TPattern *patterns, int patterns_cnt,
                TFlags flags) {
    int kCount = cnt_files(argc, argv, patterns, flags);
    if (kCount) {
        TFile files[kCount];
        init_files(files, kCount);
        get_files(argc, argv, patterns, files, flags);
        files_processing(patterns, patterns_cnt, files, kCount, flags);
    } else {
        printf("No files found");
    }
}

void set_flags(TFlags *flags, TPattern *patterns, int *patterns_cnt,
                int argc, char **argv) {
    int e = 0, f = 0;
    for (int i = 1; i < argc; i++) {
        if (strspn(argv[i], "-")) {
            get_flags_from_argv(argv[i], flags);
            if (strchr(argv[i], 'f')) {
                f++;
                patterns[*patterns_cnt].is_default = 0;
                patterns[*patterns_cnt].is_file = 1;
                patterns[*patterns_cnt].file_name =
                    get_pattern_file_name(argc, argv, i);
                (*patterns_cnt)++;
            }
            if (strchr(argv[i], 'e')) {
                e++;
                patterns[*patterns_cnt].is_default = 0;
                patterns[*patterns_cnt].is_file = 0;
                patterns[*patterns_cnt].name = get_e_pattern(argc, argv, i);
                (*patterns_cnt)++;
            }
        }
    }
    if (e == 0 && f == 0) {
        patterns[*patterns_cnt].is_file = 0;
        patterns[*patterns_cnt].is_default = 1;
        patterns[*patterns_cnt].name = get_default_pattern(argc, argv);
        (*patterns_cnt)++;
    }
}

int get_flags_from_argv(char *arg, TFlags *flags) {
    int error = 0;
    char *flag;
    if (strlen(arg) == 1 || strlen(arg) != strspn(arg, "-eivclnhsfo")) error = 1;
    char *e = strchr(arg, 'e');
    char *f = strchr(arg, 'f');
    if (!e) e = arg + strlen(arg);
    if (!f) f = arg + strlen(arg);
    if (e < f) {
        flags->f = 1;
        f = e;
    }
    if (f < e) {
        flags->e = 1;
        e = f;
    }
    if ((flag = strchr(arg, 'i')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags->i = 1;
    if ((flag = strchr(arg, 'v')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags->v = 1;
    if ((flag = strchr(arg, 'c')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags->c = 1;
    if ((flag = strchr(arg, 'l')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags->l = 1;
    if ((flag = strchr(arg, 'n')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags->n = 1;
    if ((flag = strchr(arg, 'h')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags->h = 1;
    if ((flag = strchr(arg, 's')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags->s = 1;
    if ((flag = strchr(arg, 'o')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags->o = 1;
    return error;
}

char *get_pattern_file_name(int argc, char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'f') == argv[i] + strlen(argv[i]) - 1) {
        if (i + 1 < argc)
            res = argv[i + 1];
        else
            res = strchr(argv[i], 'f') + 1;
    }
    return res;
}

char *get_e_pattern(int argc, char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'e') == argv[i] + strlen(argv[i]) - 1) {
        if (i + 1 < argc)
            res = argv[i + 1];
        else
            res = strchr(argv[i], 'e') + 1;
    }
    return res;
}

// находит первое вхождение слова без "-" в строке параметров
char *get_default_pattern(int argc, char **argv) {
    char *res = NULL;
    for (int i = 1; i < argc; i++) {
        if (!strspn(argv[i], "-")) {
            res = argv[i];
            break;
        }
    }
    return res;
}

void init_files(TFile *files, int size) {
    for (int i = 0; i < size; i++) {
        files[i].mached = 0;
        files[i].mached_all = 0;
        files[i].valid = 0;
        files[i].file_name = NULL;
    }
}

void get_files(int argc, char **argv, TPattern *patterns, TFile *files,
               TFlags flags) {
    int same = 0;
    int k = 0;
    for (int i = 1; i < argc; i++)
        if (is_arg_a_file(i, argv, patterns, &same, flags))
            files[k++].file_name = argv[i];
}

int is_arg_a_file(int i, char **argv, TPattern *patterns, int *same,
                  TFlags flags) {
    return (!strspn(argv[i], "-") &&
            !((strchr(argv[i], 'f') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'f' &&
               strspn(argv[i - 1], "-")) ||
              (strchr(argv[i], 'e') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'e' &&
               strspn(argv[i - 1], "-")) ||
              (!(flags.f || flags.e) && !strcmp(argv[i], patterns[0].name) &&
               ((*same)--) >= 0)));
}

void files_processing(TPattern *patterns, int patterns_cnt, TFile *files,
                      int files_cnt, TFlags flags) {
    int empty_line = is_empty_line_in_patterns(patterns, patterns_cnt);
    int maching_lines = 0;
    for (int i = 0; i < files_cnt; i++) {
        FILE *fd = fopen(files[i].file_name, "r");
        if (fd) {
            if (empty_line) {
                if (flags.l || flags.c || (flags.e && !flags.v) ||
                    !(flags.v && flags.e)) {
                    maching_lines = print_all(fd, flags, files + i, files_cnt);
                }
            } else {
                maching_lines = seek_in_file(fd, patterns, patterns_cnt, flags,
                                             files + i, files_cnt);
            }
            fclose(fd);
        } else {
            if (!flags.s) printf("No such file or directory\n");
            files[i].valid = 0;
        }
        if (flags.c) print_files_c(files + i, files_cnt, maching_lines, flags);
        if (flags.l) print_files_l(files + i, maching_lines);
    }
}

int is_empty_line_in_patterns(TPattern *patterns, int patterns_cnt) {
    int res = 0;
    for (int i = 0; i < patterns_cnt; i++) {
        if (patterns[i].is_file) {
            char *line = NULL;
            size_t size = 0;
            FILE *fd = fopen(patterns[i].file_name, "r");
            if (fd) {
                while (getline(&line, &size, fd) != -1)
                    if (line && is_empty_line(line)) res = 1;
                fclose(fd);
                free(line);
            }
        } else {
            if (is_empty_line(patterns[i].name)) res = 1;
        }
    }
    return res;
}

int is_empty_line(char *name) {
    return (strlen(name) == 1 && name[0] == '\n');
}

int print_all(FILE *fd, TFlags flags, TFile *file, int files_cnt) {
    char *line = NULL;
    int line_number = 0;
    size_t size = 0;
    while (getline(&line, &size, fd) != -1) {
        if (line) {
            trim_n(line);
            line_number++;
            if (!flags.c && !flags.l) {
                if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
                if (!flags.h && files_cnt > 1) printf("%s:", file->file_name);
                if (flags.n) printf("%d:", line_number);
                printf("%s\n", line);
            }
        }
    }
    free(line);
    return line_number;
}

int seek_in_file(FILE *fd, TPattern *patterns, int patterns_cnt, TFlags flags,
                 TFile *file, int files_cnt) {
    int matching_lines = 0;
    int line_number = 0;
    size_t size = 0;
    char *line = NULL;
    while (getline(&line, &size, fd) != -1) {
        if (line) {
            int one_time_print = 1;
            line_number++;
            trim_n(line);
            for (int i = 0; i < patterns_cnt; i++) {
                int file_name_print = 1;
                seek_choice(line, patterns + i, file, flags, &matching_lines,
                            files_cnt, line_number, &one_time_print,
                            &file_name_print);
            }
            if (flags.v && one_time_print == 1) {
                print_match(line, flags, file, files_cnt, line_number,
                            &one_time_print, &matching_lines);
            }
        }
    }
    free(line);
    return matching_lines;
}

void print_files_c(TFile *file, int files_cnt, int maching_lines,
                   TFlags flags) {
    if (!flags.h && files_cnt > 1) printf("%s:", file->file_name);
    if (!flags.l)
        printf("%d\n", maching_lines);
    else
        printf("%d\n", maching_lines > 0 ? 1 : 0);
}

void print_files_l(TFile *file, int maching_lines) {
    if (maching_lines > 0) printf("%s\n", file->file_name);
}

void trim_n(char *line) {
    if (strlen(line) == 1 && line[0] == '\n') line[0] = '.';
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
}

void seek_choice(char *line, TPattern *pattern, TFile *file, TFlags flags,
                 int *matching_lines, int files_cnt, int line_number,
                 int *one_time_print, int *file_name_print) {
    if (flags.o && !flags.c && !flags.v) {
        if (pattern->is_file) {
            seek_file_patterns(line, pattern, file, flags, matching_lines,
                               files_cnt, line_number, one_time_print,
                               file_name_print);
        } else {
            seek_o_pattern(line, pattern, file, flags, matching_lines,
                           files_cnt, line_number, file_name_print);
        }
    } else {
        if (pattern->is_file) {
            seek_file_patterns(line, pattern, file, flags, matching_lines,
                               files_cnt, line_number, one_time_print,
                               file_name_print);
        } else {
            seek_pattern(line, *pattern, file, flags, matching_lines, files_cnt,
                         line_number, one_time_print);
        }
    }
}

void print_match(char *line, TFlags flags, TFile *file, int files_cnt,
                 int line_number, int *one_time_print, int *maching_lines) {
    if (!flags.c && !flags.l && *one_time_print) {
        if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
        if (!flags.h && files_cnt > 1) printf("%s:", file->file_name);
        if (flags.n) printf("%d:", line_number);
        printf("%s\n", line);
    }
    if (*one_time_print) (*maching_lines)++;
}

void seek_file_patterns(char *line, TPattern *pattern, TFile *file,
                        TFlags flags, int *matching_lines, int files_cnt,
                        int line_number, int *one_time_print,
                        int *file_name_print) {
    FILE *fd = fopen(pattern->file_name, "r");
    if (fd) {
        char *file_line = NULL;
        size_t file_line_size = 0;
        while (getline(&file_line, &file_line_size, fd) != -1) {
            if (line) {
                pattern->name = file_line;
                if (flags.o && !flags.c && !flags.v) {
                    seek_o_pattern(line, pattern, file, flags, matching_lines,
                                   files_cnt, line_number, file_name_print);
                } else {
                    seek_pattern(line, *pattern, file, flags, matching_lines,
                                 files_cnt, line_number, one_time_print);
                }
            }
        }
        free(file_line);
        fclose(fd);
    } else {
        if (!flags.s) printf("No such file or directory\n");
    }
}

void seek_o_pattern(char *line, TPattern *pattern, TFile *file, TFlags flags,
                    int *maching_lines, int files_cnt, int line_number,
                    int *file_name_print) {
    regex_t regex;
    trim_n(pattern->name);
    int comp_val = do_regcomp(&regex, flags, pattern->name);
    if (!comp_val) {
        regmatch_t match;
        size_t offset = 0;
        size_t len = strlen(line);
        int eflags = 0;
        while (regexec(&regex, line + offset, 1, &match, eflags) == 0) {
            if (*file_name_print) (*maching_lines)++;
            eflags = REG_NOTBOL;
            print_o_match(file_name_print, file, offset, match, line, flags,
                          line_number, files_cnt);
            offset += match.rm_eo;
            if (match.rm_so == match.rm_eo) offset += 1;
            if (offset > len) break;
        }
    }
    regfree(&regex);
}

void seek_pattern(char *line, TPattern pattern, TFile *file, TFlags flags,
                  int *matching_lines, int files_cnt, int line_number,
                  int *one_time_print) {
    regex_t regex;
    trim_n(pattern.name);
    int comp_val = do_regcomp(&regex, flags, pattern.name);
    if (!comp_val) {
        int exec_val = regexec(&regex, line, 0, NULL, 0);
        if (exec_val == 0) {
            if (!flags.v) {
                print_match(line, flags, file, files_cnt, line_number,
                            one_time_print, matching_lines);
            }
            *one_time_print = 0;
        }
    } else {
        printf("Regex comp. fail\n");
    }
    regfree(&regex);
}

int do_regcomp(regex_t *regex, TFlags flags, char *pattern) {
    int comp_val;
    if (flags.i)
        comp_val = regcomp(regex, pattern, REG_ICASE);
    else
        comp_val = regcomp(regex, pattern, 0);
    return comp_val;
}

void print_o_match(int *file_name_print, TFile *file, size_t offset,
                   regmatch_t match, char *line, TFlags flags, int line_number,
                   int files_cnt) {
    if (!flags.c && !flags.l) {
        if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
        if (*file_name_print) {
            if (!flags.h && files_cnt > 1) printf("%s:", file->file_name);
            if (flags.n) printf("%d:", line_number);
        }
        for (size_t i = offset + match.rm_so; i < offset + match.rm_eo; i++)
            printf("%c", line[i]);
        printf("\n");
        *file_name_print = 0;
    }
}

int cnt_files(int argc, char **argv, TPattern *patterns, TFlags flags) {
    int res = 0;
    int same = 0;
    for (int i = 1; i < argc; i++)
        if (is_arg_a_file(i, argv, patterns, &same, flags)) res++;
    return res;
}
