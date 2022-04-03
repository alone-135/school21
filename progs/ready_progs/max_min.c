#include <stdio.h>

int main() {
    int i, x;
    int max = 0;
    int min = 9;
    // int mas[1024] = {0};

    scanf("%d", &i);

    while (i > 0) {
        x = i % 10;
        if (x > max) {
            max = x;
        }
        if (x < min) {
            min = x;
        }
        i = i / 10;
    }
    printf("%d %d", max, min);

    return 0;
}
