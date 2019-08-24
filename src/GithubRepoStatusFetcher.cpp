

#include <GithubRepoStatusFetcher.hpp>





GithubRepoStatusFetcher::GithubRepoStatusFetcher()
   : command("git status -uno")
{
}


GithubRepoStatusFetcher::~GithubRepoStatusFetcher()
{
}


std::string GithubRepoStatusFetcher::run()
{
return "Hello Buddy!";
}

bool GithubRepoStatusFetcher::has_untracked_files()
{
return false;
}

bool GithubRepoStatusFetcher::has_file_changes()
{
return false;
}

bool GithubRepoStatusFetcher::has_new_files()
{
return false;
}

bool GithubRepoStatusFetcher::is_the_local_repo_ahead()
{
return false;
}

bool GithubRepoStatusFetcher::is_the_local_repo_behind()
{
return false;
}

bool GithubRepoStatusFetcher::how_far_behind_is_the_repo()
{
return false;
}

bool GithubRepoStatusFetcher::how_ahead_is_the_repo()
{
return false;
}


