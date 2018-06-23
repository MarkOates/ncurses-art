#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>

#define COMMAND_FLIP_STAGING "flip_staging"
#define COMMAND_REBUILD_MENU "rebuild_menu"
#define REFRESH_TEXT_DISPLAY "refresh_text_display"
#define YANK_SELECTED_TEXT "YANK_SELECTED_TEXT"
#define GIT_CHECKOUT_BRANCH_COMMAND "GIT_CHECKOUT_BRANCH_COMMAND"
#define COPY_GIT_ADD_PATCH_COMMAND "COPY_GIT_ADD_PATCH_COMMAND"

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
   //return ltrim(rtrim(s));
   //return ltrim(rtrim(s));
   std::string s1 = s;
   std::string s2 = rtrim(s1);
   std::string s3 = ltrim(s2);
   return s3;
}


Projekt::Projekt() { current_project = this; }
bool Projekt::process_input(char ch)
{
   switch(ch)
   {
   case 'j': emit_event(MOVE_CURSOR_DOWN); break;
   case 'k': emit_event(MOVE_CURSOR_UP); break;
   // case 10: emit_event(COMMAND_FLIP_STAGING); break; // ENTER
   case 'q': emit_event(EVENT_ABORT_PROGRAM); break;
   case 'y': emit_event(YANK_SELECTED_TEXT); break;
   case 'c': emit_event(GIT_CHECKOUT_BRANCH_COMMAND); break;
   // case 'p': emit_event(COPY_GIT_ADD_PATCH_COMMAND); break;
   default: return false; break;
   }
   return true;
}

bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      init_color(20, (int)(255.0/255.0*1000), (int)(175.0/255.0*1000), 0);
      //init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
      //init_color(22, (int)(96.0/255.0*1000), 0, (int)(128.0/255.0*1000));
      //init_color(23, (int)(175.0/255.0*1000), 0, (int)(96.0/255.0*1000));
      init_color(24, 0, 0, 0);
      init_pair(1, COLOR_BLACK, 20);
      init_pair(2, COLOR_BLACK, 20);
      init_pair(3, COLOR_BLACK, 21);
      init_pair(4, 24, 22);
      init_pair(5, COLOR_MAGENTA, 23);

      create_menu("main_menu").set_styles(COLOR_PAIR(1));
      create_text("body_text", 80, 3).set_styles(COLOR_PAIR(2));

      emit_event(COMMAND_REBUILD_MENU);
      emit_event(MOVE_CURSOR_DOWN);
   }
   if (e == YANK_SELECTED_TEXT)
   {
      Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      std::string trimmed = trim(menu.current_selection());
      std::stringstream command;
      command << "printf \"" << trimmed << "\" | pbcopy";
      system(command.str().c_str());
   }
   if (e == GIT_CHECKOUT_BRANCH_COMMAND)
   {
      Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      std::string trimmed = trim(menu.current_selection());
      std::stringstream command;
      command << "printf \"git checkout " << trimmed << "\" | pbcopy";
      system(command.str().c_str());
   }
   //if (e == COPY_GIT_ADD_PATCH_COMMAND)
   //{
      //Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      //std::stringstream command;
      //command << "printf \"git add --patch " << git_status_line_deducer.parse_filename() << "\" | pbcopy";
      //system(command.str().c_str());
   //}
   else if (e == MOVE_CURSOR_DOWN)
   {
      Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      //int next_file_line = git_status_line_deducer.find_next_file_line();
      //if (next_file_line != -1) menu.set_cursor_pos(next_file_line);
      //else menu.move_cursor_down();
      menu.set_y(menu.get_y()-1);
      menu.move_cursor_down();
      //emit_event(REFRESH_TEXT_DISPLAY);
   }
   else if (e == MOVE_CURSOR_UP)
   {
      Menu &menu = find_menu("main_menu");
      //GitStatusLineDeducer git_status_line_deducer(menu);
      //int previous_file_line = git_status_line_deducer.find_previous_file_line();
      //if (previous_file_line != -1) menu.set_cursor_pos(previous_file_line);
      //else menu.move_cursor_up();
      menu.set_y(menu.get_y()+1);
      menu.move_cursor_up();
      //emit_event(REFRESH_TEXT_DISPLAY);
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

