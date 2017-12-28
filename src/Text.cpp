#include <ncurses_art/Text.h>

#include <ncurses.h>

Text::Text(std::string text, float x, float y)
   : text(text)
   , x(x)
   , y(y)
{
}

Text::~Text()
{
}

void Text::draw()
{
   mvprintw((int)y, (int)x, text.c_str());
}
