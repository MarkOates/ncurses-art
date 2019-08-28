#include "Projekt2.h"

#define SET_TEXT "set_text"
#define SET_TEXT2 "set_text2"

void initialize()
{
   TextInput &text_input = create_text_input("text_input", 50, 20);
   text_input.set_label("First name");
   text_input.set_value("Markolumu");

   mappings['s'] = SET_TEXT;
   mappings['x'] = SET_TEXT2;

   events[SET_TEXT] = []{
      find_text_input("text_input").set_value("Tommy Dorsey");
   };
   events[SET_TEXT2] = []{
      find_text_input("text_input").set_value("");
   };
}

