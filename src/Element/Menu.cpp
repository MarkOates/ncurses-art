#include <ncurses_art/Element/Menu.h>

#include <ncurses_art/Element/Rectangle.h>
#include <ncurses_art/Element/Text.h>
#include <curses.h>

Menu::Menu(float x, float y, std::vector<std::string> options)
   : ElementBase("Menu")
   , x(x)
   , y(y)
   , options(options)
   , cursor_pos(0)
   , styles(0)
{
}

Menu::~Menu()
{
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
   int largest_length = 0;
   for (unsigned i=0; i<options.size(); i++)
   {
      if (options[i].length() > largest_length) largest_length = options[i].length();
   }

   Rectangle rectangle(x-3, y-1, largest_length+6, options.size()+2);
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
