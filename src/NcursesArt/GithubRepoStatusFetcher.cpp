

#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/String/Trimmer.hpp>
#include <sstream>
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace NcursesArt
{


GithubRepoStatusFetcher::GithubRepoStatusFetcher(std::string repo_name, std::string repos_directory)
   : last_captured_output_from_status_request("")
   , git_status_command("git status -uno -u")
   , git_pull_command("git pull")
   , git_branch_count_command("git branch | wc -l")
   , git_current_branch_command("git branch | grep \\* | cut -d ' ' -f2")
   , git_remote_branch_names_command("git branch -r")
   , component_quintessence_filenames_command("find quintessence -name '*.q.yml'")
   , git_current_staged_files_command("git diff --name-only --cached")
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


std::string GithubRepoStatusFetcher::get_last_captured_output_from_status_request()
{
   return last_captured_output_from_status_request;
}


std::string GithubRepoStatusFetcher::get_git_status_command()
{
   return git_status_command;
}


std::string GithubRepoStatusFetcher::get_git_pull_command()
{
   return git_pull_command;
}


std::string GithubRepoStatusFetcher::get_git_branch_count_command()
{
   return git_branch_count_command;
}


std::string GithubRepoStatusFetcher::get_git_current_branch_command()
{
   return git_current_branch_command;
}


std::string GithubRepoStatusFetcher::get_git_remote_branch_names_command()
{
   return git_remote_branch_names_command;
}


std::string GithubRepoStatusFetcher::get_component_quintessence_filenames_command()
{
   return component_quintessence_filenames_command;
}


std::string GithubRepoStatusFetcher::get_git_current_staged_files_command()
{
   return git_current_staged_files_command;
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
   return !get_last_captured_output_from_status_request().empty();
}

bool GithubRepoStatusFetcher::has_file_changes()
{
   poll_status(); std::string string_to_find = "Changes not staged for commit:"; return last_captured_output_from_status_request_contains_string(string_to_find);
}

bool GithubRepoStatusFetcher::has_untracked_files()
{
   poll_status();
   std::string string_to_find = "Untracked files:";
   return last_captured_output_from_status_request_contains_string(string_to_find);
}

bool GithubRepoStatusFetcher::is_the_repo_in_sync_with_remote()
{
   poll_status();
   std::string string_to_find = "Your branch is up to date with 'origin/master'";
   return last_captured_output_from_status_request_contains_string(string_to_find);
}

bool GithubRepoStatusFetcher::is_the_local_repo_ahead()
{
   poll_status();
   std::string string_to_find = "Your branch is ahead of 'origin/master' by";
   return last_captured_output_from_status_request_contains_string(string_to_find);
}

bool GithubRepoStatusFetcher::is_the_local_repo_behind()
{
   poll_status();
   std::string string_to_find = "Your branch is behind 'origin/master' by";
   return last_captured_output_from_status_request_contains_string(string_to_find);
}

int GithubRepoStatusFetcher::get_branch_count()
{
   std::stringstream command;
   command << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && git fetch && " << get_git_branch_count_command() << ")";
   std::string command_output = execute_command(command.str());
   int result = atoi(command_output.c_str());
   return result;
}

std::vector<std::string> GithubRepoStatusFetcher::get_branch_names_at_remote()
{
   std::stringstream command;
   command << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && " << get_git_remote_branch_names_command() << ")";
   std::string command_output = execute_command(command.str());
   std::vector<std::string> lines = Blast::StringSplitter(command_output, '\n').split();
   for (auto &line : lines)
   {
      line = Blast::String::Trimmer(line).trim();
   }
   std::sort(lines.begin(), lines.end());
   return lines;
}

bool GithubRepoStatusFetcher::is_current_branch_master()
{
   return get_current_branch_name() == "master\n";
}

std::string GithubRepoStatusFetcher::get_current_branch_name_command()
{
   std::stringstream command;
   command << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && git fetch && " << get_git_current_branch_command() << ")";
   return command.str();
}

std::string GithubRepoStatusFetcher::get_pull_command()
{
   std::stringstream result;
   result << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && git fetch && " << get_git_pull_command() << ")";
   return result.str();
}

std::string GithubRepoStatusFetcher::get_status_command()
{
   std::stringstream result;
   result << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && git fetch && " << get_git_status_command() << ")";
   return result.str();
}

std::string GithubRepoStatusFetcher::get_current_staged_files_command()
{
   std::stringstream result;
   result << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && " << get_git_current_staged_files_command() << ")";
   return result.str();
}

std::vector<std::string> GithubRepoStatusFetcher::get_current_staged_files()
{
   std::string current_staged_files_command = get_current_staged_files_command();
   //return execute_command(current_staged_files_command);
   std::string command_output = execute_command(current_staged_files_command);
   return Blast::StringSplitter(command_output, '\n').split();
}

std::string GithubRepoStatusFetcher::get_current_branch_name()
{
   std::string current_branch_name_command = get_current_branch_name_command();
   return execute_command(current_branch_name_command);
}

std::vector<std::string> GithubRepoStatusFetcher::get_quintessence_filenames()
{
   std::stringstream command;
   command << "(cd " << get_repos_directory() << "/" << get_repo_name() << " && " << get_component_quintessence_filenames_command() << ")";
   std::string command_output = execute_command(command.str());
   return Blast::StringSplitter(command_output, '\n').split();
}

bool GithubRepoStatusFetcher::have_the_local_and_remote_repos_diverged()
{
   poll_status();
   std::string string_to_find = "Your branch and 'origin/master' have diverged";
   return last_captured_output_from_status_request_contains_string(string_to_find);
}

bool GithubRepoStatusFetcher::last_captured_output_from_status_request_contains_string(std::string string_to_find)
{
   std::size_t found = last_captured_output_from_status_request.find(string_to_find);
   if (found!=std::string::npos) return true;
   return false;
}

bool GithubRepoStatusFetcher::poll_status()
{
   if (get_only_poll_once() && get_status_polled()) return true;
   last_captured_output_from_status_request = execute_command(get_status_command());
   set_status_polled(true);
   return true;
}

std::string GithubRepoStatusFetcher::execute_command(std::string command)
{
   auto silent_callback = Blast::ShellCommandExecutorWithCallback::simple_silent_callback;
   Blast::ShellCommandExecutorWithCallback executor(command, silent_callback);
   return executor.execute();
}
} // namespace NcursesArt


