#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct words_list {
    char eng[30];
    char rus[30];
};

void initialize(struct words_list words[]);
int input(char *inp);

int main() {
    srand(time(NULL));
    printf("\n!!!!!  START  !!!!!\n\n");
    int No = 0;
    char inp[100] = {0};

    struct words_list words[2] = {0};

    initialize(words);

    for (int i = 0; i < 5; i++) {
        No = rand() % 2 + 1;
        printf("\n\t%s\n\n", words[No].rus);
        int size = input(inp);
        for (int j = 0; j < size; j++) {
            if (inp[j] != words[No].eng[j]) {
                printf("\n\t\tWRONG\n");
                break;
            }
        }
    }

    printf("\n!!!!!  END  !!!!!\n\n");

    return 0;
}

void initialize(struct words_list words[]) {
    strcpy(words[1].eng, "to mean");
    strcpy(words[1].rus, "иметь ввиду");

    strcpy(words[2].eng, "she");
    strcpy(words[2].rus, "она");
}

int input(char *inp) {
    char c;
    int size = 0;
    while (c != '\n') {
        c = getchar();
        if (c == '\n') {
            break;
        } else {
            inp[size] = c;
            size++;
        }
    }

    return size;
}