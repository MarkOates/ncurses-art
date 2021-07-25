#include "Projekt2.h"

#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE "INITIALIZE"


#include <functional>

class Program
{
private:
   std::map<std::string, std::function<void(Program&)>> actions;

public:
   Program() : actions(Program::build_default_actions()) {}
   ~Program() {}

   void process_event(std::string event_name)
   {
   }

   void initialize()
   {
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
   }

   void move_cursor_up()
   {
      find_table("table").move_cursor_up();
   }

   void move_cursor_down()
   {
      find_table("table").move_cursor_down();
   }

   void move_cursor_left()
   {
      find_table("table").move_cursor_left();
   }

   void move_cursor_right()
   {
      find_table("table").move_cursor_right();
   }

   static std::map<std::string, std::function<void(Program&)>> build_default_actions()
   {
      std::map<std::string, std::function<void(Program&)>> result;
      result = {
         { INITIALIZE, &Program::initialize },
         { MOVE_CURSOR_UP, &Program::move_cursor_up },
         { MOVE_CURSOR_DOWN, &Program::move_cursor_down },
         { MOVE_CURSOR_LEFT, &Program::move_cursor_left },
         { MOVE_CURSOR_RIGHT, &Program::move_cursor_right },
      };
      return result;
   }
};


Program program;


void initialize()
{
   mappings['j'] = MOVE_CURSOR_DOWN;
   mappings['k'] = MOVE_CURSOR_UP;
   mappings['h'] = MOVE_CURSOR_LEFT;
   mappings['l'] = MOVE_CURSOR_RIGHT;

   events[INITIALIZE] = []{
      program.initialize();
   };
   events[MOVE_CURSOR_UP] = []{
      program.move_cursor_up();
   };
   events[MOVE_CURSOR_DOWN] = []{
      program.move_cursor_down();
   };
   events[MOVE_CURSOR_LEFT] = []{
      program.move_cursor_left();
   };
   events[MOVE_CURSOR_RIGHT] = []{
      program.move_cursor_right();
   };

   emit_event(INITIALIZE);
}


