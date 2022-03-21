#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

int getch() {
    int ch;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    char mas[10][21];
    int i;
    int x = 10, y = 5;
    char key;
    int ox, oy;
    int ax = 5;
    int ay = 3;
    int score = 0;
    srand(1);

    do {
        sprintf(mas[0], "####################");
        for (i = 1; i < 9; i++)
            sprintf(mas[i], "#                  #");
        sprintf(mas[9], "####################");

        mas[y][x] = '@';
        mas[ay][ax] = '*';

        system("clear");

        for (i = 0; i < 10; i++)
            printf("%s\n", mas[i]);
            printf("SCORE: %2d\n", score);
            key = getch();

            ox = x;
            oy = y;

            if (key == 'w') y--;
            if (key == 's') y++;
            if (key == 'a') x--;
            if (key == 'd') x++;
            if (mas[y][x] == '#') {
                x = ox;
                y = oy;
            }
            if ((x == ax) && (y == ay)) {
                score++;
                ax = rand() * 1.0 / RAND_MAX * 18 + 1;
                ay = rand() * 1.0 / RAND_MAX * 8 + 1;
            }
    }
    while (key != 'q'); 

    return 0;
}
