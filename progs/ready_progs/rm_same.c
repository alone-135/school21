#include <stdio.h>
#include <stdlib.h>

void check(int ch);
void input(int* mas, int* i);
void output(int* mas, int i);

void sort(int* mas, int* i);

int main() {
    int mas[1024] = {-1};
    int i = 1;

    input(mas, &i);
    sort(mas, &i);
    output(mas, i);

    return 0;
}

void sort(int* mas, int* i) {
    int temp;
    for (int a = 0; a < *i; a++) {
        temp = mas[a];
        for (int b = a + 1; b < *i; b++) {
            if (mas[b] == temp) {
                for (int c = b; c < *i; c++) {
                    mas[c] = mas[c + 1];
                }
                *i = *i - 1;
            }
        }
    }
}

void input(int* mas, int* i) {
    int ch;
    ch = getchar();
    check(ch);
    mas[0] = ch - 48;
    while ((ch = getchar()) != '\n') {
        check(ch);
        mas[*i] = ch - 48;
        *i = *i + 1;
    }
}

void check(int ch) {
    if (48 > ch || ch > 57) {
        printf("n/a");
        exit(0);
    }
}

void output(int* mas, int i) {
    for (int a = 0; a < i; a++) {
        printf("%d", mas[a]);
    }
}
