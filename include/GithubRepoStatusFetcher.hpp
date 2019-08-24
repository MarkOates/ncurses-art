#pragma once


#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>


class GithubRepoStatusFetcher
{
private:
   std::string last_captured_output;
   std::string git_status_command;
   std::string repos_directory;
   std::string repo_name;

public:
   GithubRepoStatusFetcher(std::string repo_name="blast");
   ~GithubRepoStatusFetcher();


   std::string get_last_captured_output();
   std::string get_git_status_command();
   std::string get_repos_directory();
   std::string get_repo_name();
bool local_repo_exists();
bool has_file_changes();
bool has_untracked_files();
bool is_the_repo_in_sync_with_remote();
bool is_the_local_repo_ahead();
bool is_the_local_repo_behind();
bool last_captured_output_contains_string(std::string string_to_find);
bool poll_status();
std::string full_command();
std::string execute_command(const char* cmd);
};



