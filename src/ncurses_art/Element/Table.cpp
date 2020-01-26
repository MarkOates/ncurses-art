#include <ncurses_art/Element/Table.hpp>

#include <ncurses_art/Element/Rectangle.hpp>
#include <ncurses_art/Element/Text.hpp>
#include <curses.h>
#include <sstream>
#include <stdexcept>

std::vector<std::vector<std::string>> &Table::__validate_table_dimensions(std::vector<std::vector<std::string>> &elements)
{
   if (elements.empty()) return elements;
   int row_0_num_cols = elements[0].size();
   for (unsigned row=0; row<elements.size(); row++)
      if (elements[row].size() != row_0_num_cols)
      {
         std::stringstream error_message;
         error_message << "Table error: Num cols on row " << row << " (" << elements[row].size() << ") is not equal to the num cols in the previous row (" << row_0_num_cols << ")";
         throw std::runtime_error(error_message.str());
      }
   return elements;
}

Table::Table(float x, float y, std::vector<std::vector<std::string>> elements)
   : ElementBase("Table")
   , x(x)
   , y(y)
   , elements(__validate_table_dimensions(elements))
   , cursor_pos_x(0)
   , cursor_pos_y(0)
{
}

Table::~Table()
{
}

void Table::set_x(float x)
{
   this->x = x;
}

void Table::set_y(float y)
{
   this->y = y;
}

bool Table::set_cursor_pos_x(int pos_x)
{
   if (pos_x < 0) throw std::runtime_error("Cannot set_cursor_pos_x to a negative number");
   if (get_num_cols() == 0) cursor_pos_x = 0;
   else cursor_pos_x = pos_x % get_num_cols();
   return true;
}

bool Table::set_cursor_pos_y(int pos_y)
{
   if (pos_y < 0) throw std::runtime_error("Cannot set_cursor_pos_y to a negative number");
   if (get_num_rows() == 0) cursor_pos_y = 0;
   else cursor_pos_y = pos_y % get_num_rows();
   return true;
}

bool Table::set_elements(std::vector<std::vector<std::string>> elements)
{
   this->elements = __validate_table_dimensions(elements);
   cursor_pos_x = 0;
   cursor_pos_y = 0;
   return true;
}

bool Table::set_element(int pos_x, int pos_y, std::string element)
{
   if (pos_x < 0) throw std::runtime_error("Table [set_element] error: pos_x cannot be less than 0");
   if (pos_y < 0) throw std::runtime_error("Table [set_element] error: pos_y cannot be less than 0");
   if (pos_x >= get_num_cols())
   {
      std::stringstream error_message;
      error_message << "[Table::set_element error]: pos_x (value: \"" << pos_x << "\") cannot be greater than or equal the number of cols (value: \"" << get_num_cols() << "\")";
      throw std::runtime_error(error_message.str());
   }
   if (pos_y >= get_num_rows())
   {
      std::stringstream error_message;
      error_message << "[Table::set_element error]: pos_y (value: \"" << pos_y << "\") cannot be greater than or equal the number of rows (value: \"" << get_num_rows() << "\")";
      throw std::runtime_error(error_message.str());
   }
   elements[pos_y][pos_x] = element;
   return true;
}

float Table::get_x()
{
   return x;
}

float Table::get_y()
{
   return y;
}

int Table::get_cursor_pos_x()
{
   return cursor_pos_x;
}

int Table::get_cursor_pos_y()
{
   return cursor_pos_y;
}

std::vector<std::vector<std::string>> Table::get_elements()
{
   return elements;
}

std::string Table::get_element_at(int x, int y)
{
   if (x < 0) throw std::runtime_error("Table [get_element_at] error: x cannot be less than 0");
   if (y < 0) throw std::runtime_error("Table [get_element_at] error: y cannot be less than 0");
   if (x >= get_num_cols())
   {
      std::stringstream error_message;
      error_message << "[Table::get_element_at error]: x (value: \"" << x << "\") cannot be greater than or equal the number of cols (value: \"" << get_num_cols() << "\")";
      throw std::runtime_error(error_message.str());
   }
   if (y >= get_num_rows())
   {
      std::stringstream error_message;
      error_message << "[Table::get_element_at error]: y (value: \"" << y << "\") cannot be greater than or equal the number of rows (value: \"" << get_num_rows() << "\")";
      throw std::runtime_error(error_message.str());
   }
   return elements[y][x];
}

int Table::get_num_rows()
{
   return elements.size();
}

int Table::get_num_cols()
{
   if (elements.empty()) return 0;
   return elements[0].size();
}

void Table::move_cursor_up()
{
   cursor_pos_y = (cursor_pos_y - 1 + get_num_rows()) % get_num_rows();
}

void Table::move_cursor_down()
{
   cursor_pos_y = (cursor_pos_y + 1) % get_num_rows();
}

void Table::move_cursor_left()
{
   cursor_pos_x = (cursor_pos_x - 1 + get_num_cols()) % get_num_cols();
}

void Table::move_cursor_right()
{
   cursor_pos_x = (cursor_pos_x + 1) % get_num_cols();
}

std::string Table::current_selection()
{
   if (get_num_cols() == 0 || get_num_rows() == 0) return "";
   return elements[cursor_pos_y][cursor_pos_x];
}

void Table::draw()
{
   int assumed_column_length = 20;
   int num_cols = get_num_cols();

   Rectangle rectangle(x-3, y-1, assumed_column_length*num_cols+6, elements.size()+2);
   //rectangle.set_styles(styles);
   rectangle.draw();

   for (unsigned yy=0; yy<elements.size(); yy++)
      for (unsigned xx=0; xx<elements[yy].size(); xx++)
      {
         std::string text_str = elements[yy][xx];
         //if (i == cursor_pos) text_str += " <=";
         Text text(text_str, x+xx*assumed_column_length, y+yy);
         //text.set_styles(styles);
         if (xx == cursor_pos_x && yy == cursor_pos_y) text.reverse();
         text.draw();
      }
}

