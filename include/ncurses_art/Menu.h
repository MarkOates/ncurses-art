#pragma once

#include <string>
#include <vector>

class Menu
{
private:
   float x, y;
   std::vector<std::string> options;
   int cursor_pos;

public:
   Menu(float x, float y, std::vector<std::string> options = {});
   ~Menu();

   void move_cursor_up();
   void move_cursor_down();
   std::string current_selection();

   void draw();
};
