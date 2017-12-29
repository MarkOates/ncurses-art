#pragma once

#include <ncurses_art/Element.h>
#include <string>
#include <vector>

class Menu : public Element
{
private:
   float x, y;
   std::vector<std::string> options;
   int cursor_pos;

public:
   Menu(float x, float y, std::vector<std::string> options = {});
   ~Menu();

   float get_x();
   float get_y();
   void move_cursor_up();
   void move_cursor_down();
   std::string current_selection();

   void draw() override;
};
