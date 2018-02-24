#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>

#define COMMAND_FLIP_STAGING "flip_staging"
#define COMMAND_REBUILD_MENU "rebuild_menu"
#define REFRESH_TEXT_DISPLAY "refresh_text_display"
#define YANK_SELECTED_TEXT "YANK_SELECTED_TEXT"

class GitStatusLineDeducer
{
private:
   Menu menu;
   int line_number;
   const std::string CHANGES_TO_BE_COMMITED_LINE = "Changes to be committed:";
   const std::string CHANGES_NOT_STAGED_FOR_COMMIT_LINE = "Changes not staged for commit:";
   const std::string UNTRACKED_FILES_LINE = "Untracked files:";

public:
   GitStatusLineDeducer(Menu menu_dup) : menu(menu_dup), line_number(menu.get_cursor_pos()) {}

   int find_next_file_line()
   {
      int initial_cursor_pos = menu.get_cursor_pos();
      int iterator = initial_cursor_pos + 1;

      for (int i=iterator; i!=initial_cursor_pos; i = (i+1) % menu.get_num_options())
      {
         menu.set_cursor_pos(i);
         if (is_file_line()) return i;
      }

      return -1;
   }

   int find_previous_file_line()
   {
      int initial_cursor_pos = menu.get_cursor_pos();
      int iterator = initial_cursor_pos - 1;

      for (int i=iterator; i!=initial_cursor_pos; i=(i-1+menu.get_num_options()) % menu.get_num_options())
      {
         menu.set_cursor_pos(i);
         if (is_file_line()) return i;
      }

      return -1;
   }

   std::string line()
   {
      return menu.current_selection();
   }

   bool is_file_line()
   {
      return !(line().empty() || line()[0] != '\t');
   }

   bool a_proceeding_line_matches(std::string str, std::vector<std::string> nots = {})
   {
      int traversing_line_number = line_number;
      bool line_matched = false;
      while (traversing_line_number >= 0)
      {
         menu.set_cursor_pos(traversing_line_number);
         traversing_line_number--;

         for (auto &anot : nots) if (menu.current_selection() == anot)
         {
            line_matched = false;
            break;
         }
         if (menu.current_selection() == str)
         {
            line_matched = true;
            break;
         }
      }
      menu.set_cursor_pos(line_number);
      return line_matched;
   }

   bool line_is_staged()
   {
      if (!is_file_line()) return false;
      return a_proceeding_line_matches(CHANGES_TO_BE_COMMITED_LINE, { CHANGES_NOT_STAGED_FOR_COMMIT_LINE, UNTRACKED_FILES_LINE });
   }

   bool line_is_untracked()
   {
      if (!is_file_line()) return false;
      return a_proceeding_line_matches(UNTRACKED_FILES_LINE, { CHANGES_NOT_STAGED_FOR_COMMIT_LINE, CHANGES_TO_BE_COMMITED_LINE });
   }

   bool line_is_not_staged()
   {
      if (!is_file_line()) return false;
      return a_proceeding_line_matches(CHANGES_NOT_STAGED_FOR_COMMIT_LINE, { CHANGES_TO_BE_COMMITED_LINE, UNTRACKED_FILES_LINE });
   }

   std::string parse_directive()
   {
      if (!is_file_line()) return "";
      std::vector<std::string> tokens = split_string(line(), " ");
      std::string possible_directive_string = tokens.front();
      if (possible_directive_string.back() != ':') return "";
      // erase the first and last characters
      return possible_directive_string.substr(1, possible_directive_string.size() - 2);
   }

   std::string parse_filename()
   {
      if (!is_file_line()) return "";
      std::vector<std::string> tokens = split_string(line(), " ");
      std::string untrimmed = tokens.back();
      return untrimmed.substr(
            untrimmed.find_first_not_of('\t'),
            (untrimmed.find_last_not_of('\t') - untrimmed.find_first_not_of('\t')) + 1
         );
   }
};

Projekt::Projekt() { current_project = this; }
bool Projekt::process_input(char ch)
{
   switch(ch)
   {
   case 'j': emit_event(MOVE_CURSOR_DOWN); break;
   case 'k': emit_event(MOVE_CURSOR_UP); break;
   case 10: emit_event(COMMAND_FLIP_STAGING); break;
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
      create_menu("main_menu").set_styles(COLOR_PAIR(1));
      create_text("body_text", 80, 3).set_styles(COLOR_PAIR(2));

      emit_event(COMMAND_REBUILD_MENU);
      emit_event(MOVE_CURSOR_DOWN);
   }
   if (e == YANK_SELECTED_TEXT)
   {
      Menu &menu = find_menu("main_menu");
      GitStatusLineDeducer git_status_line_deducer(menu);
      std::stringstream command;
      command << "printf \"" << git_status_line_deducer.parse_filename() << "\" | pbcopy";
      system(command.str().c_str());
   }
   else if (e == REFRESH_TEXT_DISPLAY)
   {
      Menu &menu = find_menu("main_menu");
      GitStatusLineDeducer git_status_line_deducer(menu);
      std::stringstream system_command;
      Text &text = find_text("body_text");

      if (git_status_line_deducer.is_file_line())
      {
         std::string filename = git_status_line_deducer.parse_filename();

         if (git_status_line_deducer.line_is_untracked())
         {
            text.set_styles(COLOR_PAIR(5));
            system_command << "cat \"" << filename << "\" > \"" << TMP_OUTFILE << "\"";
         }
         else if (git_status_line_deducer.line_is_not_staged())
         {
            text.set_styles(COLOR_PAIR(4));
            system_command << "git diff \"" << filename << "\" > \"" << TMP_OUTFILE << "\"";
         }
         else if (git_status_line_deducer.line_is_staged())
         {
            text.set_styles(COLOR_PAIR(3));
            system_command << "git diff --staged \"" << filename << "\" > \"" << TMP_OUTFILE << "\"";
         }
      }
      else
      {
         text.set_styles(COLOR_PAIR(2));
         system_command << "git diff --staged > \"" << TMP_OUTFILE << "\"";
      }

      system(system_command.str().c_str());

      std::string command_output = get_file_contents();
      text.set_text(command_output);
   }
   else if (e == MOVE_CURSOR_DOWN)
   {
      Menu &menu = find_menu("main_menu");
      GitStatusLineDeducer git_status_line_deducer(menu);
      int next_file_line = git_status_line_deducer.find_next_file_line();
      if (next_file_line != -1) menu.set_cursor_pos(next_file_line);
      else menu.move_cursor_down();
      emit_event(REFRESH_TEXT_DISPLAY);
   }
   else if (e == MOVE_CURSOR_UP)
   {
      Menu &menu = find_menu("main_menu");
      GitStatusLineDeducer git_status_line_deducer(menu);
      int previous_file_line = git_status_line_deducer.find_previous_file_line();
      if (previous_file_line != -1) menu.set_cursor_pos(previous_file_line);
      else menu.move_cursor_up();
      emit_event(REFRESH_TEXT_DISPLAY);
   }
   else if (e == COMMAND_FLIP_STAGING)
   {
      Menu &menu = find_menu("main_menu");
      std::string current_selection = menu.current_selection();
      std::vector<std::string> line_tokens = split_string(current_selection, " ");

      GitStatusLineDeducer git_status_line_deducer(menu);

      if (git_status_line_deducer.is_file_line())
      {
         if (git_status_line_deducer.line_is_not_staged() || git_status_line_deducer.line_is_untracked())
         {
            std::stringstream system_command;
            system_command << "git add " << git_status_line_deducer.parse_filename();
            system_command << " > /dev/null";
            system(system_command.str().c_str());
            emit_event(COMMAND_REBUILD_MENU);
         }
         else
         {
            std::stringstream system_command;
            system_command << "git reset " << git_status_line_deducer.parse_filename();
            system_command << " > /dev/null";
            system(system_command.str().c_str());
            emit_event(COMMAND_REBUILD_MENU);
         }
      }

      //std::ofstream ofs("asdf.txt");
      //ofs
         //<< "staged: " << git_status_line_deducer.line_is_staged() << std::endl
         //<< "untracked: " << git_status_line_deducer.line_is_untracked() << std::endl
         //<< "not_staged: " << git_status_line_deducer.line_is_not_staged() << std::endl
         //<< git_status_line_deducer.is_file_line() << std::endl
         //<< git_status_line_deducer.is_file_line() << std::endl
         //<< git_status_line_deducer.parse_directive() << std::endl
         //<< git_status_line_deducer.parse_filename() << std::endl;
      //ofs.close();
      //throwit("COMMAND_FLIP_STAGING not supported yet");
   }
   else if (e == COMMAND_REBUILD_MENU)
   {
      std::stringstream ss;
      ss << "git status > \"" << TMP_OUTFILE << "\"";
      system(ss.str().c_str());
      std::string txt = get_file_contents();
      std::vector<std::string> tokens = split_string(txt, "\n");
      find_menu("main_menu").set_options(tokens);
   }
   return true;
}
