#include <ncurses_art/Element/WcharText.hpp>


WcharText::WcharText(std::wstring text, float x, float y, float align_x)
   : ElementBase("WcharText")
   , text(text)
   , x(x)
   , y(y)
   , align_x(align_x)
   , styles(0)
{
}

WcharText::~WcharText()
{
}

bool WcharText::set_text(std::wstring text)
{
   this->text = text;
   return true;
}

bool WcharText::set_x(float x)
{
   this->x = x;
   return true;
}

bool WcharText::set_y(float y)
{
   this->y = y;
   return true;
}

void WcharText::set_styles(int styles)
{
   this->styles = styles;
}

float WcharText::get_x()
{
   return x;
}

float WcharText::get_y()
{
   return y;
}

WcharText &WcharText::blink(bool on)
{
   on ? styles |= A_BLINK : styles &= ~A_BLINK;
   return *this;
}

WcharText &WcharText::bold(bool on)
{
   on ? styles |= A_BOLD : styles &= ~A_BOLD;
   return *this;
}

WcharText &WcharText::underline(bool on)
{
   on ? styles |= A_UNDERLINE : styles &= ~A_UNDERLINE;
   return *this;
}

WcharText &WcharText::reverse(bool on)
{
   on ? styles |= A_REVERSE : styles &= ~A_REVERSE;
   return *this;
}

WcharText &WcharText::color(int color_num)
{
   styles |= COLOR_PAIR(color_num);
   return *this;
}

std::wstring WcharText::get_text()
{
   return text;
}


#include <vector>
std::vector<std::wstring> ___split_wstring(std::wstring s, std::wstring delimiter);
void ___replace_tabs(std::wstring& str);


void WcharText::draw()
{
   if (text.empty()) return;

   int screen_width = COLS;
   float str_width = text.length();
   float x_pos = x - (str_width * align_x);
   attron(styles);
   int yy = 0;
   for (auto &line : ___split_wstring(text, L"\n"))
   {
      //___replace_tabs(line);
      int max_characters = (int)(screen_width - x_pos);
      mvaddnwstr((int)y + yy++, (int)x_pos, line.c_str(), max_characters);
   }
   attroff(styles);
}


////


std::vector<std::wstring> ___split_wstring(std::wstring s, std::wstring delimiter)
{
   std::vector<std::wstring> results;

   size_t pos = 0;
   std::wstring token;
   while ((pos = s.find(delimiter)) != std::wstring::npos) {
      token = s.substr(0, pos);
      results.push_back(token);
      s.erase(0, pos + delimiter.length());
   }
   results.push_back(s);

   return results;
}


void ___replace_tabs(std::wstring& str)
{
   static const std::wstring from = L"\t";
   static const std::wstring to = std::wstring(3, ' ');

   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
}


