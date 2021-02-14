#pragma once


#include <string>
#include <vector>


class ProjectListBuilder
{
private:
   std::string repos_directory;

public:
   ProjectListBuilder(std::string repos_directory="/Users/markoates/Repos/");
   ~ProjectListBuilder();

   std::string get_repos_directory();
   std::vector<std::string> get_directories();
};



