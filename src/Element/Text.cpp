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

bool Text::set_x(float x)
{
   this->x = x;
   return true;
}

bool Text::set_y(float y)
{
   this->y = y;
   return true;
}

void Text::set_styles(int styles)
{
   this->styles = styles;
}

float Text::get_x()
{
   return x;
}

float Text::get_y()
{
   return y;
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
int ___replace_tabs(std::string& str);

void Text::draw()
{
   if (text.empty()) return;

   int screen_width = COLS;
   float str_width = text.length();
   float x_pos = x - (str_width * align_x);
   attron(styles);
   int yy = 0;
   for (auto &line : ___split_string(text, "\n"))
   {
      ___replace_tabs(line);
      int max_characters = (int)(screen_width - x_pos);
      mvaddnstr((int)y + yy++, (int)x_pos, line.c_str(), max_characters);
   }
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


int ___replace_tabs(std::string& str)
{
   static const std::string from = "\t";
   static const std::string to = std::string(3, ' ');

   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
}


