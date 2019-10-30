#include "Projekt2.h"

#include <GithubRepoStatusFetcher.hpp>

#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE_SCENE "INITIALIZE_SCENE"
#define REFRESH_ALL_STATUSES "REFRESH_ALL_STATUSES"
#define REFRESH_NEXT_STATUS "REFRESH_NEXT_STATUS"
#define REFRESH_OUTPUT_REPORT "REFRESH_OUTPUT_REPORT"

#define OUTPUT_REPORT_TEXT_IDENTIFIER "output report"
#define OUTPUT_REPORT_TEXT find_text(OUTPUT_REPORT_TEXT_IDENTIFIER)

#define PROPERTY_DELIMITER ": "


class ProjectStatus
{
private:
   std::string repo_name;

   bool exists_locally;
   bool in_sync;
   bool has_no_changed_files;
   bool has_no_untracked_files;
   int num_local_branches;

   GithubRepoStatusFetcher fetcher;

public:
   ProjectStatus(std::string repo_name)
      : repo_name(repo_name)
      , exists_locally(false)
      , in_sync(false)
      , has_no_changed_files(false)
      , has_no_untracked_files(false)
      , num_local_branches(0)
      , fetcher()
   {}

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

   void process()
   {
      exists_locally = fetcher.local_repo_exists();
      in_sync = fetcher.is_the_repo_in_sync_with_remote();
      has_no_changed_files = !fetcher.has_file_changes();
      has_no_untracked_files = !fetcher.has_untracked_files();
      num_local_branches = fetcher.get_branch_count();
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
         "all",
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


std::string get_status_icon_and_text(bool project_has_been_processed, bool exists_locally, bool in_sync, bool has_no_changed_files, bool has_no_untracked_files)
{
   if (project_has_been_processed == false) return "▫️  unprocessed";

   std::string status_icon = "🔹 clean";
   if (!exists_locally || !in_sync) status_icon = "🔺 unsynced";
   if (!has_no_changed_files || !has_no_untracked_files) status_icon = "🔸 some cluttered files";
   return status_icon;
}



void initialize()
{
   events[INITIALIZE_SCENE] = []{
      create_text(OUTPUT_REPORT_TEXT_IDENTIFIER);

      Args magic_args;
      magic_args.set(args);

      bool fetch_game_repos = magic_args.has("games");
      bool fetch_core_repos = magic_args.has("core") || magic_args.has_no_recognized_args();

      if (fetch_game_repos)
      {
         projects = {
            { "Slug3D",               { false, ProjectStatus("slug_3d") } },
            { "Adventures of Beary",  { false, ProjectStatus("adventures-of-beary") } },
            { "Alex Park",            { false, ProjectStatus("AlexPark") } },
            { "dungeon",              { false, ProjectStatus("dungeon") } },
            { "lightracer-max",       { false, ProjectStatus("lightracer-max") } },
            { "beary2d",              { false, ProjectStatus("beary2d") } },
            { "tilemap",              { false, ProjectStatus("tilemap") } },
            { "motris",               { false, ProjectStatus("motris") } },
            { "tileo",                { false, ProjectStatus("tileo") } },
         };
      }

      if (fetch_core_repos)
      {
         projects = {
            { "ncurses-art",      { false, ProjectStatus("ncurses-art") } },
            { "blast",            { false, ProjectStatus("blast") } },
            { "fullscore",        { false, ProjectStatus("fullscore") } },
            { "oatescodes",       { false, ProjectStatus("oatescodes") } },
            { "hexagon",          { false, ProjectStatus("hexagon") } },
            { "HomeServer",       { false, ProjectStatus("HomeServer") } },
            { "beebot",           { false, ProjectStatus("beebot") } },
            { "allegro_flare",    { false, ProjectStatus("allegro_flare") } },
            { "allegro-planet",   { false, ProjectStatus("allegro-planet") } },
            { "disclife",         { false, ProjectStatus("disclife") } },
            { "crayola",          { false, ProjectStatus("crayola") } },
            { "crayola-client",   { false, ProjectStatus("crayola-client") } },
            { "me",               { false, ProjectStatus("me") } },
            { ".dotfiles",        { false, ProjectStatus(".dotfiles") } },
            { "first_vim_plugin", { false, ProjectStatus("first_vim_plugin") } },
            { "allegroflare.github.io", { false, ProjectStatus("allegroflare.github.io") } },
         };
      }
   };
   events[REFRESH_NEXT_STATUS] = []{
   };
   events[REFRESH_OUTPUT_REPORT] = []{
      std::stringstream result_text;

      result_text << "Important note - this tool does not check the status of *branches* within the repos" << std::endl << std::endl;

      for (auto &project : projects)
      {
         ProjectStatus &project_status = project.second.second;
         bool exists_locally = project_status.get_exists_locally();
         bool in_sync = project_status.get_in_sync();
         bool has_no_changed_files = project_status.get_has_no_changed_files();
         bool has_no_untracked_files = project_status.get_has_no_untracked_files();
         int num_local_branches = project_status.get_num_local_branches();
         std::string project_identifier = project.first;
         bool project_has_been_processed = project.second.first;

         result_text << std::endl;
         result_text << project_identifier << std::endl;
         result_text << "  status" << PROPERTY_DELIMITER << get_status_icon_and_text(project_has_been_processed, exists_locally, in_sync, has_no_changed_files, has_no_untracked_files) << std::endl;
         if (project_has_been_processed == true)
         {
            result_text << "  " << check_it("exists locally", exists_locally) << std::endl;
            result_text << "  " << diamond_it("num local branches", num_local_branches) << std::endl;
            result_text << "  " << check_it("in sync with remote", in_sync) << std::endl;
            result_text << "  " << check_it("has no changed files", has_no_changed_files) << std::endl;
            result_text << "  " << check_it("has no untracked files", has_no_untracked_files) << std::endl;
         }
      }

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
   };

   emit_event(INITIALIZE_SCENE);
   emit_event(REFRESH_ALL_STATUSES);
   emit_event(REFRESH_OUTPUT_REPORT);
}

