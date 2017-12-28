#include <ncurses_art/Text.h>

#include <ncurses.h>

Text::Text(std::string text, float x, float y, float align_x)
   : text(text)
   , x(x)
   , y(y)
   , align_x(align_x)
   , styles(0)
{
}

Text::~Text()
{
}

void Text::set_styles(int styles)
{
   this->styles = styles;
}

void Text::draw()
{
   float str_width = text.length();
   float x_pos = x - (str_width * align_x);
   attron(styles);
   mvprintw((int)y, (int)x_pos, text.c_str());
   attroff(styles);
}
