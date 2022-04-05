

#include <Quizes/MultiplexQuizRunner.hpp>
#include <Quizes/MultiplexSheetLoader.hpp>
#include <Quizes/MultiplexQuestionCollectionHelper.hpp>
#include <iostream>
#include <sstream>
#include <sstream>
#include <fstream>
#include <string>
#include <fstream>
#include <streambuf>


namespace Quizes
{


MultiplexQuizRunner::MultiplexQuizRunner()
   : question_pool()
{
}


MultiplexQuizRunner::~MultiplexQuizRunner()
{
}


void MultiplexQuizRunner::initialize()
{
   std::string QUIZ_FILE = "/Users/markoates/Repos/me/quizes/discover_canada/csv/Canada Flash Cards - Capitals.tsv";
   std::string file_contents = get_file_contents(QUIZ_FILE);

   Quizes::MultiplexSheetLoader loader(file_contents);
   loader.load();
   question_pool = loader.get_questions();
   return;
}

void MultiplexQuizRunner::run()
{
   initialize();

   Quizes::MultiplexQuestionCollectionHelper collection_helper(question_pool);
   std::vector<Quizes::MultiplexQuestion> date_questions = collection_helper.select_with_relevance();

   std::string QUIZ_YAML_OUTPUT_FILE =
      "/Users/markoates/Repos/me/quizes/discover_canada/csv/multiplex_output.yml";
   std::string yaml_formatted = format_for_quiz_yaml_relevance(date_questions);
   write_file_contents(QUIZ_YAML_OUTPUT_FILE, yaml_formatted);


   return;
}

std::string MultiplexQuizRunner::format_for_quiz_yaml_date(std::vector<Quizes::MultiplexQuestion> questions)
{
   std::stringstream output;
   output << "questions:" << std::endl;
   for (auto &question : questions)
   {
      output << "  \"" << question.get_subject() << " (page " << question.get_reference_page() << ")\":" << std::endl;
      output << "    - \"" << question.get_date() << "\"" << std::endl;
      output << std::endl;
      output << "  \"" << question.get_date() << " (page " << question.get_reference_page() << ")\":" << std::endl;
      output << "    - \"" << question.get_subject() << "\"" << std::endl;
      output << std::endl;
   }
   return output.str();
}

std::string MultiplexQuizRunner::format_for_quiz_yaml_relevance(std::vector<Quizes::MultiplexQuestion> questions)
{
   std::stringstream output;
   output << "questions:" << std::endl;
   for (auto &question : questions)
   {
      std::string subject = question.get_subject();
      std::string reference_page = question.get_reference_page();
      std::string relevance = question.get_relevance();

      output << "  \"" << subject << " (page " << reference_page << ")\":" << std::endl;
      output << "    - \"" << relevance << "\"" << std::endl;
      output << std::endl;
      output << "  \"" << relevance << " (page " << reference_page << ")\":" << std::endl;
      output << "    - \"" << subject << "\"" << std::endl;
      output << std::endl;
   }
   return output.str();
}

void MultiplexQuizRunner::write_file_contents(std::string filename, std::string file_contents)
{
   std::ofstream out(filename);
   out << file_contents;
   out.close();
}

std::string MultiplexQuizRunner::get_file_contents(std::string filename)
{
   std::ifstream t(filename);
   std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
   return str;
}
} // namespace Quizes


