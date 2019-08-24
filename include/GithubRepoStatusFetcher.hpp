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
   std::string repo_name;

public:
   GithubRepoStatusFetcher();
   ~GithubRepoStatusFetcher();


   std::string get_git_status_command();
   std::string get_repo_name();
bool poll_status();
std::string execute_command(const char* cmd);
std::string full_command();
bool has_untracked_files();
bool has_file_changes();
bool has_new_files();
std::string is_the_repo_in_sync_with_remote();
bool is_the_local_repo_ahead();
bool is_the_local_repo_behind();
bool how_far_behind_is_the_repo();
bool how_ahead_is_the_repo();
};



