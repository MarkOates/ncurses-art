#include <ncurses_art/Element/ProgressBar.hpp>

#include <ncurses.h>

ProgressBar::ProgressBar(float x, float y, float w, float h)
   : ElementBase("ProgressBar")
   , x(x)
   , y(y)
   , w(w)
   , h(h)
   , value(0.0)
{
}

ProgressBar::~ProgressBar()
{
}

float ProgressBar::get_value()
{
   return value;
}

void ProgressBar::set_value(float value)
{
   this->value = value;
}

void ProgressBar::set_styles(int styles)
{
   this->styles = styles;
}

void ProgressBar::draw()
{
   attron(styles);
   for (unsigned yy=0; yy<(int)h; yy++)
      for (unsigned xx=0; xx<(int)w; xx++)
         mvaddch((int)(y + yy), (int)(x + xx), ' ');
   attroff(styles);
}
