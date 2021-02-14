

#include <ProjectListBuilder.hpp>
#include <filesystem>
#include <sstream>




ProjectListBuilder::ProjectListBuilder(std::string repos_directory)
   : repos_directory(repos_directory)
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
   if (repos_directory.empty() || repos_directory.back() != '/')
   {
      std::stringstream error_message;
      error_message << "[ProjectListBuilder::get_directories error:] "
                    << "repos_directory must end in '/' character.";
      throw std::runtime_error(error_message.str());
   }

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


