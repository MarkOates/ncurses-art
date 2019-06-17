

#include <ProjectListBuilder.hpp>





ProjectListBuilder::ProjectListBuilder()
{
}


ProjectListBuilder::~ProjectListBuilder()
{
}


std::vector<std::string> ProjectListBuilder::list()
{
std::vector<std::string> result = {};
result = { "Hello World!", "Hello Buddy!" };
return result;

}

std::vector<std::string> ProjectListBuilder::get_directories(std::string s)
{
return { "" };

}


