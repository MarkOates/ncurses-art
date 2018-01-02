#include <ncurses_art/Element/TabSet.h>

TabSet::TabSet(float x, float y, std::vector<std::string> tabs)
   : ElementBase("TabSet")
   , x(x)
   , y(y)
   , tabs(tabs)
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

void TabSet::draw()
{
   // next
}
