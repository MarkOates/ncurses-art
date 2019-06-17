

#include <ProjectListBuilder.hpp>
#include <dirent.h>
#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <dirent.h>
#include <stdio.h>




ProjectListBuilder::ProjectListBuilder()
   : repos_directory("/Users/markoates/Repos")
{
}


ProjectListBuilder::~ProjectListBuilder()
{
}


std::string ProjectListBuilder::get_repos_directory()
{
   return repos_directory;
}


std::vector<std::string> ProjectListBuilder::get_directories()
{
std::vector<std::string> result = {};
const char* PATH = get_repos_directory().c_str();
DIR *dir = opendir(PATH);
struct dirent *entry = readdir(dir);
while (entry != NULL)
{
    if (entry->d_type == DT_DIR)
    {
       std::string name = entry->d_name;
       if (name == ".") {}
       else if (name == "..") {}
       else { result.push_back(name); }
    }

    entry = readdir(dir);
}
closedir(dir);
return result;

}


