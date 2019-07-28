#include <Projekt.h>

#include <ncurses.h>

#include <map>

#include "projekt_helper.h"




#define MOVE_MENU_OPTION_UP "move_menu_option_up"
#define MOVE_MENU_OPTION_DOWN "move_menu_option_down"
#define START_INPUT "start_input"
#define INPUT_FINISHED "input_finished"
#define SUBMIT_FORM "submit_form"

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

std::string get_input_val(std::string name)
{
   return find_text(attr_name(name, "input")).get_text();
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




class InputForm
{
private:
   std::vector<std::pair<std::string, std::string>> input_elements;

public:
   InputForm(std::vector<std::pair<std::string, std::string>> input_elements = {})
      : input_elements(input_elements)
   {}
   virtual ~InputForm() {}

   void initialize()
   {
      int x = 40;
      int y = 20;
      int vertical_spacing = 4;

      std::vector<std::string> menu_options;

      int y_cursor = y;
      for (auto &input_element : input_elements)
      {
         std::string input_name = std::get<0>(input_element);
         std::string input_label = std::get<1>(input_element);

         create_input(input_name, x, y_cursor, input_label);
         y_cursor += vertical_spacing;

         menu_options.push_back(input_name);
      }

      menu_options.push_back(SUBMIT_FORM);

      create_menu("input_selector", 0, 2).set_options(menu_options);
   }

   virtual void submit()
   {
      if (get_input_val("title").empty()) throwit("Title is empty");
   }
};





std::map<char, std::string> mappings;
std::map<std::string, void(*)()> events;
InputForm input_form({
   { "upstream",    "Upstream:" },
   { "title",       "Title:" },
   { "description", "Description:" },
});


Projekt::Projekt()
{
   current_project = this;
   create_text(":state", 0, 3).set_text("normal");
   
   input_form.initialize();

   init_color(20, (int)(175.0/255.0*1000), (int)(175.0/255.0*1000), (int)(255.0/255.0*1000));
   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_color(22, (int)(32.0/255.0*1000), (int)(32.0/255.0*1000), (int)(32.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);
   init_pair(1, 20, 22);

   create_header_bar("header_bar");

   events[EVENT_PROGRAM_INITIALIZED] = []{};
   events[START_INPUT] = []{
      if (find_menu("input_selector").current_selection() == SUBMIT_FORM)
      {
         ::emit_event(SUBMIT_FORM);
      }
      else
      {
         set(":state", "input");
         std::string str = find_menu("input_selector").current_selection();
         set_input(str, "");
         std::pair<float, float> pos = get_input_pos(str);
         set_buffer_pos(std::get<0>(pos), std::get<1>(pos));
      }
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
   events[SUBMIT_FORM] = []{
      input_form.submit();
      // validate essential pieces
      // TODO validate more pieces

      // build command
      //std::stringstream submit_command;
      //submit_command << "UPSTREAM=Shopify/stock-photos:master;";
      //submit_command << "TITLE=\"" << get_input_val("title") << "\";";
      //submit_command << "BRANCH_NAME=`git rev-parse --abbrev-ref HEAD`;";
      //submit_command << "git push origin ${BRANCH_NAME};";
      //submit_command << get_input_val("title");
      //system("UPSTREAM=Shopify/stock-photos:master; echo \"${UPSTREAM}\" > asdfasdf.txt");
      ::emit_event(EVENT_ABORT_PROGRAM);
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

