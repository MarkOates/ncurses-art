#include <ncurses_art/Element/Frame.hpp>

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

   // horizontal lines
   for (unsigned yy=0; yy<(int)h; yy+=(h-1))
      for (unsigned xx=1; xx<(int)w-1; xx++)
         mvaddch((int)(y + yy), (int)(x + xx), ACS_HLINE);

   // vertical lines
   for (unsigned xx=0; xx<(int)w; xx+=(w-1))
      for (unsigned yy=1; yy<(int)h-1; yy++)
         mvaddch((int)(y + yy), (int)(x + xx), ACS_VLINE);

   // corners
   mvaddch((int)(y), (int)(x), ACS_ULCORNER);
   mvaddch((int)(y), (int)(x+(w-1)), ACS_URCORNER);
   mvaddch((int)(y+(h-1)), (int)(x), ACS_LLCORNER);
   mvaddch((int)(y+(h-1)), (int)(x+(w-1)), ACS_LRCORNER);

   attroff(styles);
}
