#include <Projekt.h>

#include "projekt_helper.h"

#include <fstream>
#include <streambuf>

#define GIT_DIFF_COMMAND "(d) git diff"
#define GIT_STATUS_COMMAND "(s) git status"
#define GIT_LOG_COMMAND "(l) git log"
#define QUIT_COMMAND "(q) quit"
#define LOAD_FILE_COMMAND "   load_file"

Projekt::Projekt()
{
   current_project = this;

   elements.push_back(new Menu(1, 3, {
      GIT_DIFF_COMMAND,
      GIT_STATUS_COMMAND,
      GIT_LOG_COMMAND,
      QUIT_COMMAND,
   }));
   last_element().set_name("main_menu");

   elements.push_back(new Text("[ output text empty ]", 0, 10));
   last_element().set_name("body_text");
}

bool Projekt::process_input(char input_ch)
{
   switch(input_ch)
   {
   case 'j': emit_event(MOVE_CURSOR_DOWN); break;
   case 'k': emit_event(MOVE_CURSOR_UP); break;
   case 'q': emit_event(EVENT_ABORT_PROGRAM); break;
   case 10: emit_event(CHOOSE_CURRENT_MENU_ITEM); break;
   default: return false; break;
   }

   return true;
}

bool Projekt::process_event(std::string event)
{
   if (event == MOVE_CURSOR_DOWN) find_menu("main_menu").move_cursor_down();
   else if (event == MOVE_CURSOR_UP) find_menu("main_menu").move_cursor_up();
   else if (event == QUIT_COMMAND) emit_event(EVENT_ABORT_PROGRAM);
   else if (event == CHOOSE_CURRENT_MENU_ITEM)
   {
      std::string selection = find_menu("main_menu").current_selection();
      emit_event(find_menu("main_menu").current_selection());
   }
   else if (event == GIT_DIFF_COMMAND)
   {
      std::stringstream ss;
      ss << "git diff > \"" << TMP_OUTFILE << "\"";
      system(ss.str().c_str());
      emit_event(LOAD_FILE_COMMAND);
   }
   else if (event == GIT_STATUS_COMMAND)
   {
      system("git status > \"out.tmp\"");
      emit_event(LOAD_FILE_COMMAND);
   }
   else if (event == GIT_LOG_COMMAND)
   {
      std::stringstream ss;
      ss << "git log --pretty=tformat:'\''%an%x09%ad%x09%C(yellow)%h%Creset%x09%s'\'' --date=format:'\''%Y-%m-%d %H:%M:%S'\'' -12 > \"" << TMP_OUTFILE << "\"";
      system(ss.str().c_str());
      emit_event(LOAD_FILE_COMMAND);
   }
   else if (event == LOAD_FILE_COMMAND)
   {
      find_text("body_text").set_text(get_file_contents());
   }

   return true;
}
