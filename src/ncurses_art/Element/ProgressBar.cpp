#include <ncurses_art/Element/ProgressBar.hpp>

#include <ncurses_art/Element/Frame.hpp>
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
   int inner_progress_bar_total_width = w - 4;
   char progress_bar_char = ' ';

   Frame frame(x, y, w, h);
   frame.set_styles(styles);
   frame.draw();

   std::string string_to_draw((int)(inner_progress_bar_total_width * value), progress_bar_char);

   int max_characters = inner_progress_bar_total_width; // a placeholder for now
                                                        // this feature is used to prevent words from wrapping around the screen if they fall off the right edge

   int styles_with_reverse = styles;
   styles_with_reverse |= A_REVERSE;
   // styles_wihtout_reverse = styles &= ~A_REVERSE;

   attron(styles_with_reverse);
   mvaddnstr(((int)y)+1, ((int)x)+2, string_to_draw.c_str(), max_characters);
   attroff(styles_with_reverse);
}
