#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>

#define BUILD_COMMAND_MENU "command_build_menu"
#define YANK_SELECTED_TEXT "yank_selected_text"

// trim from start
std::string ltrim(std::string &s) {
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
   return s;
}

// trim from end
std::string rtrim(std::string &s) {
   s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
   return s;
}

// trim from both ends
std::string trim(std::string s)
{
   std::string s1 = s;
   std::string s2 = rtrim(s1);
   std::string s3 = ltrim(s2);
   return s3;
}

// replace characters in a string
void ___replace(std::string& str, std::string from, std::string to)
{
   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
}



Projekt::Projekt() { current_project = this; }
bool Projekt::process_input(char ch)
{
   switch(ch)
   {
   case 'j': emit_event(MOVE_CURSOR_DOWN); break;
   case 'k': emit_event(MOVE_CURSOR_UP); break;
   case 'q': emit_event(EVENT_ABORT_PROGRAM); break;
   case 'y': emit_event(YANK_SELECTED_TEXT); break;
   default: return false; break;
   }
   return true;
}

bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      init_color(25, (int)(255.0/255.0*1000), 0, 0);
      init_pair(1, COLOR_BLACK, 25);
      create_menu("main_menu").set_styles(COLOR_PAIR(1));

      emit_event(BUILD_COMMAND_MENU);
   }
   if (e == YANK_SELECTED_TEXT)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = trim(menu.current_selection());
      std::string quite_sanitized = trimmed;
      ___replace(quite_sanitized, "\"", "\\\"");
      std::stringstream command;
      command << "printf \"" << quite_sanitized << "\" | pbcopy";
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
   else if (e == BUILD_COMMAND_MENU)
   {
      std::vector<std::string> tokens = {
         "bin/rails db:migrate",
         "bin/rails db:rollback",
         "bin/rails db:drop db:create db:migrate",
         "bin/rails db:seed",
         "bin/rails generate migration ",
         "",
         "mysql -u root ",
         "",
         "git commit --allow-empty -m \"Kick shipit\"",
         "",
         "git push origin -f name-of-your-branch:staging",
         "",
         "yarn run build",
         "yarn run lint",
         "yarn run test",
         "",
         "ps aux | grep sewing | grep node_modules | awk \"{print $2}\" | xargs kill",
      };
      Menu &menu = find_menu("main_menu");
      menu.set_options(tokens);
      menu.set_x(COLS/2 - menu.get_width()/2);
      menu.set_y(LINES/2 - 3);
   }
   return true;
}
