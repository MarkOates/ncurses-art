#include <ncurses_art/Screen.h>

#include <ncurses.h>

Screen::Screen()
   : initialized(false)
{
}

Screen::~Screen()
{
   if (!initialized) return;

   endwin();
}

bool Screen::initialize()
{
   if (initialized) return true;

   initscr();
   cbreak();
   start_color();

   noecho();
   curs_set(0);

   return true;
}
