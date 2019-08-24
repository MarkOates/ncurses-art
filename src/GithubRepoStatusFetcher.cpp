

#include <GithubRepoStatusFetcher.hpp>
#include <sstream>
#include <iostream>
#include <iostream>




GithubRepoStatusFetcher::GithubRepoStatusFetcher(std::string repo_name, std::string repos_directory)
   : last_captured_output("")
   , git_status_command("git status -uno -u")
   , git_branch_count_command("git branch | wc -l")
   , repo_name(repo_name)
   , repos_directory(repos_directory)
   , only_poll_once(true)
   , status_polled(false)
{
}


GithubRepoStatusFetcher::~GithubRepoStatusFetcher()
{
}


void GithubRepoStatusFetcher::set_status_polled(bool status_polled)
{
   this->status_polled = status_polled;
}


std::string GithubRepoStatusFetcher::get_last_captured_output()
{
   return last_captured_output;
}


std::string GithubRepoStatusFetcher::get_git_status_command()
{
   return git_status_command;
}


std::string GithubRepoStatusFetcher::get_git_branch_count_command()
{
   return git_branch_count_command;
}


std::string GithubRepoStatusFetcher::get_repo_name()
{
   return repo_name;
}


std::string GithubRepoStatusFetcher::get_repos_directory()
{
   return repos_directory;
}


bool GithubRepoStatusFetcher::get_only_poll_once()
{
   return only_poll_once;
}


bool GithubRepoStatusFetcher::get_status_polled()
{
   return status_polled;
}


bool GithubRepoStatusFetcher::local_repo_exists()
{
poll_status();
// TODO: modify this function so it can rely on captured std::err output
// std::string string_to_find = "cd: no such file or directory";
return !get_last_captured_output().empty();

}

bool GithubRepoStatusFetcher::has_file_changes()
{
poll_status(); std::string string_to_find = "Changes not staged for commit:"; return last_captured_output_contains_string(string_to_find);
}

bool GithubRepoStatusFetcher::has_untracked_files()
{
poll_status();
std::string string_to_find = "Untracked files:";
return last_captured_output_contains_string(string_to_find);

}

bool GithubRepoStatusFetcher::is_the_repo_in_sync_with_remote()
{
poll_status();
std::string string_to_find = "Your branch is up to date with 'origin/master'";
return last_captured_output_contains_string(string_to_find);

}

bool GithubRepoStatusFetcher::is_the_local_repo_ahead()
{
poll_status();
std::string string_to_find = "Your branch is ahead of 'origin/master' by";
return last_captured_output_contains_string(string_to_find);

}

bool GithubRepoStatusFetcher::is_the_local_repo_behind()
{
poll_status();
std::string string_to_find = "Your branch is behind 'origin/master' by";
return last_captured_output_contains_string(string_to_find);

}

int GithubRepoStatusFetcher::get_branch_count()
{
std::stringstream command;
command << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && git fetch && " << get_git_branch_count_command() << ")";
std::string command_output = execute_command(command.str().c_str());
int result = atoi(command_output.c_str());
return result;

}

bool GithubRepoStatusFetcher::have_the_local_and_remote_repos_diverged()
{
poll_status();
std::string string_to_find = "Your branch and 'origin/master' have diverged";
return last_captured_output_contains_string(string_to_find);

}

bool GithubRepoStatusFetcher::last_captured_output_contains_string(std::string string_to_find)
{
std::size_t found = last_captured_output.find(string_to_find);
if (found!=std::string::npos) return true;
return false;

}

bool GithubRepoStatusFetcher::poll_status()
{
if (get_only_poll_once() && get_status_polled()) return true;
last_captured_output = execute_command(full_command().c_str());
set_status_polled(true);
return true;

}

std::string GithubRepoStatusFetcher::full_command()
{
std::stringstream result;
result << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && git fetch && " << get_git_status_command() << ")";
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


