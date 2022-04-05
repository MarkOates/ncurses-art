

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
#include <ctime>
#include <random>
#include <Blast/StringSplitter.hpp>
#include <Blast/StringJoiner.hpp>


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
   //std::string QUIZ_FILE = "/Users/markoates/Repos/me/quizes/discover_canada/csv/Canada Flash Cards - Capitals.tsv";
   std::string QUIZ_FILE = "/Users/markoates/Repos/me/quizes/discover_canada/csv/Canada Flash Cards - Provinces.tsv";
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
      std::string subject = sanitize_quotes(question.get_subject());
      std::string reference_page = sanitize_quotes(question.get_reference_page());
      std::string date = sanitize_quotes(question.get_date());

      output << "  \"" << subject << " (page " << reference_page << ")\":" << std::endl;
      output << "    - \"" << date << "\"" << std::endl;
      output << std::endl;
      output << "  \"" << date << " (page " << reference_page << ")\":" << std::endl;
      output << "    - \"" << subject << "\"" << std::endl;
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
      std::string subject = sanitize_quotes(question.get_subject());
      std::string reference_page = sanitize_quotes(question.get_reference_page());
      std::string relevance = sanitize_quotes(question.get_relevance());

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

std::string MultiplexQuizRunner::sanitize_quotes(std::string str)
{
   std::size_t n = str.length();
   std::string escaped;
   escaped.reserve(n * 2);        // pessimistic preallocation
   for (std::size_t i = 0; i < n; ++i) {
       if (str[i] == '\\' || str[i] == '\"' || str[i] == '\'')
           escaped += '\\';
       escaped += str[i];
   }
   return escaped;
}

std::vector<std::string> MultiplexQuizRunner::split_and_shuffle_by_semicolon(std::string str)
{
   std::vector<std::string> tokens = Blast::StringSplitter(str, ';').split();

   std::random_device rng;
   std::mt19937 urng(rng());
   std::shuffle(tokens.begin(), tokens.end(), urng);

   return tokens;
}
} // namespace Quizes


