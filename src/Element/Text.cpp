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

std::string Text::get_text()
{
   return text;
}

#include <vector>
std::vector<std::string> ___split_string(std::string s, std::string delimiter);

void Text::draw()
{
   if (text.empty()) return;

   float str_width = text.length();
   float x_pos = x - (str_width * align_x);
   attron(styles);
   int yy = 0;
   for (auto &line : ___split_string(text, "\n"))
      mvaddstr((int)y + yy++, (int)x_pos, line.c_str());
   attroff(styles);
}

////


std::vector<std::string> ___split_string(std::string s, std::string delimiter)
{
   std::vector<std::string> results;

   size_t pos = 0;
   std::string token;
   while ((pos = s.find(delimiter)) != std::string::npos) {
       token = s.substr(0, pos);
       results.push_back(token);
       s.erase(0, pos + delimiter.length());
   }
   results.push_back(s);

   return results;
}
