#include <ncurses.h>

int main(int, char**)
{
   initscr();
   cbreak();
   printw("Hello world.");
   getch();
   endwin();
   return 0;
}
