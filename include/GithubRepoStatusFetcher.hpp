#pragma once


#include <string>


class GithubRepoStatusFetcher
{
private:
   std::string command;

public:
   GithubRepoStatusFetcher();
   ~GithubRepoStatusFetcher();


std::string run();
bool has_untracked_files();
bool has_file_changes();
bool has_new_files();
bool is_the_local_repo_ahead();
bool is_the_local_repo_behind();
bool how_far_behind_is_the_repo();
bool how_ahead_is_the_repo();
};



