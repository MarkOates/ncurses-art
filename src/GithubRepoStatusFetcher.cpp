

#include <GithubRepoStatusFetcher.hpp>
#include <sstream>
#include <iostream>
#include <iostream>




GithubRepoStatusFetcher::GithubRepoStatusFetcher(std::string repo_name)
   : last_captured_output("")
   , git_status_command("git status -uno")
   , repos_directory("~/Repos")
   , repo_name(repo_name)
{
}


GithubRepoStatusFetcher::~GithubRepoStatusFetcher()
{
}


std::string GithubRepoStatusFetcher::get_last_captured_output()
{
   return last_captured_output;
}


std::string GithubRepoStatusFetcher::get_git_status_command()
{
   return git_status_command;
}


std::string GithubRepoStatusFetcher::get_repos_directory()
{
   return repos_directory;
}


std::string GithubRepoStatusFetcher::get_repo_name()
{
   return repo_name;
}


bool GithubRepoStatusFetcher::local_repo_exists()
{
poll_status();
// TODO: modify this function so it can rely on captured std::err output
// std::string string_to_find = "cd: no such file or directory";
return !get_last_captured_output().empty();

}

bool GithubRepoStatusFetcher::has_untracked_files()
{
throw std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::has_file_changes()
{
throw std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::has_new_files()
{
throw std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::is_the_repo_in_sync_with_remote()
{
poll_status();
std::string string_to_find = "Your branch is up to date with 'origin/master'";
return last_captured_output_contains_string(string_to_find);
return true;

}

bool GithubRepoStatusFetcher::is_the_local_repo_ahead()
{
poll_status();
std::string string_to_find = "Your branch is ahead of 'origin/master' by";
return last_captured_output_contains_string(string_to_find);

}

bool GithubRepoStatusFetcher::is_the_local_repo_behind()
{
throw std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::how_far_behind_is_the_repo()
{
throw std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::how_ahead_is_the_repo()
{
throw std::runtime_error("not implemented"); return false;
}

bool GithubRepoStatusFetcher::last_captured_output_contains_string(std::string string_to_find)
{
std::size_t found = last_captured_output.find(string_to_find);
if (found!=std::string::npos) return true;
return false;

}

bool GithubRepoStatusFetcher::poll_status()
{
last_captured_output = execute_command(full_command().c_str());
return true;

}

std::string GithubRepoStatusFetcher::full_command()
{
std::stringstream result;
result << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && git status -uno)";
return result.str();

}

std::string GithubRepoStatusFetcher::execute_command(const char* cmd)
{
// TODO: This should be replaced with Blast::ShellCommandExecutor
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


