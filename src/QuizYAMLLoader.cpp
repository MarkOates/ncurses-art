

#include <QuizYAMLLoader.hpp>





QuizYAMLLoader::QuizYAMLLoader(Quiz* quiz, std::string yaml_filename)
   : quiz(quiz)
   , yaml_filename(yaml_filename)
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
quiz->set_questions({
   { "The speed limit approaching a school crosswalk is",
     "",
     "15 mph",
     { "20 mph", "25 mph" }
   },
 });
return true;

}

std::string QuizYAMLLoader::get_type_string(YAML::Node node)
{
switch (node.Type())
{
  case YAML::NodeType::Null: return "Null"; break;
  case YAML::NodeType::Scalar: return "Scalar"; break;
  case YAML::NodeType::Sequence: return "Sequence"; break;
  case YAML::NodeType::Map: return "Map"; break;
  case YAML::NodeType::Undefined: return "Undefined"; break;
}
return "[NO_TYPE_DEFINED_ERROR]";

}


