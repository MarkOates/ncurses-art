#include "Projekt2.h"

#include <GithubRepoStatusFetcher.hpp>

#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE_SCENE "INITIALIZE_SCENE"
#define REFRESH_STATUSES "REFRESH_STATUSES"

#define PROPERTY_DELIMITER ": "

std::map<std::string, GithubRepoStatusFetcher> statuses = {};

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



class Args
{
private:
   std::vector<std::string> args;

   bool find(std::string string)
   {
      return std::find(this->args.begin(), this->args.end(), string) != this->args.end();
   }

public:
   Args()
      : args{}
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
};




void initialize()
{
   events[INITIALIZE_SCENE] = []{
      create_text("output");

      Args magic_args;
      magic_args.set(args);

      if (magic_args.has("games"))
      {
         statuses = {
            { "Slug3D",               GithubRepoStatusFetcher("slug_3d") },
            { "Adventures of Beary",  GithubRepoStatusFetcher("adventures-of-beary") },
            { "Alex Park",            GithubRepoStatusFetcher("AlexPark") },
            { "UnnamedGameFramework", GithubRepoStatusFetcher("UnnamedGameFramework") },
         };
      }
      else
      {
         statuses = {
            { "ncurses-art",      GithubRepoStatusFetcher("ncurses-art") },
            { "blast",            GithubRepoStatusFetcher("blast") },
            { "fullscore",        GithubRepoStatusFetcher("fullscore") },
            { "hexagon",          GithubRepoStatusFetcher("hexagon") },
            { "HomeServer",       GithubRepoStatusFetcher("HomeServer") },
            { "beebot",           GithubRepoStatusFetcher("beebot") },
            { "allegro_flare",    GithubRepoStatusFetcher("allegro_flare") },
            { "disclife",         GithubRepoStatusFetcher("disclife") },
            { "me",               GithubRepoStatusFetcher("me") },
            { ".dotfiles",        GithubRepoStatusFetcher(".dotfiles") },
            { "first_vim_plugin", GithubRepoStatusFetcher("first_vim_plugin") },
            { "UnnamedGameFramework", GithubRepoStatusFetcher("UnnamedGameFramework") },
         };
      }
   };
   events[REFRESH_STATUSES] = []{
      Text &text = find_text("output");

      std::stringstream result_text;

      result_text << "Important note - this tool does not check the status of *branches* within the repos" << std::endl << std::endl;

      for (auto &status : statuses)
      {
         std::cout << "processing \"" << status.first << "\"" << std::endl;

         result_text << std::endl;

         bool exists_locally = status.second.local_repo_exists();
         bool in_sync = status.second.is_the_repo_in_sync_with_remote();
         bool has_no_changed_files = !status.second.has_file_changes();
         bool has_no_untracked_files = !status.second.has_untracked_files();
         int num_local_branches = status.second.get_branch_count();

         std::string status_icon = "🔹 clean";
         if (!exists_locally || !in_sync) status_icon = "🔺 unsynced";
         if (!has_no_changed_files || !has_no_untracked_files) status_icon = "🔸 some cluttered files";

         result_text << status.first << std::endl;
         result_text << "  status" << PROPERTY_DELIMITER << status_icon << std::endl;
         if (!exists_locally) result_text << "  " << check_it("exists locally", exists_locally) << std::endl;
         if (num_local_branches != 1) result_text << "  " << diamond_it("num local branches", num_local_branches) << std::endl;
         if (!in_sync) result_text << "  " << check_it("in sync with remote", in_sync) << std::endl;
         if (!has_no_changed_files) result_text << "  " << check_it("has no changed files", has_no_changed_files) << std::endl;
         if (!has_no_untracked_files) result_text << "  " << check_it("has no untracked files", has_no_untracked_files) << std::endl;
      }

      text.set_text(result_text.str());
   };

   emit_event(INITIALIZE_SCENE);
   emit_event(REFRESH_STATUSES);
}

