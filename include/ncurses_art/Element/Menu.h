#pragma once

#include <ncurses_art/Element/ElementBase.h>
#include <string>
#include <vector>

class Menu : public ElementBase
{
private:
   float x, y;
   std::vector<std::string> options;
   int cursor_pos;
   int styles;

public:
   Menu(float x, float y, std::vector<std::string> options = {});
   ~Menu();

   bool set_cursor_pos(int pos);
   void set_styles(int styles);
   bool set_options(std::vector<std::string> options);

   float get_x();
   float get_y();
   int get_cursor_pos();
   void move_cursor_up();
   void move_cursor_down();
   std::string current_selection();

   void draw() override;
};
