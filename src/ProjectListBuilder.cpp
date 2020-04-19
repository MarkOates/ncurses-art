

#include <ProjectListBuilder.hpp>
#include <filesystem>




ProjectListBuilder::ProjectListBuilder()
   : repos_directory("/Users/markoates/Repos/")
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

int repos_directory_length = repos_directory.length();
for (const auto& entry : std::filesystem::directory_iterator(repos_directory))
{
   std::string directory = entry.path().string();
   directory = directory.substr(repos_directory_length);
   result.push_back(directory);
}

return result;

}


