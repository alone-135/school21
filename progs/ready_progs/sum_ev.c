#include <stdio.h>

int main() {
    int i, x, sum = 0;

    scanf("%d", &i);

    while (i > 0) {
        x = i % 10;
        i = i / 10;

        if (x % 2 == 0) {
            sum = sum + x;
        }
    }

    printf("%d", sum);

    return 0;
}
