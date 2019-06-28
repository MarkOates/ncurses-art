

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


YAML::Node QuizYAMLLoader::load()
{
return YAML::Load("Hello World!");
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


