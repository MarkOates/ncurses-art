

#include <QuizYAMLLoader.hpp>





QuizYAMLLoader::QuizYAMLLoader()
   : quiz(nullptr)
   , yaml_filename()
{
}


QuizYAMLLoader::~QuizYAMLLoader()
{
}


std::string QuizYAMLLoader::get_yaml_filename()
{
   return yaml_filename;
}


bool QuizYAMLLoader::load()
{
return true;
}


