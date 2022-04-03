#include <stdio.h>

int main() {
    int sum, ch;
    ch = getchar();
    if (48 <= ch && ch <= 57) {
        sum = ch - 48;
        while ((ch = getchar()) != '\n') {
            sum += ch - 48;
        }
        printf("%d", sum);
    } else {
        printf("n/a");
    }

    return 0;
}
