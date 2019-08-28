#include "Projekt2.h"

#define GOTO_NEXT_TAB "goto_next_tab"
#define GOTO_PREVIOUS_TAB "goto_previous_tab"
#define INITIALIZE_SCENE "initialize_scene"

void initialize()
{
   mappings['\t'] = GOTO_NEXT_TAB;
   mappings['h'] = GOTO_PREVIOUS_TAB;
   mappings['l'] = GOTO_NEXT_TAB;

   events[INITIALIZE_SCENE] = []{
      TabSet *tab_set = new TabSet(10, 20, {
            "Welcome Screen",
            "Info Panel",
            "Repos/ncurses/main.cpp",
            "Honey Badger",
         });
      tab_set->set_name("tab_set");
      current_project->get_elements().push_back(tab_set);
   };
   events[GOTO_NEXT_TAB] = []{
      find_tab_set("tab_set").goto_next_tab();
   };
   events[GOTO_PREVIOUS_TAB] = []{
      find_tab_set("tab_set").goto_previous_tab();
   };

   emit_event(INITIALIZE_SCENE);
}


