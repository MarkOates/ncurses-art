

#include <GithubRepoStatusFetcher.hpp>
#include <sstream>
#include <iostream>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>




GithubRepoStatusFetcher::GithubRepoStatusFetcher()
   : tmp_outfile("")
   , initialized(false)
   , command("git status -uno")
{
}


GithubRepoStatusFetcher::~GithubRepoStatusFetcher()
{
}


std::string GithubRepoStatusFetcher::get_tmp_outfile()
{
   return tmp_outfile;
}


std::string GithubRepoStatusFetcher::get_command()
{
   return command;
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

bool GithubRepoStatusFetcher::is_the_repo_in_sync_with_remote()
{
#//std::stringstream ss;
#//ss << get_command() << " > \"" << get_tmp_outfile() << "\"";
std::stringstream command_output;
command_output << get_command() << " > \"" << get_tmp_outfile() << "\"";
system(command_output.str().c_str());

//emit_event(LOAD_FILE_COMMAND);
//find_text("body_text").set_text(get_file_contents());

//bool result = false;
//std::stringstream command_output;
#// command_output << get_command() << " > \"" << get_tmp_outfile() << "\"";
#// return result;

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

bool GithubRepoStatusFetcher::_set_cwd()
{
if (initialized) return initialized;

if (!al_init()) std::cerr << "al_init() failed" << std::endl;

ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
al_destroy_path(resource_path);
return true;

}


