

#include <Quizes/MultiplexQuizRunner.hpp>
#include <Quizes/MultiplexSheetLoader.hpp>
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
#include <Blast/String/Trimmer.hpp>


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
   return;
}

void MultiplexQuizRunner::run()
{
   // initialize
   std::string FOLDER = "/Users/markoates/Repos/me/quizes/discover_canada/csv/";
   std::string OUTPUT_FOLDER = "/Users/markoates/Repos/me/quizes/discover_canada/csv/generated/";
   std::vector<std::string> quiz_files = {
      "Canada Flash Cards - Capitals.tsv",
      "Canada Flash Cards - Formation.tsv",
      "Canada Flash Cards - History1.tsv",
      "Canada Flash Cards - Provinces-P2.tsv",
      "Canada Flash Cards - Provinces.tsv",
      "Canada Flash Cards - Representatives.tsv",
      "Canada Flash Cards - Symbols Heros.tsv",
      "Canada Flash Cards - 3rd Party Questions.tsv",
   };

   for (auto &quiz_file : quiz_files)
   {
      std::string QUIZ_FILE = FOLDER + quiz_file;
      std::string file_contents = get_file_contents(QUIZ_FILE);

      Quizes::MultiplexSheetLoader loader(file_contents);
      loader.load();
      question_pool = loader.get_questions();

      // write relevance:
      {
         Quizes::MultiplexQuestionCollectionHelper collection_helper(question_pool);
         std::vector<Quizes::MultiplexQuestion> date_questions = collection_helper.select_with_relevance();
         std::string QUIZ_YAML_OUTPUT_FILE = OUTPUT_FOLDER + quiz_file + "-relevance.yml";
         std::string yaml_formatted = format_for_quiz_yaml_relevance(date_questions);
         write_file_contents(QUIZ_YAML_OUTPUT_FILE, yaml_formatted);
      }

      // write dates
      {
         Quizes::MultiplexQuestionCollectionHelper collection_helper(question_pool);
         std::vector<Quizes::MultiplexQuestion> date_questions = collection_helper.select_with_dates();
         std::string QUIZ_YAML_OUTPUT_FILE = OUTPUT_FOLDER + quiz_file + "-dates.yml";
         std::string yaml_formatted = format_for_quiz_yaml_date(date_questions);
         write_file_contents(QUIZ_YAML_OUTPUT_FILE, yaml_formatted);
      }
   }


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
      std::vector<std::string> relevance_options = split_trim_and_shuffle_by_semicolon(sanitize_quotes(question.get_relevance()));
      int num_options = relevance_options.size();
      std::string relevance = Blast::StringJoiner(relevance_options, "; ").join();

      output << "  \"" << subject << "";
        if (num_options >= 1) output << " (pick " << num_options << ")";
      output << " (page " << reference_page << ")\":" << std::endl;
      output << "    - \"[select here]" << "\"" << std::endl;
      for (auto &option : relevance_options)
      {
         output << "    - \"" << option << "\"" << std::endl;
      }
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

std::vector<std::string> MultiplexQuizRunner::split_trim_and_shuffle_by_semicolon(std::string str)
{
   std::vector<std::string> tokens = Blast::StringSplitter(str, ';').split();

   for (auto &token : tokens)
   {
      token = trim(token);
   }

   std::random_device rng;
   std::mt19937 urng(rng());
   std::shuffle(tokens.begin(), tokens.end(), urng);

   return tokens;
}

std::string MultiplexQuizRunner::trim(std::string str)
{
   return Blast::String::Trimmer(str).trim();
}
} // namespace Quizes


