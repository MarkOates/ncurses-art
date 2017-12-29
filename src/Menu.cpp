#include <ncurses_art/Menu.h>

#include <ncurses_art/Rectangle.h>
#include <ncurses_art/Text.h>
#include <curses.h>

Menu::Menu(float x, float y, std::vector<std::string> options)
   : x(x)
   , y(y)
   , options(options)
   , cursor_pos(0)
{
}

Menu::~Menu()
{
}

float Menu::get_x()
{
   return x;
}

float Menu::get_y()
{
   return y;
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
   rectangle.set_styles(COLOR_PAIR(3));
   rectangle.draw();

   for (unsigned i=0; i<options.size(); i++)
   {
      std::string text_str = options[i];
      if (i == cursor_pos) text_str += " <=";
      Text text(text_str, x, y+i);
      if (i == cursor_pos) text.reverse();
      text.draw();
   }
}
