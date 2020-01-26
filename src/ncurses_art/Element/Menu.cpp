#include <ncurses_art/Element/Menu.hpp>

#include <ncurses_art/Element/Rectangle.hpp>
#include <ncurses_art/Element/Text.hpp>
#include <stdexcept>
#include <curses.h>

Menu::Menu(float x, float y, std::vector<std::string> options)
   : ElementBase("Menu")
   , x(x)
   , y(y)
   , width(0)
   , options({})
   , cursor_pos(0)
   , styles(0)
{
   set_options(options);
}

Menu::~Menu()
{
}

void Menu::update_width()
{
   this->width = 0;
   for (auto &option : options)
      if (option.length() > this->width) this->width = option.length();
}

void Menu::set_x(float x)
{
   this->x = x;
}

void Menu::set_y(float y)
{
   this->y = y;
}

bool Menu::set_cursor_pos(int pos)
{
   if (pos < 0) throw std::runtime_error("Cannot set_cursor_pos to a negative number");
   if (options.empty()) cursor_pos = 0;
   else cursor_pos = pos % options.size();
   return true;
}

void Menu::set_styles(int styles)
{
   this->styles = styles;
}

bool Menu::set_options(std::vector<std::string> options)
{
   this->options = options;
   cursor_pos = 0;
   update_width();
   return true;
}

float Menu::get_x()
{
   return x;
}

float Menu::get_y()
{
   return y;
}

float Menu::get_width()
{
   return width;
}

float Menu::get_height()
{
   return options.size();
}

std::vector<std::string> Menu::get_options()
{
   return options;
}

int Menu::get_cursor_pos()
{
   return cursor_pos;
}

int Menu::get_num_options()
{
   return options.size();
}

void Menu::move_cursor_up()
{
   cursor_pos = (cursor_pos - 1 + options.size()) % options.size();
}

void Menu::move_cursor_down()
{
   cursor_pos = (cursor_pos + 1) % options.size();
}

std::string Menu::current_selection()
{
   if (options.empty()) return "";
   return options[cursor_pos];
}

void Menu::draw()
{
   Rectangle rectangle(x-3, y-1, get_width()+6, get_height()+2);
   rectangle.set_styles(styles);
   rectangle.draw();

   for (unsigned i=0; i<options.size(); i++)
   {
      std::string text_str = options[i];
      if (i == cursor_pos) text_str += " <=";
      Text text(text_str, x, y+i);
      text.set_styles(styles);
      if (i == cursor_pos) text.reverse();
      text.draw();
   }
}
