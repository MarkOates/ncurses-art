#include <ncurses_art/Screen.h>

#include <ncurses.h>

Screen::Screen()
{
   initscr();
   cbreak();
   start_color();

   noecho();
   cbreak();
   curs_set(0);
}

Screen::~Screen()
{
   endwin();
}
