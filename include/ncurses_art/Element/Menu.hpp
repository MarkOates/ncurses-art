#pragma once

#include <ncurses_art/Element/ElementBase.hpp>
#include <string>
#include <vector>

class Menu : public ElementBase
{
private:
   float x, y, width;
   std::vector<std::string> options;
   int cursor_pos;
   int styles;

   void update_width();

public:
   Menu(float x, float y, std::vector<std::string> options = {});
   ~Menu();

   void set_x(float x);
   void set_y(float y);

   bool set_cursor_pos(int pos);
   void set_styles(int styles);
   bool set_options(std::vector<std::string> options);

   float get_x();
   float get_y();
   float get_width();
   float get_height();
   std::vector<std::string> get_options();
   int get_cursor_pos();
   int get_num_options();
   void move_cursor_up();
   void move_cursor_down();
   std::string current_selection();

   void draw() override;
};
