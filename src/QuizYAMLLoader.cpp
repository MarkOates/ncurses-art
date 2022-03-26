

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


bool QuizYAMLLoader::load_and_append()
{
   YAML::Node loaded_file = YAML::LoadFile(yaml_filename);
   YAML::Node questions_within_yaml = loaded_file["questions"];

   std::vector<Question> questions;

   for(YAML::const_iterator it=questions_within_yaml.begin(); it!=questions_within_yaml.end(); ++it)
   {
     YAML::Node answers = it->second;
     std::string first_answer_str = answers[0].as<std::string>();
     std::vector<std::string> wrong_answers;
     for (int i=1; i<answers.size(); i++)
     {
       wrong_answers.push_back(answers[i].as<std::string>());
     }

     questions.push_back({
       it->first.as<std::string>(),
       "",
       first_answer_str,
       wrong_answers,
     });
   }

   //quiz->set_questions(questions);
   quiz->append_questions(questions);
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


