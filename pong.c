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

    do {
        sprintf(mas[0], "####################");
        for (i = 1; i < 9; i++)
            sprintf(mas[i], "#                  #");
        sprintf(mas[9], "####################");

        mas[y][x] = '@';

        system("clear");

        for (i = 0; i < 10; i++)
            printf("%s\n", mas[i]);

            key = getch();
            if (key == 'w') y--;
            if (key == 's') y++;
            if (key == 'a') x--;
            if (key == 'd') x++;
    }
    while (key != 'c'); {}

    return 0;
}
