#include <Projekt.h>

#include <ncurses.h>

#include <map>

#include "projekt_helper.h"

#define MOVE_MENU_OPTION_UP "move_menu_option_up"
#define MOVE_MENU_OPTION_DOWN "move_menu_option_down"
#define START_INPUT "start_input"
#define INPUT_FINISHED "input_finished"

std::string get(std::string var) { return find_text(var).get_text(); }
bool set(std::string var, std::string val) { return find_text(var).set_text(val); }

std::string attr_name(std::string element, std::string attribute)
{
   return element + "__" + attribute;
}

Text &find_attr(std::string element_name, std::string attribute)
{
   return find_text(attr_name(element_name, attribute));
}

void create_input(std::string name, int ifx, int ify, std::string label)
{
   create_frame(attr_name(name, "frame"), ifx, ify, 40, 3);
   create_text(attr_name(name, "label"), ifx-4, ify+1, 1.0).set_text(label);
   create_text(attr_name(name, "input"), ifx+3, ify+1).set_text("");
}

std::pair<float, float> get_input_pos(std::string name)
{
   Text &input = find_text(attr_name(name, "input"));
   std::pair<float, float> pos = {
      input.get_x(),
      input.get_y(),
   };
   return pos;
}

void set_input(std::string name, std::string value)
{
   find_text(attr_name(name, "input")).set_text(value);
}

void set_buffer_pos(float x, float y)
{
   Text &text = find_text(":input_buffer");
   text.set_x(x);
   text.set_y( y);
}

void hide_buffer()
{
   Text &text = find_text(":input_buffer");
   text.set_x(0);
   text.set_y(3);
}

std::map<char, std::string> mappings;
std::map<std::string, void(*)()> events;

Projekt::Projekt()
{
   current_project = this;
   create_text(":state", 0, 3).set_text("normal");
   
   init_color(20, (int)(175.0/255.0*1000), (int)(175.0/255.0*1000), (int)(255.0/255.0*1000));
   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_color(22, (int)(32.0/255.0*1000), (int)(32.0/255.0*1000), (int)(32.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);
   init_pair(1, 20, 22);

   create_header_bar("header_bar");
   create_input("text_input1", 40, 20, "First Name:");
   create_input("text_input2", 40, 25, "Last Name:");
   create_input("text_input3", 40, 30, "Address:");

   create_menu("input_selector", 0, 2).set_options({ "text_input1", "text_input2", "text_input3" });

   events[EVENT_PROGRAM_INITIALIZED] = []{};
   events[START_INPUT] = []{
      set(":state", "input");
      std::string str = find_menu("input_selector").current_selection();
      set_input(str, "");
      std::pair<float, float> pos = get_input_pos(str);
      set_buffer_pos(std::get<0>(pos), std::get<1>(pos));
   };
   events[INPUT_FINISHED] = []{
      std::string str = find_menu("input_selector").current_selection();
      set_input(str, get(":input_buffer"));
      set(":input_buffer", "");
      hide_buffer();
   };
   events[MOVE_MENU_OPTION_UP] = []{
      find_menu("input_selector").move_cursor_up();
   };
   events[MOVE_MENU_OPTION_DOWN] = []{
      find_menu("input_selector").move_cursor_down();
   };

   mappings['q'] = EVENT_ABORT_PROGRAM;
   mappings['j'] = MOVE_MENU_OPTION_DOWN;
   mappings['k'] = MOVE_MENU_OPTION_UP;
   mappings[10] = START_INPUT;

   // these should always be in back:

   create_text(":input_buffer", 0, 3).set_text("");
   texts().back()->set_styles(COLOR_PAIR(1));
}

bool Projekt::process_input(char input_ch)
{
   std::string state = get(":state");

   if (state == "normal")
   {
      if (mappings.find(input_ch) == mappings.end()) { return false; }
      return emit_event(mappings[input_ch]);
   }
   else if (state == "input")
   {
      if (input_ch == 10) // enter
      {
         set(":state", "normal");
         emit_event(INPUT_FINISHED);
      }
      if (input_ch == 127) // backspace
      {
         if (!get(":input_buffer").empty())
         {
            std::string buff = get(":input_buffer");
            buff.erase(buff.size() - 1);
            set(":input_buffer",buff);
         }
      }
      else
      {
         set(":input_buffer", get(":input_buffer").append(1, input_ch));
      }
   }
   else
   {
      std::stringstream ss;
      ss << "Unknown state \"" << state << "\"";
      throwit(ss.str()); 
   }

   return false;
}

bool Projekt::process_event(std::string e)
{
   if (events.find(e) == events.end()) return false;
   events[e]();
   return true;
}
