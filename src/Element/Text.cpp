#include <ncurses_art/Element/Text.h>

#include <ncurses.h>

Text::Text(std::string text, float x, float y, float align_x)
   : ElementBase("Text")
   , text(text)
   , x(x)
   , y(y)
   , align_x(align_x)
   , styles(0)
{
}

Text::~Text()
{
}

bool Text::set_text(std::string text)
{
   this->text = text;
   return true;
}

void Text::set_styles(int styles)
{
   this->styles = styles;
}

Text &Text::blink(bool on)
{
   on ? styles |= A_BLINK : styles &= ~A_BLINK;
   return *this;
}

Text &Text::bold(bool on)
{
   on ? styles |= A_BOLD : styles &= ~A_BOLD;
   return *this;
}

Text &Text::underline(bool on)
{
   on ? styles |= A_UNDERLINE : styles &= ~A_UNDERLINE;
   return *this;
}

Text &Text::reverse(bool on)
{
   on ? styles |= A_REVERSE : styles &= ~A_REVERSE;
   return *this;
}

Text &Text::color(int color_num)
{
   styles |= COLOR_PAIR(color_num);
   return *this;
}

void Text::draw()
{
   float str_width = text.length();
   float x_pos = x - (str_width * align_x);
   attron(styles);
   mvaddstr((int)y, (int)x_pos, text.c_str());
   attroff(styles);
}
