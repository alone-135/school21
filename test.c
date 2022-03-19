#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

int main() {

   char c;
   struct termios0 tty, savetty;

   fflush(stdout); // вывели буфер
   printf("fflush(stdout);");
   tcgetattr(0, &tty); // получили структуру termios
   savetty = tty; // сохранили
   tty.c_lflag &= ~(ISIG | ICANON);
   // ISIG - when any of the characters  INTR,  QUIT,  SUSP,  or DSUSP are received, generate the corresponding signal.
   // ICANON - enable canonical mode.  This  enables  the  special characters  EOF,  EOL,  EOL2, ERASE, KILL, REPRINT, STATUS, and WERASE, and buffers by lines.
   tty.c_cc[VMIN] = 1;
   tcsetattr(0, TCSAFLUSH, &tty);
   read(0, &c, 1);
   tcsetattr(0, TCSANOW, &savetty);
   printf("%c", c);
   return 0;
}

