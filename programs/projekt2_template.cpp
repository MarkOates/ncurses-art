#include "Projekt2.h"

#define SET_TEXT "set_text"

void initialize()
{
   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);

   create_text("text", 10, 20);
   create_frame("frame", 20, 30, 80, 7).set_styles(COLOR_PAIR(3));

   mappings['s'] = SET_TEXT;

   events[SET_TEXT] = []{
      find_text("text").set_text("Hello world!");
   };
}
