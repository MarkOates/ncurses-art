#include <ncurses_art/Screen.h>

#include <ncurses.h>

Screen::Screen()
   : initialized(false)
{
}

Screen::~Screen()
{
   if (!initialized) return;

   curs_set(1);
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

   initialized = true;

   return true;
}
