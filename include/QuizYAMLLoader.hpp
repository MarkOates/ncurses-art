#pragma once


#include <Quiz.hpp>
#include <string>
#include <yaml-cpp/yaml.h>


class QuizYAMLLoader
{
private:
   Quiz* quiz;
   std::string yaml_filename;

public:
   QuizYAMLLoader(Quiz* quiz=nullptr, std::string yaml_filename="");
   ~QuizYAMLLoader();

   std::string get_yaml_filename();
   bool load_and_append();
   std::string get_type_string(YAML::Node node=YAML::Node());
};



