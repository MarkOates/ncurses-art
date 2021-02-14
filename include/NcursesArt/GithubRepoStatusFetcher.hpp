#pragma once


#include <string>
#include <vector>


namespace NcursesArt
{
   class GithubRepoStatusFetcher
   {
   private:
      std::string last_captured_output_from_status_request;
      std::string git_status_command;
      std::string git_pull_command;
      std::string git_branch_count_command;
      std::string git_current_branch_command;
      std::string git_remote_branch_names_command;
      std::string component_quintessence_filenames_command;
      std::string git_current_staged_files_command;
      std::string repo_name;
      std::string repos_directory;
      bool only_poll_once;
      bool status_polled;

   public:
      GithubRepoStatusFetcher(std::string repo_name="blast", std::string repos_directory="~/Repos");
      ~GithubRepoStatusFetcher();

      void set_status_polled(bool status_polled);
      std::string get_last_captured_output_from_status_request();
      std::string get_git_status_command();
      std::string get_git_pull_command();
      std::string get_git_branch_count_command();
      std::string get_git_current_branch_command();
      std::string get_git_remote_branch_names_command();
      std::string get_component_quintessence_filenames_command();
      std::string get_git_current_staged_files_command();
      std::string get_repo_name();
      std::string get_repos_directory();
      bool get_only_poll_once();
      bool get_status_polled();
      bool local_repo_exists();
      bool has_file_changes();
      bool has_untracked_files();
      bool is_the_repo_in_sync_with_remote();
      bool is_the_local_repo_ahead();
      bool is_the_local_repo_behind();
      int get_branch_count();
      std::vector<std::string> get_branch_names_at_remote();
      bool is_current_branch_master();
      std::string get_current_branch_name_command();
      std::string get_pull_command();
      std::string get_status_command();
      std::string get_current_staged_files_command();
      std::vector<std::string> get_current_staged_files();
      std::string get_current_branch_name();
      std::vector<std::string> get_quintessence_filenames();
      bool have_the_local_and_remote_repos_diverged();
      bool last_captured_output_from_status_request_contains_string(std::string string_to_find);
      bool poll_status();
      std::string execute_command(std::string command);
   };
}



