#include "Projekt2.h"

#define SET_TEXT "set_text"
#define TOGGLE_CHECKBOX "toggle_checkbox"
#define CHECKBOX_TOGGLE_CHANGE "checkbox_toggle_change"

std::string attr_name(std::string element, std::string attribute)
{
   return element + "__" + attribute;
}

Text &find_attr(std::string element_name, std::string attribute)
{
   return find_text(attr_name(element_name, attribute));
}

// checkboxes

void create_checkbox(std::string name, int cbx, int cby, std::string text)
{
   create_text(attr_name(name, "name"), 0, -1).set_text(name);
   create_text(attr_name(name, "is_checked"), 0, -1).set_text("no");

   create_frame(attr_name(name, "frame"), cbx, cby, 4, 3);
   create_text(attr_name(name, "text"), cbx + 6, cby + 1).set_text(text);
   create_text(attr_name(name, "checked"), cbx + 1, cby + 1).set_text("  ");
}

void toggle_checkbox(std::string name)
{
   Text &is_checked = find_attr(name, "is_checked");
   if (is_checked.get_text() == "no")
   {
      is_checked.set_text("yes");
      find_text(attr_name(name, "checked")).reverse(true);
      emit_event(CHECKBOX_TOGGLE_CHANGE);
   }
   else if (is_checked.get_text() == "yes")
   {
      is_checked.set_text("no");
      find_text(attr_name(name, "checked")).reverse(false);
      emit_event(CHECKBOX_TOGGLE_CHANGE);
   }
}

// text input

void initialize()
{
   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);

   create_checkbox("checkbox", 20, 20, "Be awesome");

   events = {{
      SET_TEXT, [] {
         find_text("text").set_text("Hello world!");
      }}, {
      TOGGLE_CHECKBOX, [] {
         toggle_checkbox("checkbox");
      }}, {
      CHECKBOX_TOGGLE_CHANGE, [] {
      }}, 
   };

   mappings['s'] = SET_TEXT;
   mappings[32] = TOGGLE_CHECKBOX;
}

