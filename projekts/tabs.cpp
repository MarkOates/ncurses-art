#include "Projekt2.h"

#define GOTO_NEXT_TAB "goto_next_tab"

void initialize()
{
   TabSet *tab_set = new TabSet(10, 20, {
         "Welcome Screen",
         "Info Panel",
         "Repos/ncurses/main.cpp",
         "Honey Badger",
      });
   tab_set->set_name("tab_set");
   current_project->get_elements().push_back(tab_set);

   mappings['\t'] = GOTO_NEXT_TAB;

   events[GOTO_NEXT_TAB] = []{
      find_tab_set("tab_set").goto_next_tab();
   };
}
