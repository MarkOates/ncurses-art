#include "Projekt2.h"

#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE_SCENE "initialize_scene"

void initialize()
{
   mappings['j'] = MOVE_CURSOR_DOWN;
   mappings['k'] = MOVE_CURSOR_UP;
   mappings['h'] = MOVE_CURSOR_LEFT;
   mappings['l'] = MOVE_CURSOR_RIGHT;

   events[INITIALIZE_SCENE] = []{
      Table *table = new Table(10, 20, { {
            "Welcome",
            "Info",
            "Repos",
            "Honey",
         }, {
            "Screen",
            "Panel",
            "ncurses",
            "Badger",
         }, {
            "Rough",
            "Special",
            "Censored",
            "Raster",
         } });
      table->set_name("table");
      current_project->get_elements().push_back(table);
   };
   events[MOVE_CURSOR_UP] = []{
      find_table("table").move_cursor_up();
   };
   events[MOVE_CURSOR_DOWN] = []{
      find_table("table").move_cursor_down();
   };
   events[MOVE_CURSOR_LEFT] = []{
      find_table("table").move_cursor_left();
   };
   events[MOVE_CURSOR_RIGHT] = []{
      find_table("table").move_cursor_right();
   };

   emit_event(INITIALIZE_SCENE);
}


