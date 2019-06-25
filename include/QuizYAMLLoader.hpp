#pragma once


#include <Quiz.hpp>
#include <string>


class QuizYAMLLoader
{
private:
   Quiz* quiz;
   std::string yaml_filename;

public:
   QuizYAMLLoader();
   ~QuizYAMLLoader();


   std::string get_yaml_filename();
bool load();
};



