#include <Projekt.h>
#include "projekt_helper.h"
#include <algorithm> // for std::find_if

#include <ncurses.h>

#define COMMAND_FLIP_STAGING "flip_staging"
#define COMMAND_REBUILD_MENU "rebuild_menu"
#define REFRESH_TEXT_DISPLAY "refresh_text_display"
#define YANK_SELECTED_TEXT "YANK_SELECTED_TEXT"
#define GIT_CHECKOUT_BRANCH_COMMAND "GIT_CHECKOUT_BRANCH_COMMAND"
#define GIT_DELETE_BRANCH_COMMAND "GIT_DELETE_BRANCH_COMMAND"
#define COPY_GIT_ADD_PATCH_COMMAND "COPY_GIT_ADD_PATCH_COMMAND"


#include <Blast/String/Trimmer.hpp>


Projekt::Projekt() { current_project = this; }
bool Projekt::process_input(char ch)
{
   switch(ch)
   {
   case 'j': emit_event(MOVE_CURSOR_DOWN); break;
   case 'k': emit_event(MOVE_CURSOR_UP); break;
   case 'q': emit_event(EVENT_ABORT_PROGRAM); break;
   case 'y': emit_event(YANK_SELECTED_TEXT); break;
   case 'c': emit_event(GIT_CHECKOUT_BRANCH_COMMAND); break;
   case 'd': emit_event(GIT_DELETE_BRANCH_COMMAND); break;
   default: return false; break;
   }
   return true;
}

bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
      init_color(22, (int)(96.0/255.0*1000), 0, (int)(128.0/255.0*1000));
      init_color(23, (int)(175.0/255.0*1000), 0, (int)(96.0/255.0*1000));
      init_color(24, 0, 0, 0);
      init_color(25, (int)(96.0/255.0*1000), 0, (int)(255.0/255.0*1000));
      init_pair(1, COLOR_BLACK, 25);
      init_pair(2, COLOR_BLACK, 25);
      init_pair(3, COLOR_BLACK, 21);
      init_pair(4, 24, 22);
      init_pair(5, COLOR_MAGENTA, 23);

      create_menu("main_menu").set_styles(COLOR_PAIR(1));
      create_text("body_text", 80, 3).set_styles(COLOR_PAIR(2));

      emit_event(COMMAND_REBUILD_MENU);
   }
   if (e == YANK_SELECTED_TEXT)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = Blast::String::Trimmer(menu.current_selection()).trim();
      std::stringstream command;
      command << "printf \"" << trimmed << "\" | pbcopy";
      system(command.str().c_str());
   }
   if (e == GIT_CHECKOUT_BRANCH_COMMAND)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = Blast::String::Trimmer(menu.current_selection()).trim();
      std::stringstream command;
      command << "printf \"git checkout " << trimmed << "\" | pbcopy";
      system(command.str().c_str());
   }
   if (e == GIT_DELETE_BRANCH_COMMAND)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = Blast::String::Trimmer(menu.current_selection()).trim();
      std::stringstream command;
      command << "printf \"git branch -d " << trimmed << "\" | pbcopy";
      system(command.str().c_str());
   }
   else if (e == MOVE_CURSOR_DOWN)
   {
      Menu &menu = find_menu("main_menu");
      menu.set_y(menu.get_y()-1);
      menu.move_cursor_down();
   }
   else if (e == MOVE_CURSOR_UP)
   {
      Menu &menu = find_menu("main_menu");
      menu.set_y(menu.get_y()+1);
      menu.move_cursor_up();
   }
   else if (e == COMMAND_REBUILD_MENU)
   {
      std::stringstream ss;
      ss << "git branch --sort=-committerdate > \"" << TMP_OUTFILE << "\"";
      system(ss.str().c_str());
      std::string txt = get_file_contents();
      std::vector<std::string> tokens = split_string(txt, "\n");
      Menu &menu = find_menu("main_menu");
      menu.set_options(tokens);
      menu.set_x(COLS/2 - menu.get_width()/2);
      menu.set_y(LINES/2 - 3);
   }
   return true;
}
