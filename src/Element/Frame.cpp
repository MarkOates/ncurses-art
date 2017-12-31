#include <ncurses_art/Element/Frame.h>

#include <ncurses.h>

Frame::Frame(float x, float y, float w, float h)
   : ElementBase("Frame")
   , x(x)
   , y(y)
   , w(w)
   , h(h)
{
}

Frame::~Frame()
{
}

void Frame::set_styles(int styles)
{
   this->styles = styles;
}

void Frame::draw()
{
   attron(styles);
   for (unsigned yy=0; yy<(int)h; yy++)
      for (unsigned xx=0; xx<(int)w; xx++)
         mvaddch((int)(y + yy), (int)(x + xx), ' ');
   attroff(styles);
}
