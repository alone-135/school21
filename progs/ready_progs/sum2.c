#include <stdio.h>

int main() {
    int i, x;
    int sum = 0;
    scanf("%d", &i);

    while (i != 0) {
        x = i % 10;
        i = i / 10;

        sum += x;

        if (i == 0) {
            break;
        }
        printf("%d %d\n", x, i);
    }

    printf("%d", sum);

    return 0;
}
