#include <ncurses_art/Element/Rectangle.hpp>

#include <ncurses.h>

Rectangle::Rectangle(float x, float y, float w, float h)
   : ElementBase("Rectangle")
   , x(x)
   , y(y)
   , w(w)
   , h(h)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::set_styles(int styles)
{
   this->styles = styles;
}

void Rectangle::draw()
{
   attron(styles);
   for (unsigned yy=0; yy<(int)h; yy++)
      for (unsigned xx=0; xx<(int)w; xx++)
         mvaddch((int)(y + yy), (int)(x + xx), ' ');
   attroff(styles);
}
