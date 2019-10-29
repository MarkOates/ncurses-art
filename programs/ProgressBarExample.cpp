#include "Projekt2.h"

#include "unistd.h" // for usleep

#include <iostream>

#define RUN_WHOLE_EXAMPLE_PROGRAM "run whole example program"
#define SET_TEXT "set_text"
#define SLEEP_FOR_3_SECONDS "sleep for 3 seconds"

void initialize()
{
   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);

   create_text("text", 10, 20);
   create_frame("frame", 20, 30, 80, 7);//.set_styles(COLOR_PAIR(3));

   mappings['s'] = SET_TEXT;
   mappings[' '] = EVENT_ABORT_PROGRAM;

   events[RUN_WHOLE_EXAMPLE_PROGRAM] = []{
      emit_event(SET_TEXT);
      emit_event(SLEEP_FOR_3_SECONDS);
      emit_event(EVENT_ABORT_PROGRAM);
   };
   events[SET_TEXT] = []{
      find_text("text").set_text("Hello world!");
   };
   events[SLEEP_FOR_3_SECONDS] = []{
      usleep(2000000);
      //find_text("text").set_text("Hello world!");
   };

   emit_event(RUN_WHOLE_EXAMPLE_PROGRAM);
}
