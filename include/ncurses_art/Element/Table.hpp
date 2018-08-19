#pragma once

#include <ncurses_art/Element/ElementBase.hpp>
#include <string>
#include <vector>

class Table : public ElementBase
{
private:
   float x, y;
   std::vector<std::vector<std::string>> elements;
   int cursor_pos_x, cursor_pos_y;
   std::vector<std::vector<std::string>> &__validate_table_dimensions(std::vector<std::vector<std::string>> &elements);

public:
   Table(float x=0, float y=0, std::vector<std::vector<std::string>> elements={});
   ~Table();

   void set_x(float x);
   void set_y(float y);

   bool set_cursor_pos_x(int pos_x);
   bool set_cursor_pos_y(int pos_y);
   bool set_elements(std::vector<std::vector<std::string>> elements);
   bool set_element(int pos_x, int pos_y, std::string element);

   float get_x();
   float get_y();
   int get_cursor_pos_x();
   int get_cursor_pos_y();
   std::vector<std::vector<std::string>> get_elements();
   std::string get_element_at(int x, int y);
   int get_num_rows();
   int get_num_cols();
   void move_cursor_up();
   void move_cursor_down();
   void move_cursor_left();
   void move_cursor_right();
   std::string current_selection();

   void draw() override;
};
