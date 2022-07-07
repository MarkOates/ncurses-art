#include "Projekt2.h"

#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <HostnameExtractor.hpp>

#include <iostream>
#include <algorithm> // for std::find

#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE_SCENE "INITIALIZE_SCENE"
#define REFRESH_ALL_STATUSES "REFRESH_ALL_STATUSES"
#define PROCESS_NEXT_STATUS "PROCESS_NEXT_STATUS"
#define REFRESH_OUTPUT_REPORT "REFRESH_OUTPUT_REPORT"
#define REFRESH_PROGRESS_BAR "REFRESH_PROGRESS_BAR"
#define INCREMENTAL_RUN "INCREMENTAL_RUN"

#define OUTPUT_REPORT_TEXT_IDENTIFIER "output report"
#define OUTPUT_REPORT_TEXT find_text(OUTPUT_REPORT_TEXT_IDENTIFIER)

#define HOSTNAME_TEXT_IDENTIFIER "hostname text"
#define HOSTNAME_TEXT find_text(HOSTNAME_TEXT_IDENTIFIER)

#define PROGRESS_BAR_IDENTIFIER "progress bar"
#define PROGRESS_BAR find_progress_bar(PROGRESS_BAR_IDENTIFIER)

#define PROGRESS_BAR_TEXT_IDENTIFIER "progress bar text"
#define PROGRESS_BAR_TEXT find_text(PROGRESS_BAR_TEXT_IDENTIFIER)

#define PROPERTY_DELIMITER ": "


using NcursesArt::GithubRepoStatusFetcher;


class ProjectStatus
{
private:
   std::string repo_name;

   bool exists_locally;
   bool in_sync;
   bool has_no_changed_files;
   bool has_no_untracked_files;
   bool has_no_staged_files;
   int num_local_branches;

   GithubRepoStatusFetcher fetcher;

public:
   ProjectStatus(std::string repo_name)
      : repo_name(repo_name)
      , exists_locally(false)
      , in_sync(false)
      , has_no_changed_files(false)
      , has_no_untracked_files(false)
      , has_no_staged_files(false)
      , num_local_branches(0)
      , fetcher(repo_name)
   {}

   std::string get_repo_name()
   {
      return repo_name;
   }

   bool get_exists_locally()
   {
      return exists_locally;
   }

   bool get_in_sync()
   {
      return in_sync;
   }

   bool get_has_no_changed_files()
   {
      return has_no_changed_files;
   }

   bool get_has_no_untracked_files()
   {
      return has_no_untracked_files;
   }

   int get_num_local_branches()
   {
      return num_local_branches;
   }

   int get_has_no_staged_files()
   {
      return has_no_staged_files;
   }

   void process()
   {
      exists_locally = fetcher.local_repo_exists();
      in_sync = fetcher.is_the_repo_in_sync_with_remote();
      has_no_changed_files = !fetcher.has_file_changes();
      has_no_untracked_files = !fetcher.has_untracked_files();
      num_local_branches = fetcher.get_branch_count();
      has_no_staged_files = (fetcher.get_current_staged_files().size() == 0);
   }
};


std::map<std::string, std::pair<bool, ProjectStatus>> projects = {};

std::string diamond_it(std::string label, int number)
{
   std::stringstream result;
   bool check = number == 1;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "🔹 ";
   else result << PROPERTY_DELIMITER << "🔸 ";
   result << number;

   return result.str();
}

std::string check_it(std::string label, bool check)
{
   std::stringstream result;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "✓ yes";
   else result << PROPERTY_DELIMITER << "✗ no";
   return result.str();
}

std::string show_it(std::string label, std::string value)
{
   std::stringstream result;
   result << label << PROPERTY_DELIMITER << value;
   return result.str();
}


#include <StringVectorIntersection.hpp>

class Args
{
private:
   std::vector<std::string> known_args;
   std::vector<std::string> args;

   bool find(std::string string)
   {
      return std::find(this->args.begin(), this->args.end(), string) != this->args.end();
   }

public:
   Args()
      : known_args({
         "core",
         "games",
        })
      , args{}
   {}

   void set(std::vector<std::string> args)
   {
      this->args = args;
   }

   void set(int argc, char **argv)
   {
      for (int i=0; i<argc; i++) this->args.push_back(argv[i]);
   }

   bool has(std::string arg_string_to_find)
   {
      return find(arg_string_to_find);
   }

   bool has_no_recognized_args()
   {
      StringVectorIntersection intersection(args, known_args);
      return intersection.intersection().empty();
   }
};


enum final_status_t
{
   NONE = 0,
   UNPROCESSED,
   CLEAN,
   UNSYNCED,
   SOME_CLUTTERED_FILES,
   EXTRA_LOCAL_BRANCHES,
};


final_status_t get_final_status(int num_local_branches, bool project_has_been_processed, bool exists_locally, bool in_sync, bool has_no_changed_files, bool has_no_untracked_files, bool has_no_staged_files)
{
   if (project_has_been_processed == false) return UNPROCESSED;

   final_status_t status = CLEAN;
   if (num_local_branches > 1) status = EXTRA_LOCAL_BRANCHES;
   if (!exists_locally || !in_sync) status = UNSYNCED;
   if (!has_no_changed_files || !has_no_untracked_files || !has_no_staged_files) status = SOME_CLUTTERED_FILES;
   return status;
}


std::string get_hostname()
{
   return HostnameExtractor().get_computer_name();
}


std::string get_status_icon_and_text(final_status_t status, int num_local_branches)
{
   switch (status)
   {
   case NONE:
      return "⧄  none";
      break;
   case UNPROCESSED:
      return "▫️  unprocessed";
      break;
   case CLEAN:
      return "💎 clean";
      break;
   case UNSYNCED:
      return "🔺 unsynced";
      break;
   case SOME_CLUTTERED_FILES:
      return "🔸 some cluttered files";
      break;
   case EXTRA_LOCAL_BRANCHES:
      return std::string("🔹 some extra local branches (") + std::to_string(num_local_branches) + ")";
      break;
   }

   return "🌌 status unknown";
}


bool have_all_projects_been_processed()
{
   for (auto &project : projects)
   {
      bool project_has_been_processed = project.second.first;
      if (!project_has_been_processed) return false;
   }
   return true;
}


int get_number_of_projects_processed()
{
   int projects_processed_count = 0;
   for (auto &project : projects)
   {
      bool project_has_been_processed = project.second.first;
      if (project_has_been_processed) projects_processed_count++;
   }
   return projects_processed_count;
}


void initialize()
{
   events[INITIALIZE_SCENE] = []{
      create_text(HOSTNAME_TEXT_IDENTIFIER, 5, 2);
      create_progress_bar(PROGRESS_BAR_IDENTIFIER, 3, 2+2, 60, 3);
      create_text(PROGRESS_BAR_TEXT_IDENTIFIER, 5, 5+2);
      create_text(OUTPUT_REPORT_TEXT_IDENTIFIER, 3, 8+2);

      HOSTNAME_TEXT.set_text(get_hostname());

      PROGRESS_BAR_TEXT.set_text("processing...");

      Args magic_args;
      magic_args.set(args);

      projects = {
         //{ "Adventures of Beary",  { false, ProjectStatus("adventures-of-beary") } },
         //{ "Alex Park",            { false, ProjectStatus("AlexPark") } },
         //{ "HomeServer",       { false, ProjectStatus("HomeServer") } },
         { "LabyrinthOfLore",  { false, ProjectStatus("LabyrinthOfLore") } },
         //{ "Peri",      { false, ProjectStatus("Peri") } },
         { "Solitare",          { false, ProjectStatus("Solitare") } },
         //{ "allegro-planet",   { false, ProjectStatus("allegro-planet") } },
         //{ "allegroflare.github.io", { false, ProjectStatus("allegroflare.github.io") } },
         //{ "beary2d",              { false, ProjectStatus("beary2d") } },
         //{ "crayola",          { false, ProjectStatus("crayola") } },
         //{ "crayola-client",   { false, ProjectStatus("crayola-client") } },
         //{ "disclife",         { false, ProjectStatus("disclife") } },
         //{ "dungeon",              { false, ProjectStatus("dungeon") } },
         //{ "first_vim_plugin", { false, ProjectStatus("first_vim_plugin") } },
         //{ "flare_network",    { false, ProjectStatus("flare_network") } },
         //{ "fullscore",        { false, ProjectStatus("fullscore") } },
         { "motris",               { false, ProjectStatus("motris") } },
         //{ "tilemap",              { false, ProjectStatus("tilemap") } },
         { "Fade to White (Krampus21)", { false, ProjectStatus("Krampus21") } },
         { ".dotfiles",        { false, ProjectStatus(".dotfiles") } },
         { "DragonWrath",      { false, ProjectStatus("DragonWrath") } },
         { "Releaser",      { false, ProjectStatus("Releaser") } },
         { "Slug3D",               { false, ProjectStatus("slug_3d") } },
         { "allegro_flare",    { false, ProjectStatus("allegro_flare") } },
         { "beebot",           { false, ProjectStatus("beebot") } },
         { "blast",            { false, ProjectStatus("blast") } },
         { "hexagon",          { false, ProjectStatus("hexagon") } },
         { "lightracer-max",       { false, ProjectStatus("lightracer-max") } },
         { "me",               { false, ProjectStatus("me") } },
         { "ncurses-art",      { false, ProjectStatus("ncurses-art") } },
         { "oatescodes",       { false, ProjectStatus("oatescodes") } },
         { "tileo",                { false, ProjectStatus("tileo") } },
         { "union",            { false, ProjectStatus("union") } },
         { "Wicked",            { false, ProjectStatus("Wicked") } },
         //{ "/Library/Application Support/Adobe/CEP/extensions", { false, ProjectStatus("unset") } },
      };

      emit_event(REFRESH_OUTPUT_REPORT);
      emit_event(REFRESH_PROGRESS_BAR);
   };
   events[PROCESS_NEXT_STATUS] = []{
      if (projects.empty()) return;

      for (auto &project : projects)
      {
         bool project_has_been_processed = project.second.first;
         if (!project_has_been_processed)
         {
            std::string project_identifier = project.first;
            ProjectStatus &project_status = project.second.second;
            bool &project_processed_state = project.second.first;

            project_status.process();
            project_processed_state = true;

            break;
         }
      }
   };
   events[INCREMENTAL_RUN] = []{
      if (!have_all_projects_been_processed())
      {
         emit_event(PROCESS_NEXT_STATUS);
         emit_event(REFRESH_OUTPUT_REPORT);
         emit_event(REFRESH_PROGRESS_BAR);
         emit_event(INCREMENTAL_RUN);
      }
      else
      {
         PROGRESS_BAR_TEXT.set_text("finished.");
      }
   };
   events[REFRESH_PROGRESS_BAR] = []{
      int total_number_of_projects_for_processing = projects.size();
      int number_of_projects_processed = get_number_of_projects_processed();
      float updated_progress_bar_value = (float)number_of_projects_processed / total_number_of_projects_for_processing;
      PROGRESS_BAR.set_value(updated_progress_bar_value);
   };
   events[REFRESH_OUTPUT_REPORT] = []{
      std::stringstream result_text;

      result_text << "[i] This tool does not check the status of *branches* within the repos" << std::endl << std::endl << std::endl;

      for (auto &project : projects)
      {
         ProjectStatus &project_status = project.second.second;
         bool exists_locally = project_status.get_exists_locally();
         bool in_sync = project_status.get_in_sync();
         bool has_no_changed_files = project_status.get_has_no_changed_files();
         bool has_no_untracked_files = project_status.get_has_no_untracked_files();
         bool has_no_staged_files = project_status.get_has_no_staged_files();
         int num_local_branches = project_status.get_num_local_branches();
         std::string project_identifier = project.first;
         std::string repo_name = project_status.get_repo_name();
         bool project_has_been_processed = project.second.first;
         final_status_t final_status = get_final_status(num_local_branches, project_has_been_processed, exists_locally, in_sync, has_no_changed_files, has_no_untracked_files, has_no_staged_files);

         std::string status_icon_and_text = get_status_icon_and_text(final_status, num_local_branches);
         result_text << project_identifier << PROPERTY_DELIMITER << status_icon_and_text;
         if (project_has_been_processed == true && !(final_status == CLEAN || final_status == EXTRA_LOCAL_BRANCHES))
         {
            result_text << "  " << show_it("repo name", repo_name) << std::endl;
            result_text << "  " << check_it("exists locally", exists_locally) << std::endl;
            result_text << "  " << diamond_it("num local branches", num_local_branches) << std::endl;
            result_text << "  " << check_it("in sync with remote", in_sync) << std::endl;
            result_text << "  " << check_it("has no changed files", has_no_changed_files) << std::endl;
            result_text << "  " << check_it("has no untracked files", has_no_untracked_files) << std::endl;
            result_text << "  " << check_it("has no staged files", has_no_staged_files) << std::endl;
         }
         result_text << std::endl;
      }

      //result_text << std::endl << "some processing messaging garbage:" << std::endl << std::endl << std::endl;

      OUTPUT_REPORT_TEXT.set_text(result_text.str());
   };
   events[REFRESH_ALL_STATUSES] = []{
      for (auto &project : projects)
      {
         std::string project_identifier = project.first;
         ProjectStatus &project_status = project.second.second;
         bool &project_processed_state = project.second.first;

         std::cout << "processing \"" << project_identifier << "\"" << std::endl;
         project_status.process();
         project_processed_state = true;
      }

      PROGRESS_BAR_TEXT.set_text("finished.");
   };

   emit_event(INITIALIZE_SCENE);
   emit_event(INCREMENTAL_RUN);
}

