#include <ncurses_art/HeaderBar.h>

#include <ncurses.h>

HeaderBar::HeaderBar()
   : text("[Untitled]")
{
}

HeaderBar::~HeaderBar()
{
}

void HeaderBar::draw()
{
   attron(A_REVERSE);
   mvprintw(0, 0, text.c_str());
   chgat(-1, A_REVERSE, 0, NULL);
   attroff(A_REVERSE);
}
