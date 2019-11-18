//#include <string>
//std::string thing = "find quintessence/**/*.yml"
#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>

#include <iostream>

#include <string>

#include <Blast/ProjectComponentLister.hpp>
#include <ShellCommandExecutorWithCallback.hpp>
#include <StringTrimmer.hpp>
#include <StringSplitter.hpp>

#define COMMAND_FLIP_STAGING "flip_staging"
#define COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU "COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU"
#define COMMAND_REBUILD_ALL_PROJECTS_IN_MENU "COMMAND_REBUILD_ALL_PROJECTS_IN_MENU"
#define REFRESH_TEXT_DISPLAY "refresh_text_display"
#define YANK_SELECTED_TEXT "YANK_SELECTED_TEXT"
#define SAVE_MENU_CONTENTS_TO_FILE "SAVE_MENU_CONTENTS_TO_FILE"
#define BEEBOT_SETUP_BLAST_COMPONENT_COMMAND "BEEBOT_SETUP_BLAST_COMPONENT_COMMAND"
#define SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION "SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION"

#define DELIMITER std::string(" - ")

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

// write string to a file
bool file_put_contents(std::string filename, std::string contents)
{
   std::ofstream file;
   file.open(filename.c_str());
   if (!file.is_open()) return false;
   file << contents.c_str();
   file.close();
   return true;
}


std::vector<std::pair<std::string, std::string>> project_folder_names = {
   { { ".dotfiles" }, {} },
   { { "adventures-of-beary" }, {} },
   { { "AlexPark" }, {} },
   { { "HomeServer" }, {} },
   { { "Slug3D" }, {} },
   { { "allegro-planet" }, {} },
   { { "allegro_flare" }, {} },
   { { "allegroflare.github.io" }, {} },
   { { "beary2d" }, {} },
   { { "beebot" }, {} },
   { { "blast" }, {} },
   //{ { "crayola" }, {} },
   //{ { "crayola-client" }, {} },
   { { "disclife" }, {} },
   { { "dungeon" }, {} },
   { { "first_vim_plugin" }, {} },
   { { "fullscore" }, {} },
   { { "hexagon" }, {} },
   { { "lightracer-max" }, {} },
   { { "me" }, {} },
   { { "motris" }, {} },
   { { "ncurses-art" }, {} },
   { { "oatescodes" }, {} },
   { { "tilemap" }, {} },
   { { "tileo" }, {} },
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
   case 'p': emit_event(COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU); break;
   case 'a': emit_event(COMMAND_REBUILD_ALL_PROJECTS_IN_MENU); break;
   case 's': emit_event(SAVE_MENU_CONTENTS_TO_FILE); break;
   case 'c': emit_event(BEEBOT_SETUP_BLAST_COMPONENT_COMMAND); break;
   default: return false; break;
   }
   return true;
}

bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      init_color(21, (int)(175.0/255.0*1000), (int)(255.0/255.0*1000), 60);
      init_color(22, (int)(96.0/255.0*1000), 0, (int)(128.0/255.0*1000));
      init_color(23, (int)(175.0/255.0*1000), (int)(96.0/255.0*1000), 60);
      init_color(24, 0, 0, 0);
      init_color(25, (int)(96.0/255.0*1000), 60, (int)(255.0/255.0*1000));
      init_pair(1, COLOR_WHITE, 25);
      init_pair(2, COLOR_BLACK, 25);
      init_pair(3, COLOR_BLACK, 21);
      init_pair(4, 24, 22);
      init_pair(5, COLOR_MAGENTA, 23);

      create_menu("main_menu").set_styles(COLOR_PAIR(1));
      create_text("body_text", 80, 3).set_styles(COLOR_PAIR(2));

      Menu &file_preview = create_menu("file_preview", 70, 4);
      file_preview.set_styles(COLOR_PAIR(3));
      file_preview.set_options({ "FILE PREVIEW" });

      emit_event(COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU);
   }
   if (e == YANK_SELECTED_TEXT)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = trim(menu.current_selection());
      std::stringstream command;
      command << "printf \"" << trimmed << "\" | pbcopy";
      system(command.str().c_str());
   }
   else if (e == MOVE_CURSOR_DOWN)
   {
      Menu &menu = find_menu("main_menu");
      //menu.set_y(menu.get_y()-1);
      menu.move_cursor_down();

      emit_event(SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION);
   }
   else if (e == MOVE_CURSOR_UP)
   {
      Menu &menu = find_menu("main_menu");
      //menu.set_y(menu.get_y()+1);
      menu.move_cursor_up();

      emit_event(SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION);
   }
   else if (e == COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU)
   {
      // get the options
      std::vector<std::string> options = { };
      std::string current_directory = StringTrimmer(ShellCommandExecutorWithCallback("pwd").execute()).trim();
      std::vector<std::string> current_project_absolute_directory_components = StringSplitter(current_directory, '/').split();
      std::string current_project_name = current_project_absolute_directory_components.empty() ? "[unidentifiable project directory]" : current_project_absolute_directory_components.back();
      std::string current_project_folder_name = current_directory;
      std::vector<std::pair<std::string, std::string>> project_folder_names = { { { current_project_name }, {} } };

      // extract project components
      for (const auto &project_folder_name : project_folder_names)
      {
         std::string project_folder_name_string = project_folder_name.first;

         //std::string full_folder_name = std::string("/Users/markoates/Repos/") + project_folder_name_string;
         std::string full_folder_name = current_directory + "/";
         Blast::ProjectComponentLister lister(full_folder_name);
         std::vector<std::string> actual_components = lister.components();

         for (auto &actual_component : actual_components)
         {
            std::stringstream text_to_be_displayed_in_menu_option;
            text_to_be_displayed_in_menu_option << project_folder_name_string << DELIMITER << actual_component;

            options.push_back(text_to_be_displayed_in_menu_option.str());
         }
      }

      std::sort(options.begin(), options.end());
      std::vector<std::string>::iterator it = std::unique(options.begin(), options.end());
      options.resize(std::distance(options.begin(), it));

      // fill the options into the menu
      Menu &menu = find_menu("main_menu");
      menu.set_options(options);
      menu.set_x(10);
      menu.set_y(10);
   }
   else if (e == COMMAND_REBUILD_ALL_PROJECTS_IN_MENU)
   {
      // get the options
      std::vector<std::string> options = { };

      // extract project components
      for (const auto &project_folder_name : project_folder_names)
      {
         std::string project_folder_name_string = project_folder_name.first;

         std::string full_folder_name = std::string("/Users/markoates/Repos/") + project_folder_name_string;
         Blast::ProjectComponentLister lister(full_folder_name);
         std::vector<std::string> actual_components = lister.components();

         for (auto &actual_component : actual_components)
         {
            std::stringstream text_to_be_displayed_in_menu_option;
            text_to_be_displayed_in_menu_option << project_folder_name_string << DELIMITER << actual_component;

            options.push_back(text_to_be_displayed_in_menu_option.str());
         }
      }

      std::sort(options.begin(), options.end());
      std::vector<std::string>::iterator it = std::unique(options.begin(), options.end());
      options.resize(std::distance(options.begin(), it));

      // fill the options into the menu
      Menu &menu = find_menu("main_menu");
      menu.set_options(options);
      menu.set_x(10);
      menu.set_y(10);
   }
   if (e == SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION)
   {
      Menu &main_menu = find_menu("main_menu");
      Menu &file_preview = find_menu("file_preview");

      std::string trimmed = StringTrimmer(main_menu.current_selection()).trim();
      std::vector<std::string> tokens = split_string(trimmed, DELIMITER);
      std::string component_name = tokens.empty() ? "[UnextractableComponentName]" : tokens.back();

      file_preview.set_options({ component_name });
   }
   if (e == SAVE_MENU_CONTENTS_TO_FILE)
   {
      Menu &menu = find_menu("main_menu");
      std::vector<std::string> options = menu.get_options();

      std::stringstream result_to_write_to_file;
      for (auto &option : options) { result_to_write_to_file << option << std::endl; }

      file_put_contents("tmp/output_list_of_components.txt", result_to_write_to_file.str());
   }
   if (e == BEEBOT_SETUP_BLAST_COMPONENT_COMMAND)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = trim(menu.current_selection());
      std::stringstream command;
      command << "printf \"ruby ~/Repos/beebot/lib/runner.rb setup_blast_component\" | pbcopy"; // should be replaced with an environment variable and std::getenv
      system(command.str().c_str());
   }
   return true;
}
