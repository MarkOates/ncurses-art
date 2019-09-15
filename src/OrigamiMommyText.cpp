#include <OrigamiMommyText.hpp>
#include <OrigamiMommyFontLoader.hpp>

#include <ncurses.h>

OrigamiMommyText::OrigamiMommyText(std::string text, float x, float y, float align_x, float align_y)
   : ElementBase("OrigamiMommyText")
   , text(text)
   , x(x)
   , y(y)
   , align_x(align_x)
   , align_y(align_y)
   , styles(0)
{
}

OrigamiMommyText::~OrigamiMommyText()
{
}

bool OrigamiMommyText::set_text(std::string text)
{
   this->text = text;
   return true;
}

bool OrigamiMommyText::set_x(float x)
{
   this->x = x;
   return true;
}

bool OrigamiMommyText::set_y(float y)
{
   this->y = y;
   return true;
}

void OrigamiMommyText::set_styles(int styles)
{
   this->styles = styles;
}

float OrigamiMommyText::get_x()
{
   return x;
}

float OrigamiMommyText::get_y()
{
   return y;
}

OrigamiMommyText &OrigamiMommyText::blink(bool on)
{
   on ? styles |= A_BLINK : styles &= ~A_BLINK;
   return *this;
}

OrigamiMommyText &OrigamiMommyText::bold(bool on)
{
   on ? styles |= A_BOLD : styles &= ~A_BOLD;
   return *this;
}

OrigamiMommyText &OrigamiMommyText::underline(bool on)
{
   on ? styles |= A_UNDERLINE : styles &= ~A_UNDERLINE;
   return *this;
}

OrigamiMommyText &OrigamiMommyText::reverse(bool on)
{
   on ? styles |= A_REVERSE : styles &= ~A_REVERSE;
   return *this;
}

OrigamiMommyText &OrigamiMommyText::color(int color_num)
{
   styles |= COLOR_PAIR(color_num);
   return *this;
}

std::string OrigamiMommyText::get_text()
{
   return text;
}

#include <vector>
static std::vector<std::string> ___split_string(std::string s, std::string delimiter);
static void ___replace_tabs(std::string& str);


#include <map>

static std::map<char, std::vector<std::string>> letters = {};

static bool letters_loaded = false;

static void load_letters();

void load_letters()
{
   if (letters_loaded) return;

   OrigamiMommyFontLoader loader;
   letters = loader.load();

   letters_loaded = true;
}


#include <ASCIICharacterRenderer.hpp>



void OrigamiMommyText::draw()
{
   if (text.empty()) return;

   //attron(styles);
   load_letters();
   ASCIICharacterRenderer renderer;

   int xx = 0;
   for(char& c : get_text())
   {
      xx += renderer.draw_character(letters, tolower(c), x+xx, y);
   }
   //attroff(styles);
}


