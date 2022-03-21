// Чекер на всё, кроме целых чисел
int check() {
    char check;
    if ((scanf("%c", &check) == 1) && (check == '\n' || check == '\0')) {
    return 1;
    }
    return 0;
}