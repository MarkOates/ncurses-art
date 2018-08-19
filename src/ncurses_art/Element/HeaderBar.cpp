#include <ncurses_art/Element/HeaderBar.hpp>

#include <ncurses_art/Element/Text.hpp>
#include <ncurses.h>
#include <sstream>

HeaderBar::HeaderBar()
   : ElementBase("HeaderBar")
   , text("[Untitled]")
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
   str << "Cs: " << COLORS << " W: " << COLS << " H: " << LINES;
   std::string width_height_text = str.str();
   mvprintw(0, COLS - width_height_text.length() - 2, width_height_text.c_str());

   attroff(A_REVERSE);
}
