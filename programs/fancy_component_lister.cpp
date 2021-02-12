//#include <string>
//std::string thing = "find quintessence/**/*.yml"
#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>

#include <iostream>
#include <algorithm> // for std::sort and std::unique

#include <string>

#include <Blast/Project/ComponentLister.hpp>
#include <Blast/Project/Component.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <ProjectFilenameGenerator.hpp>
#include <Blast/String/Trimmer.hpp>
#include <StringSplitter.hpp>

#define COMMAND_MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define COMMAND_MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define COMMAND_ABORT_PROGRAM "ABORT_PROGRAM"
#define COMMAND_FLIP_STAGING "FLIP_STAGING"
#define COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU "COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU"
#define COMMAND_REBUILD_ALL_PROJECTS_IN_MENU "COMMAND_REBUILD_ALL_PROJECTS_IN_MENU"
#define COMMAND_BUILD_COMMAND_LIST "BUILD_COMMAND_LIST"
#define COMMAND_REFRESH_TEXT_DISPLAY "REFRESH_TEXT_DISPLAY"
#define COMMAND_YANK_SELECTED_TEXT "YANK_SELECTED_TEXT"
#define COMMAND_SAVE_MENU_CONTENTS_TO_FILE "SAVE_MENU_CONTENTS_TO_FILE"
#define COMMAND_BEEBOT_SETUP_BLAST_COMPONENT_COMMAND "BEEBOT_SETUP_BLAST_COMPONENT_COMMAND"
#define COMMAND_SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION "SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION"
#define COMMAND_TOGGLE_MENU_MOVING_WITH_CURSOR "TOGGLE_MENU_MOVING_WITH_CURSOR"
#define COMMAND_RERUN_MAKE_WITH_COMPONENT_AS_FOCUS "COMMAND_RERUN_MAKE_WITH_COMPONENT_AS_FOCUS"

#define DELIMITER std::string(" - ")

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

// obtain the contents of a file
std::string file_get_contents(std::string filename, bool raise_on_missing_file=true)
{
   std::ifstream file(filename.c_str());
   std::string input = "";
   if (!file)
   {
      if (raise_on_missing_file)
      {
         std::stringstream error_message;
         error_message << "Attempting to open file \"" << filename << "\" but it was not found." << std::endl;
         throw std::runtime_error(error_message.str());
      }
      else
      {
         return "";
      }
   }
   char ch;
   while (file.get(ch)) input.append(1, ch);
   if (!file.eof()) return ""; // strange error
   file.close();
   return input;
}


bool menu_is_moving_with_cursor = false;


std::vector<std::pair<std::string, std::string>> project_folder_names = {
   { { ".dotfiles" }, {} },
   { { "adventures-of-beary" }, {} },
   { { "AlexPark" }, {} },
   { { "HomeServer" }, {} },
   { { "DragonWrath" }, {} },
   { { "LabyrinthOfLore" }, {} },
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


std::string extract_component_from_menu_option(std::string text_to_extract_token)
{
   std::string trimmed = Blast::String::Trimmer(text_to_extract_token).trim();
   std::vector<std::string> tokens = split_string(trimmed, DELIMITER);
   std::string component_name = tokens.empty() ? "[UnextractableComponentName]" : tokens.back();
   return component_name;
}


#include <map>

std::map<char, std::string> command_mapping = {
   { 'j', COMMAND_MOVE_CURSOR_DOWN },
   { 'k', COMMAND_MOVE_CURSOR_UP },
   { 'q', COMMAND_ABORT_PROGRAM },
   { 'y', COMMAND_YANK_SELECTED_TEXT },
   { 'p', COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU },
   { 'f', COMMAND_RERUN_MAKE_WITH_COMPONENT_AS_FOCUS },
   { 'a', COMMAND_REBUILD_ALL_PROJECTS_IN_MENU },
   { 's', COMMAND_SAVE_MENU_CONTENTS_TO_FILE },
   { 'c', COMMAND_BEEBOT_SETUP_BLAST_COMPONENT_COMMAND },
   { 'm', COMMAND_TOGGLE_MENU_MOVING_WITH_CURSOR },
};


std::string compose_command_mapping_text(std::map<char, std::string> &command_mapping)
{
   std::stringstream result;
   for (auto &command_map : command_mapping)
   {
      result
         << command_map.first
         << " - "
         << command_map.second
         << std::endl;
         ;
   }
   return result.str();
}


Projekt::Projekt() { current_project = this; }
bool Projekt::process_input(char ch)
{
   auto found = command_mapping.find(ch);
   if (found == command_mapping.end()) return false;
   emit_event(found->second);
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
      init_pair(6, 21, COLOR_BLACK);

      // layout
      create_menu("main_menu").set_styles(COLOR_PAIR(1));
      create_text("body_text", 80, 3).set_styles(COLOR_PAIR(2));

      Menu &file_preview = create_menu("file_preview", 70, 4);
      file_preview.set_styles(COLOR_PAIR(6));
      file_preview.set_options({ "FILE PREVIEW" });

      create_text("command_list_text", 170, 4).set_styles(COLOR_PAIR(5));

      // initial events
      emit_event(COMMAND_BUILD_COMMAND_LIST);
      emit_event(COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU);
   }
   if (e == COMMAND_YANK_SELECTED_TEXT)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = Blast::String::Trimmer(menu.current_selection()).trim();
      std::stringstream command;
      command << "printf \"" << trimmed << "\" | pbcopy";
      system(command.str().c_str());
   }
   else if (e == COMMAND_MOVE_CURSOR_DOWN)
   {
      Menu &menu = find_menu("main_menu");
      menu.move_cursor_down();
      if (menu_is_moving_with_cursor) menu.set_y(menu.get_y()-1);

      emit_event(COMMAND_SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION);
   }
   else if (e == COMMAND_MOVE_CURSOR_UP)
   {
      Menu &menu = find_menu("main_menu");
      menu.move_cursor_up();
      if (menu_is_moving_with_cursor) menu.set_y(menu.get_y()+1);

      emit_event(COMMAND_SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION);
   }
   else if (e == COMMAND_TOGGLE_MENU_MOVING_WITH_CURSOR)
   {
      menu_is_moving_with_cursor = !menu_is_moving_with_cursor;
   }
   else if (e == COMMAND_BUILD_COMMAND_LIST)
   {
      std::string command_mapping_string = compose_command_mapping_text(command_mapping);
      find_text("command_list_text").set_text(command_mapping_string);
   }
   else if (e == COMMAND_RERUN_MAKE_WITH_COMPONENT_AS_FOCUS)
   {
      Menu &main_menu = find_menu("main_menu");
      std::string menu_selection = main_menu.current_selection();
      std::string component_name = extract_component_from_menu_option(menu_selection);

      std::stringstream rerun_with_focus_component_command;
      rerun_with_focus_component_command << "rr make COMPONENT=" << component_name << " focus";

      std::stringstream copy_to_clipboard_command;
      copy_to_clipboard_command << "printf \"" << rerun_with_focus_component_command.str() << "\" | pbcopy";
      system(copy_to_clipboard_command.str().c_str());
   }
   else if (e == COMMAND_REBUILD_CURRENT_PROJECT_IN_MENU)
   {
      // get the options
      std::vector<std::string> options = { };
      std::string current_directory = Blast::String::Trimmer(Blast::ShellCommandExecutorWithCallback("pwd").execute()).trim();
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
         Blast::Project::ComponentLister lister(full_folder_name);
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
         Blast::Project::ComponentLister lister(full_folder_name);
         std::vector<std::string> actual_components = lister.components();

         for (auto &actual_component : actual_components)
         {
            std::stringstream text_to_be_displayed_in_menu_option;
            text_to_be_displayed_in_menu_option
               << project_folder_name_string
               << DELIMITER
               << actual_component;

            Blast::Project::Component component(actual_component);
            std::vector<std::pair<std::string, std::string>> symlink_list = component.read_symlinks();

            bool is_symlink = !symlink_list.empty();
            if (is_symlink)
            {
               std::stringstream symlink_info_string;

               symlink_info_string << "{ ";
               for (auto &symlink_info : symlink_list)
               {
                  symlink_info_string << symlink_info.first << " ~> " << symlink_info.second << ", ";
               }
               symlink_info_string << " }";

               text_to_be_displayed_in_menu_option
                  << DELIMITER
                  << symlink_info_string.str();
            }

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
   if (e == COMMAND_SET_FILE_PREVIEW_TO_A_FILE_FROM_THE_CURRENT_SELECTION)
   {
      Menu &main_menu = find_menu("main_menu");
      Menu &file_preview = find_menu("file_preview");

      std::string text_to_extract_token = main_menu.current_selection();

      std::string component_name = extract_component_from_menu_option(text_to_extract_token);

      std::string component_header_filename = ProjectFilenameGenerator(component_name).generate_header_filename();
      std::string file_contents = file_get_contents(component_header_filename, false);

      std::vector<std::string> file_lines = StringSplitter(file_contents, '\n').split();

      file_preview.set_options(file_lines);
   }
   if (e == COMMAND_SAVE_MENU_CONTENTS_TO_FILE)
   {
      Menu &menu = find_menu("main_menu");
      std::vector<std::string> options = menu.get_options();

      std::stringstream result_to_write_to_file;
      for (auto &option : options) { result_to_write_to_file << option << std::endl; }

      file_put_contents("tmp/output_list_of_components.txt", result_to_write_to_file.str());
   }
   if (e == COMMAND_BEEBOT_SETUP_BLAST_COMPONENT_COMMAND)
   {
      Menu &menu = find_menu("main_menu");
      std::string trimmed = Blast::String::Trimmer(menu.current_selection()).trim();
      std::stringstream command;
      command << "printf \"ruby ~/Repos/beebot/lib/runner.rb setup_blast_component\" | pbcopy"; // should be replaced with an environment variable and std::getenv
      system(command.str().c_str());
   }
   return true;
}
