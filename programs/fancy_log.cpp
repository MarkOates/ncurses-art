#include <Projekt.h>

#include <iostream>

#include <cstdlib>

#include <ncurses.h>

#include "projekt_helper.h"

#define MENU_OUT_POS (COLS-80)
#define MENU_DOCKED_POS (COLS-40)


static std::string COMMIT_HASH = "%H";
static std::string ABBREVIATED_COMMIT_HASH = "%h";
static std::string AUTHOR_NAME = "%an";
static std::string AUTHOR_DATE = "%ad";
static std::string SUBJECT = "%s";

static std::string DELIMITER = "%x09"; // 09 is the tab character
static std::string DELIMITER_CHAR = "\t"; // 09 is the tab character

class GitLogFormat
{
private:
   std::vector<std::string> format_components;

public:
   GitLogFormat(std::vector<std::string> format_components)
      : format_components(format_components)
   {}

   std::string command(unsigned limit = 100)
   {
      std::stringstream ss;
      //ss << "git log --pretty=tformat:'\''%an%x09%ad%x09%C(yellow)%h%Creset%x09%s'\'' --date=format:'\''%Y-%m-%d %H:%M:%S'\'' -100 > \"" << TMP_OUTFILE << "\"";
      ss << "git log --pretty=tformat:'\''";
      for (auto &format_component : format_components)
         ss << format_component << DELIMITER;
      ss << "'\'' ";
      //ss << " --date=format:'\''%Y-%m-%d %H:%M:%S'\''";
      ss << " --date=relative";
      ss << " -" << limit;

      return ss.str();

      //%an%x09%ad%x09%C(yellow)%h%Creset%x09%s'\'' --date=format:'\''%Y-%m-%d %H:%M:%S'\'' -100 > \"" << TMP_OUTFILE << "\"";
   }
   std::string extract_component(std::string line, std::string component_identifier)
   {
      int index = -1;
      for (int i=0; i<format_components.size(); i++)
         if (format_components[i] == component_identifier)
         {
            index = i;
            break;
         }

      if (index == -1) throw std::runtime_error("GitLogFormat::extract_component(): expected component for extraction is not present");

      auto git_line_tokens = split_string(line, DELIMITER_CHAR);

      if (index >= git_line_tokens.size()) throw std::runtime_error("GitLogFormat::extract_component(): number of extracted tokens does not match the expected position");

      return git_line_tokens[index];
   }
};


#define SET_COMMIT_LOG_MENU "set_commit_log_menu"
#define SET_DIFF_TEXT "set_diff_text"
#define COPY_CURRENT_HASH_TO_CLIPBOARD "copy_current_hash_to_clipboard"
#define COPY_GIT_DIFF_TREE_COMMAND_TO_CLIPBOARD "copy_GIT_DIFF_TREE_COMMAND_TO_CLIPBOARD"
#define COPY_INTERACTIVE_REBASE_COMMAND "copy_interactive_rebase_command"
#define COPY_FANCY_FIXUP_COMMAND "copy_fancy_fixup_command"
#define TOGGLE_MENU_PLACEMENT "toggle_menu_placement"
#define COPY_FILES_COMMAND "copy_files_command"




//GitLogFormat git_log_format({ AUTHOR_NAME, AUTHOR_DATE, ABBREVIATED_COMMIT_HASH, SUBJECT });
GitLogFormat git_log_format({ ABBREVIATED_COMMIT_HASH, SUBJECT });


void set_commit_log_menu()
{
   std::stringstream ss;
   //ss << "git log --pretty=tformat:'\''%an%x09%ad%x09%C(yellow)%h%Creset%x09%s'\'' --date=format:'\''%Y-%m-%d %H:%M:%S'\'' -100 > \"" << TMP_OUTFILE << "\"";
   ss << git_log_format.command() << " > \"" << TMP_OUTFILE << "\"";
   system(ss.str().c_str());
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

   elements.push_back(new Text("[ output text empty ]", 0, 0));
   last_element().set_name("body_text");

   elements.push_back(new Menu(MENU_OUT_POS, 1, { "[ menu empty ]" }));
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
   case 'd': emit_event(COPY_GIT_DIFF_TREE_COMMAND_TO_CLIPBOARD); break;
   case 'r': emit_event(COPY_INTERACTIVE_REBASE_COMMAND); break;
   case 'f': emit_event(COPY_FANCY_FIXUP_COMMAND); break;
   case 'i': emit_event(COPY_FILES_COMMAND); break;
   case 10: emit_event(CHOOSE_CURRENT_MENU_ITEM); break;
   case '\t': emit_event(TOGGLE_MENU_PLACEMENT); break;
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
      std::string command_token = git_log_format.extract_component(selection_text, ABBREVIATED_COMMIT_HASH);
      std::stringstream command;

      command << "printf \"" << command_token << "\" | pbcopy";
      system(command.str().c_str());
   }
   else if (event == COPY_GIT_DIFF_TREE_COMMAND_TO_CLIPBOARD)
   {
      std::string selection_text = find_menu("main_menu").current_selection();
      std::string command_token = git_log_format.extract_component(selection_text, ABBREVIATED_COMMIT_HASH);
      std::stringstream command;

      command << "printf \"git diff-tree " << command_token << "\" | pbcopy";
      system(command.str().c_str());
   }
   else if (event == COPY_INTERACTIVE_REBASE_COMMAND)
   {
      std::string selection_text = find_menu("main_menu").current_selection();
      std::string command_token = git_log_format.extract_component(selection_text, ABBREVIATED_COMMIT_HASH);
      std::stringstream command;

      command << "printf \"git rebase -i " << command_token << "~\" | pbcopy";
      system(command.str().c_str());
   }
   else if (event == COPY_FANCY_FIXUP_COMMAND)
   {
      std::string selection_text = find_menu("main_menu").current_selection();
      std::string command_token = git_log_format.extract_component(selection_text, ABBREVIATED_COMMIT_HASH);
      std::stringstream command;

      command << "printf \"git_fixup " << command_token << "\" | pbcopy";
      system(command.str().c_str());
   }
   else if (event == TOGGLE_MENU_PLACEMENT)
   {
      Menu &menu = find_menu("main_menu");
      if (menu.get_x() == MENU_OUT_POS) menu.set_x(MENU_DOCKED_POS);
      else menu.set_x(MENU_OUT_POS);
   }
   else if (event == COPY_FILES_COMMAND)
   {
      std::string selection_text = find_menu("main_menu").current_selection();
      std::string command_token = git_log_format.extract_component(selection_text, ABBREVIATED_COMMIT_HASH);
      std::stringstream command;

      command << "git diff-tree --no-commit-id --name-only -r " << command_token << " > \"" << TMP_OUTFILE << "\"";
      system(command.str().c_str());

      std::string command_output = get_file_contents();
      find_text("body_text").set_text(command_output);
   }
   else if (event == SET_DIFF_TEXT)
   {
      std::string selection_text = find_menu("main_menu").current_selection();
      std::string command_token = git_log_format.extract_component(selection_text, ABBREVIATED_COMMIT_HASH);
      std::stringstream command;

      command << "git show " << command_token << " > \"" << TMP_OUTFILE << "\"";
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
