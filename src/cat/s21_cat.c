#include <stdio.h>

#include "s21_cat_lib.h"

int main(int argc, char** argv) {
    printf("\nargument count:\t\t%d\narguments:\t\t", argc);
    for (int i = 0; i < argc; i++) {
        printf("[%d]%s ", i, argv[i]);
    }
    printf("\n\n");

    return 0;
}
