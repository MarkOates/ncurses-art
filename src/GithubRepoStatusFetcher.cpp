

#include <GithubRepoStatusFetcher.hpp>
#include <sstream>
#include <iostream>
#include <iostream>




GithubRepoStatusFetcher::GithubRepoStatusFetcher()
   : last_captured_output("")
   , git_status_command("git status -uno")
   , repo_name("blast")
{
}


GithubRepoStatusFetcher::~GithubRepoStatusFetcher()
{
}


std::string GithubRepoStatusFetcher::get_git_status_command()
{
   return git_status_command;
}


std::string GithubRepoStatusFetcher::get_repo_name()
{
   return repo_name;
}


bool GithubRepoStatusFetcher::poll_status()
{
last_captured_output = execute_command(full_command().c_str());
return true;

}

std::string GithubRepoStatusFetcher::execute_command(const char* cmd)
{
std::array<char, 128> buffer;
std::string result;
std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
if (!pipe) {
    throw std::runtime_error("popen() failed!");
}
while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
}
return result;

}

std::string GithubRepoStatusFetcher::full_command()
{
std::stringstream result;
result << "(cd ~/Repos/" << repo_name << " && git status -uno)";
return result.str();

}

bool GithubRepoStatusFetcher::has_untracked_files()
{
raise std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::has_file_changes()
{
raise std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::has_new_files()
{
raise std::runtime_error("not implemented"); return false;
}

std::string GithubRepoStatusFetcher::is_the_repo_in_sync_with_remote()
{
poll_status();
return last_captured_output;

}

bool GithubRepoStatusFetcher::is_the_local_repo_ahead()
{
raise std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::is_the_local_repo_behind()
{
raise std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::how_far_behind_is_the_repo()
{
raise std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::how_ahead_is_the_repo()
{
raise std::runtime_error("not implemented"); return false;
}


