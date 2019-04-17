#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>

#define BUILD_COMMAND_MENU "command_build_menu"
#define YANK_SELECTED_TEXT "yank_selected_text"
#define YANK_OPEN_COMMAND "yank_open_command"

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
   }
};



Projekt::Projekt() { current_project = this; }
bool Projekt::process_input(char ch)
{
   switch(ch)
   {
   case 'j': emit_event(MOVE_CURSOR_DOWN); break;
   case 'k': emit_event(MOVE_CURSOR_UP); break;
   case 'q': emit_event(EVENT_ABORT_PROGRAM); break;
   case 'y': emit_event(YANK_SELECTED_TEXT); break;
   case 'o': emit_event(YANK_OPEN_COMMAND); break;
   default: return false; break;
   }
   return true;
}

bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      init_color(25, (int)(255.0/255.0*1000), (int)(255.0/255.0*1000), (int)(255.0/255.0*1000));
      init_pair(1, COLOR_BLACK, 25);
      create_menu("main_menu").set_styles(COLOR_PAIR(1));

      emit_event(BUILD_COMMAND_MENU);
   }
   if (e == YANK_OPEN_COMMAND)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = trim(menu.current_selection());
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
      std::string trimmed = trim(menu.current_selection());
      std::vector<std::string> tokens = split_string(trimmed, TokenBuilder::DELIMITER);
      if (tokens.size() == 2)
      {
         TokenBuilder token_builder(tokens[0], tokens[1]);
         std::stringstream command;
         command << "printf \"" << token_builder.get_link() << "\" | pbcopy";
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
   else if (e == BUILD_COMMAND_MENU)
   {
      std::vector<std::string> tokens = {
         TokenBuilder("Interview Training", "https://docs.google.com/document/d/1kcREoyed0YBP5gIJot4i6Vs-gjttFFT_V0DNtB5jXaY/edit").build_show_string(),
         "",
         TokenBuilder("Stages of Unicorn Project", "https://vault.shopify.com/gsd#1-the-basics-projects-and-people_projects_project-flows").build_show_string(),
         TokenBuilder("Authme", "https://authme.shopify.io/").build_show_string(),
         TokenBuilder("Kibana", "https://stock-photos-es6-kibana.shopifycloud.com").build_show_string(),
         TokenBuilder("Coaches Corner", "https://session.shopify.io/a/coaching/").build_show_string(),
         TokenBuilder("RnD Levels of Impact", "https://vault.shopify.com/RnD-Titles-and-Levels-of-Impact").build_show_string(),
         "",
         TokenBuilder("Ruby Koans", "http://rubykoans.com/").build_show_string(),
         TokenBuilder("Desk Directory", "https://shopify.officespacesoftware.com/visual-directory").build_show_string(),
         TokenBuilder("League", "https://app.league.com").build_show_string(),
         TokenBuilder("Workday", "https://wd3.myworkday.com/shopify/d/home.htmld").build_show_string(),
         TokenBuilder("Rails Generators", "https://railsguides.net/advanced-rails-model-generators/").build_show_string(),
         "",
         TokenBuilder("Distance to the Frontline", "https://vault.shopify.com/Platform/Distance-to-the-frontline").build_show_string(),
      };
      Menu &menu = find_menu("main_menu");
      menu.set_options(tokens);
      menu.set_x(10);
      menu.set_y(LINES/2 - 3);
   }
   return true;
}
