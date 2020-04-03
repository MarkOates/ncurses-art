#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>
#include <algorithm> // for sd::find_if

#define BUILD_COMMAND_MENU "command_build_menu"
#define JUMP_TO_NEXT_SECTION "JUMP_TO_NEXT_SECTION"
#define YANK_SELECTED_TEXT "yank_selected_text"
#define YANK_OPEN_COMMAND "yank_open_command"

#include <Blast/String/Trimmer.hpp>

// replace characters in a string
void ___replace(std::string& str, std::string from, std::string to)
{
   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
}



class TokenBuilder
{
private:
   std::string title;
   std::string link;

public:
   static const std::string DELIMITER;

   TokenBuilder(std::string title, std::string link)
      : title(title)
      , link(link)
   {}

   std::string get_link() { return link; }
   std::string get_title() { return title; }

   std::string build_show_string() { return title + DELIMITER + link; }
};
const std::string TokenBuilder::DELIMITER = " - ";


class TokenExtractor
{
private:
   std::string string;

public:
   TokenExtractor(std::string string)
      : string(string)
   {}

   std::string infer_link()
   {
      // TODO
      return "";
   }
};



#include <string>
#include <fstream>
#include <streambuf>

std::string get_file_contents(std::string filename)
{
   std::ifstream t(filename);
   std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
   return str;
}



class FancyList
{
private:
   std::string filename;

public:
   FancyList(std::string filename) : filename(filename) {}
   ~FancyList() {}

   std::vector<std::string> get_tokens()
   {
      std::string file_contents = get_file_contents(filename);
      std::vector<std::string> file_lines = split_string(file_contents, "\n");
      //std::vector<std::string> tokens = {
         //TokenBuilder("Label", "actual value to be copied").build_show_string(),
      //};

      return file_lines;
   }
};



class GitCurrentBranchExtractor
{
private:

public:
   GitCurrentBranchExtractor() {}
   ~GitCurrentBranchExtractor() {}

   std::string get_current_branch()
   {
      std::string get_current_branch_command = "git branch | grep \\* | cut -d ' ' -f2";

      std::stringstream ss;
      ss << get_current_branch_command << " > \"" << TMP_OUTFILE << "\"";
      system(ss.str().c_str());
      std::string txt = get_file_contents();
      std::vector<std::string> tokens = split_string(txt, "\n");

      return tokens[0];
   }
};



bool current_selection_is_header(Menu &menu)
{
   std::string current_selection = menu.current_selection();
   if (current_selection.length() <= 4) return false;
   if (current_selection.substr(0, 4) == "----") return true;
   return false;
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
   case '\t': emit_event(JUMP_TO_NEXT_SECTION); break;
   case 'o': emit_event(YANK_OPEN_COMMAND); break;
   default: return false; break;
   }
   return true;
}

std::string color_theme()
{
   if (args.size() <= 2) return "white";
   return args[2];
}


bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      if (color_theme() == "red")
      {
         init_color(25, (int)(255.0/255.0*1000), 0, 0);
      }
      else
      {
         init_color(25, (int)(255.0/255.0*1000), (int)(255.0/255.0*1000), (int)(255.0/255.0*1000));
      }

      init_pair(1, COLOR_BLACK, 25);
      create_menu("main_menu").set_styles(COLOR_PAIR(1));

      emit_event(BUILD_COMMAND_MENU);
   }
   if (e == YANK_OPEN_COMMAND)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = Blast::String::Trimmer(menu.current_selection()).trim();
      std::vector<std::string> tokens = split_string(trimmed, TokenBuilder::DELIMITER);
      if (tokens.size() == 2)
      {
         TokenBuilder token_builder(tokens[0], tokens[1]);
         std::stringstream command;
         command << "printf \"open " << token_builder.get_link() << "\" | pbcopy";
         system(command.str().c_str());
      }
      else
      {
         std::stringstream error_message;
         error_message << "Cannot extract token from line \"" << trimmed << "\"";
         throw std::runtime_error(error_message.str());
      }
   }
   if (e == YANK_SELECTED_TEXT)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = Blast::String::Trimmer(menu.current_selection()).trim();
      std::vector<std::string> tokens = split_string(trimmed, TokenBuilder::DELIMITER);
      if (tokens.size() == 2)
      {
         TokenBuilder token_builder(tokens[0], tokens[1]);
         std::stringstream command;
         command << "printf \"" << token_builder.get_link() << "\" | pbcopy";
         system(command.str().c_str());
      }
      else if (tokens.size() == 1)
      {
         std::stringstream command;
         command << "printf \"" << tokens[0] << "\" | pbcopy";
         system(command.str().c_str());
      }
      else
      {
         std::stringstream error_message;
         error_message << "Cannot extract token from line \"" << trimmed << "\"";
         throw std::runtime_error(error_message.str());
      }
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
   else if (e == JUMP_TO_NEXT_SECTION)
   {
      Menu &menu = find_menu("main_menu");
      unsigned jump_limit = 100;
      for (unsigned i=0; i<jump_limit; i++)
      {
         menu.set_y(menu.get_y()-1);
         menu.move_cursor_down();
         if (current_selection_is_header(menu)) break;
      }
   }
   else if (e == BUILD_COMMAND_MENU)
   {
      GitCurrentBranchExtractor extractor;
      std::string current_git_branch = extractor.get_current_branch();
      //tokens.push_back(current_git_branch);

      if (args.size() <= 1) std::runtime_error("Yeeeks! There must be an argument, a filename to the list you want to open.");

      FancyList fancy_list(args[1]);
      std::vector<std::string> tokens = fancy_list.get_tokens();

      Menu &menu = find_menu("main_menu");
      menu.set_options(tokens);
      menu.set_x(10);
      menu.set_y(LINES/2 - 3);
   }
   return true;
}
