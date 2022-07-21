#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
} TFlags;

typedef struct s21_pattern {
    char *name;
    int is_file;
    char *file_name;
    int is_default;
} TPattern;

typedef struct s21_file {
    char *file_name;
    int mached;
    int mached_all;
    int valid;
} TFile;

void s21_grep(int argc, char **argv);
void init_patterns(TPattern *patterns, int size);
void set_flags(TFlags *flags, TPattern *patterns, int *patterns_cnt,
                int argc, char **argv);
int get_flags_from_argv(char *arg, TFlags *flags);
char *get_pattern_file_name(int argc, char **argv, int i);
char *get_e_pattern(int argc, char **argv, int i);
char *get_default_pattern(int argc, char **argv);
void scan_files(int argc, char **argv, TPattern *patterns, int patterns_cnt,
                TFlags flags);
void init_files(TFile *files, int size);
void get_files(int argc, char **argv, TPattern *patterns, TFile *files,
               TFlags flags);
void files_processing(TPattern *patterns, int patterns_cnt, TFile *files,
                      int files_cnt, TFlags flags);
int is_empty_line_in_patterns(TPattern *patterns, int patterns_cnt);
int print_all(FILE *fd, TFlags flags, TFile *file, int files_cnt);
int is_arg_a_file(int i, char **argv, TPattern *patterns, int *same,
                  TFlags flags);
int seek_in_file(FILE *fd, TPattern *patterns, int patterns_cnt, TFlags flags,
                 TFile *file, int files_cnt);
void print_files_c(TFile *file, int files_cnt, int maching_lines,
                   TFlags flags);
void print_files_l(TFile *file, int maching_lines);
int is_empty_line(char *name);
void seek_o_pattern(char *line, TPattern *pattern, TFile *file, TFlags flags,
                    int *maching_lines, int files_cnt, int line_number,
                    int *file_name_print);
void seek_pattern(char *line, TPattern pattern, TFile *file, TFlags flags,
                  int *matching_lines, int files_cnt, int line_number,
                  int *one_time_print);
void seek_choice(char *line, TPattern *pattern, TFile *file, TFlags flags,
                 int *matching_lines, int files_cnt, int line_number,
                 int *one_time_print, int *file_name_print);
void print_match(char *line, TFlags flags, TFile *file, int files_cnt,
                 int line_number, int *one_time_print, int *maching_lines);
void seek_file_patterns(char *line, TPattern *pattern, TFile *file,
                        TFlags flags, int *matching_lines, int files_cnt,
                        int line_number, int *one_time_print,
                        int *file_name_print);
void trim_n(char *line);
int do_regcomp(regex_t *regex, TFlags flags, char *pattern);
int cnt_files(int argc, char **argv, TPattern *patterns, TFlags flags);
void print_o_match(int *file_name_print, TFile *file, size_t offset,
                   regmatch_t match, char *line, TFlags flags, int line_number,
                   int files_cnt);


#endif  // SRC_GREP_S21_GREP_H_
