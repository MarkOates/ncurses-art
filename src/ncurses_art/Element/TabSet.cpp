#include <ncurses_art/Element/TabSet.hpp>

#include <ncurses.h>

TabSet::TabSet(float x, float y, std::vector<std::string> tabs)
   : ElementBase("TabSet")
   , x(x)
   , y(y)
   , tabs(tabs)
   , horizontal_padding(3)
   , active_tab(0)
{
}

TabSet::~TabSet()
{
}

bool TabSet::set_x(float x)
{
   this->x = x;
   return true;
}

bool TabSet::set_y(float y)
{
   this->y = y;
   return true;
}

bool TabSet::set_tabs(std::vector<std::string> tabs)
{
   this->tabs = tabs;
   active_tab = 0;
   return true;
}

float TabSet::get_x()
{
   return x;
}

float TabSet::get_y()
{
   return y;
}

std::vector<std::string> TabSet::get_tabs()
{
   return tabs;
}

bool TabSet::goto_next_tab()
{
   active_tab = (active_tab + 1) % tabs.size();
   return true;
}

bool TabSet::goto_previous_tab()
{
   active_tab = (active_tab - 1 + tabs.size()) % tabs.size();
   return true;
}

std::string TabSet::current_tab()
{
   if (tabs.empty()) return "";
   return tabs[active_tab];
}

void __draw_tab(float x, float y, std::string text, bool active)
{
   float w = text.length() + 6;
   float h = 3;

   // horizontal lines
   for (unsigned yy=0; yy<(int)h; yy+=(active ? h : (h-1)))
      for (unsigned xx=1; xx<(int)w-1; xx++)
         mvaddch((int)(y + yy), (int)(x + xx), ACS_HLINE);

   // vertical lines
   for (unsigned xx=0; xx<(int)w; xx+=(w-1))
      for (unsigned yy=1; yy<(int)h-1; yy++)
         mvaddch((int)(y + yy), (int)(x + xx), ACS_VLINE);

   // corners
   mvaddch((int)(y), (int)(x), ACS_ULCORNER);
   mvaddch((int)(y), (int)(x+(w-1)), ACS_URCORNER);

   if (active)
   {
      mvaddch((int)(y + (h - 1)), (int)(x), ACS_LRCORNER);
      mvaddch((int)(y+(h-1)), (int)(x+(w-1)), ACS_LLCORNER);
   }
   else
   {
      mvaddch((int)(y + (h - 1)), (int)(x), ACS_BTEE);
      mvaddch((int)(y+(h-1)), (int)(x+(w-1)), ACS_BTEE);
   }

   mvaddstr((int)(y+1), (int)(x)+3, text.c_str());
}

void TabSet::draw()
{
   float x_cursor = 0;
   int count = 0;
   for (auto &tab : tabs)
   {
      __draw_tab(x_cursor, y, tab, count == active_tab);
      x_cursor += tab.length() + horizontal_padding * 2;
      count++;
   };
}
