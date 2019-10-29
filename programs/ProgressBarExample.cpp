#include "Projekt2.h"

#include "unistd.h" // for usleep

#include <iostream>

#define RUN_WHOLE_EXAMPLE_PROGRAM "run whole example program"
#define SET_TEXT "set_text"
#define INCREMENT_PROGRESS_BAR "increment progress bar"
#define SLEEP_THEN_ABORT "sleep then abort"

void initialize()
{
   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);

   //create_text("text", 10, 20);
   create_progress_bar("progress_bar", 6, 20, 40, 3);//.set_styles(COLOR_PAIR(3));
   create_frame("frame", 6, 30, 40, 3);//.set_styles(COLOR_PAIR(3));
   create_text_input("text_input", 6, 50);//.set_styles(COLOR_PAIR(3));

   mappings['s'] = SET_TEXT;
   mappings[' '] = EVENT_ABORT_PROGRAM;

   events[RUN_WHOLE_EXAMPLE_PROGRAM] = []{
      //emit_event(SET_TEXT);
      emit_event(INCREMENT_PROGRESS_BAR);
   };
   events[SET_TEXT] = []{
      find_text("text").set_text("Hello world!");
   };
   events[SLEEP_THEN_ABORT] = []{
      usleep(2000000);
      emit_event(EVENT_ABORT_PROGRAM);
   };
   events[INCREMENT_PROGRESS_BAR] = []{
      ProgressBar &progress_bar = find_progress_bar("progress_bar");
      float progress_bar_value = progress_bar.get_value();
      progress_bar.set_value(progress_bar_value + 0.01);
      usleep(20000);

      if (progress_bar.get_value() >= 1.0)
      {
         progress_bar.set_value(1.0);
         emit_event(SLEEP_THEN_ABORT);
      }
      else
      {
         emit_event(INCREMENT_PROGRESS_BAR);
      }
   };

   emit_event(RUN_WHOLE_EXAMPLE_PROGRAM);
}
