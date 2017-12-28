#include <ncurses_art/HeaderBar.h>

#include <ncurses_art/Text.h>
#include <ncurses.h>
#include <sstream>

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

   // draw the primary header text
   mvprintw(0, 0, text.c_str());
   chgat(-1, A_REVERSE, 0, NULL);

   // draw the info text
   std::stringstream str;
   str << "W: " << COLS << " H: " << LINES;
   std::string width_height_text = str.str();
   mvprintw(0, COLS - width_height_text.length() - 2, width_height_text.c_str());

   attroff(A_REVERSE);
}
