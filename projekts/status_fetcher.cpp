#include "Projekt2.h"

#include <GithubRepoStatusFetcher.hpp>

#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE_SCENE "INITIALIZE_SCENE"
#define REFRESH_STATUSES "REFRESH_STATUSES"

std::map<std::string, GithubRepoStatusFetcher> statuses = {};

std::string check_it(std::string label, bool check)
{
   std::stringstream result;
   result << label;
   if (check) result << " - ✓ yes";
   else result << " - ✗ no";
   return result.str();
}

void initialize()
{
   events[INITIALIZE_SCENE] = []{
      create_text("output");

      statuses = {
         { "ncurses-art",   GithubRepoStatusFetcher("ncurses-art") },
         { "blast",         GithubRepoStatusFetcher("blast") },
         { "fullscore",     GithubRepoStatusFetcher("fullscore") },
         { "hexagon",       GithubRepoStatusFetcher("hexagon") },
         { "HomeServer",    GithubRepoStatusFetcher("HomeServer") },
         { "beebot",        GithubRepoStatusFetcher("beebot") },
         { "allegro_flare", GithubRepoStatusFetcher("allegro_flare") },
         { "me",            GithubRepoStatusFetcher("me", "~") },
         { ".dotfiles",     GithubRepoStatusFetcher(".dotfiles") },
      };
   };
   events[REFRESH_STATUSES] = []{
      Text &text = find_text("output");

      std::stringstream result_text;

      result_text << "Important note - this tool does not check the status of *branches* within the repos" << std::endl << std::endl;

      for (auto &status : statuses)
      {
         std::cout << "processing \"" << status.first << "\"" << std::endl;

         result_text << std::endl;
         result_text << status.first << std::endl;
         result_text << "  " << check_it("exists locally", status.second.local_repo_exists()) << std::endl;
         result_text << "  " << check_it("in sync with remote", status.second.is_the_repo_in_sync_with_remote()) << std::endl;
         result_text << "  " << check_it("has no changed files", !status.second.has_file_changes()) << std::endl;
         result_text << "  " << check_it("has no untracked files", !status.second.has_untracked_files()) << std::endl;
      }

      text.set_text(result_text.str());
   };

   emit_event(INITIALIZE_SCENE);
   emit_event(REFRESH_STATUSES);
}

