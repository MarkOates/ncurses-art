#pragma once


#include <string>
#include <vector>


class ProjectListBuilder
{
private:
   std::string repos_directory;

public:
   ProjectListBuilder();
   ~ProjectListBuilder();


   std::string get_repos_directory();
std::vector<std::string> list();
std::vector<std::string> get_directories();
};



