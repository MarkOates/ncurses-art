#include <Projekt.h>

#include <iostream>

#include <cstdlib>

#include <ncurses.h>

#include "projekt_helper.h"

#define SET_COMMIT_LOG_MENU "set_commit_log_menu"
#define SET_DIFF_TEXT "set_diff_text"
#define COPY_CURRENT_HASH_TO_CLIPBOARD "copy_current_hash_to_clipboard"

void set_commit_log_menu()
{
   system("git log --pretty=tformat:'\''%an%x09%ad%x09%C(yellow)%h%Creset%x09%s'\'' --date=format:'\''%Y-%m-%d %H:%M:%S'\'' -100 > \"out.tmp\"");
   std::string txt = get_file_contents();
   std::vector<std::string> tokens = split_string(txt, "\n");
   find_text("body_text").set_text(tokens[0]);
   find_menu("main_menu").set_options(tokens);
}

Projekt::Projekt()
{
   current_project = this;

   init_color(20, 0, (int)(255.0/255.0*1000), (int)(175.0/255.0*1000));

   init_pair(1, COLOR_BLACK, 20);

   elements.push_back(new Text("[ output text empty ]", 0, 5));
   last_element().set_name("body_text");

   elements.push_back(new Menu(100, 5, { "[ menu empty ]" }));
   last_menu().set_styles(COLOR_PAIR(1));
   last_element().set_name("main_menu");

   set_commit_log_menu();
}

bool Projekt::process_input(char input_ch)
{
   switch(input_ch)
   {
   case 'j': emit_event(MOVE_CURSOR_DOWN); break;
   case 'k': emit_event(MOVE_CURSOR_UP); break;
   case 'q': emit_event(EVENT_ABORT_PROGRAM); break;
   case 'y': emit_event(COPY_CURRENT_HASH_TO_CLIPBOARD); break;
   case 10: emit_event(CHOOSE_CURRENT_MENU_ITEM); break;
   default: return false; break;
   }

   return true;
}

bool Projekt::process_event(std::string event)
{
   if (event == MOVE_CURSOR_DOWN)
   {
      find_menu("main_menu").move_cursor_down();
      emit_event(SET_DIFF_TEXT);
   }
   else if (event == MOVE_CURSOR_UP)
   {
      find_menu("main_menu").move_cursor_up();
      emit_event(SET_DIFF_TEXT);
   }
   else if (event == COPY_CURRENT_HASH_TO_CLIPBOARD)
   {
      std::string selection_text = find_menu("main_menu").current_selection();
      auto git_line_tokens = split_string(selection_text, "\t");

      std::stringstream command;
      command << "echo " << git_line_tokens[2] << " | pbcopy";
      system(command.str().c_str());
   }
   else if (event == SET_DIFF_TEXT)
   {
      std::string selection_text = find_menu("main_menu").current_selection();
      auto git_line_tokens = split_string(selection_text, "\t");

      std::stringstream command;
      command << "git show " << git_line_tokens[2] << " > \"out.tmp\"";
      system(command.str().c_str());

      std::string command_output = get_file_contents();
      find_text("body_text").set_text(command_output);
   }
   else if (event == SET_COMMIT_LOG_MENU)
   {
      set_commit_log_menu();
   }

   return true;
}
