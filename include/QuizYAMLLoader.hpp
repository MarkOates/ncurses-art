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
   QuizYAMLLoader();
   ~QuizYAMLLoader();


   std::string get_yaml_filename();
YAML::Node load();
std::string get_type_string(YAML::Node node=YAML::Node());
};



