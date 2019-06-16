#include <Projekt.h>
#include "projekt_helper.h"

#include <map>

#include <ncurses.h>

// actions
#define REFRESH_TEXT_DISPLAY "refresh_text_display"
#define BUILD_MENU "build_menu"

// constants
#define PROJECT_MENU "project_menu"


std::map<char, std::string> command_mapping = {
   { 'j', MOVE_CURSOR_DOWN },
   { 'k', MOVE_CURSOR_UP },
   { 'q', EVENT_ABORT_PROGRAM },
};


Projekt::Projekt() { current_project = this; }
bool Projekt::process_input(char ch)
{
   auto found = command_mapping.find(ch);
   if (found == command_mapping.end()) return false;
   emit_event(found->second);
   return true;
}
bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      init_color(20, (int)(255.0/255.0*1000), 0, (int)(175.0/255.0*1000));
      init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
      init_color(22, (int)(96.0/255.0*1000), 0, (int)(128.0/255.0*1000));
      init_color(23, (int)(175.0/255.0*1000), 0, (int)(96.0/255.0*1000));
      init_color(24, 0, 0, 0);
      init_pair(1, 20, COLOR_BLACK);
      init_pair(2, COLOR_BLACK, 20);
      init_pair(3, COLOR_BLACK, 21);
      init_pair(4, 24, 22);
      init_pair(5, COLOR_MAGENTA, 23);
      create_menu(PROJECT_MENU).set_styles(COLOR_PAIR(1));
      create_text("body_text", 80, 3).set_styles(COLOR_PAIR(2));
      create_text("command_list_text", 130, 20, 0.0, 1.0).set_styles(COLOR_PAIR(5));

      emit_event(BUILD_MENU);
   }
   else if (e == BUILD_MENU)
   {
      std::vector<std::string> options = {
         "option 1",
         "option 2",
         "option 3",
      };
      Menu &menu = find_menu(PROJECT_MENU);
      menu.set_options(options);
   }
   else if (e == MOVE_CURSOR_DOWN)
   {
      Menu &menu = find_menu(PROJECT_MENU);
      menu.move_cursor_down();
   }
   else if (e == MOVE_CURSOR_UP)
   {
      Menu &menu = find_menu(PROJECT_MENU);
      menu.move_cursor_up();
   }
   else
   {
      std::stringstream error_message;
      error_message << "Command not found: \"" << e << "\".";
      throw std::runtime_error(error_message.str());
   }
   return true;
}
