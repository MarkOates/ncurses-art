#pragma once


#include <string>


class GithubRepoStatusFetcher
{
private:
   std::string tmp_outfile;
   bool initialized;
   std::string command;

public:
   GithubRepoStatusFetcher();
   ~GithubRepoStatusFetcher();


   std::string get_tmp_outfile();
   std::string get_command();
std::string run();
bool has_untracked_files();
bool has_file_changes();
bool has_new_files();
bool is_the_repo_in_sync_with_remote();
bool is_the_local_repo_ahead();
bool is_the_local_repo_behind();
bool how_far_behind_is_the_repo();
bool how_ahead_is_the_repo();
bool _set_cwd();
};



