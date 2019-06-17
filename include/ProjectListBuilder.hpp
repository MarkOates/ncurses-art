#pragma once


#include <string>
#include <vector>


class ProjectListBuilder
{
private:

public:
   ProjectListBuilder();
   ~ProjectListBuilder();


std::vector<std::string> list();
std::vector<std::string> get_directories(std::string s);
};



