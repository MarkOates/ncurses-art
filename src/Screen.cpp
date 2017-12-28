#include <ncurses_art/Screen.h>

#include <ncurses.h>

Screen::Screen()
{
   initscr();
   cbreak();
}

Screen::~Screen()
{
   endwin();
}
