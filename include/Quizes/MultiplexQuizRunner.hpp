#pragma once


#include <Quizes/MultiplexQuestion.hpp>
#include <string>
#include <vector>


namespace Quizes
{
   class MultiplexQuizRunner
   {
   private:
      std::vector<Quizes::MultiplexQuestion> question_pool;

   public:
      MultiplexQuizRunner();
      ~MultiplexQuizRunner();

      void initialize();
      void run();
      std::string format_for_quiz_yaml_date(std::vector<Quizes::MultiplexQuestion> questions={});
      std::string format_for_quiz_yaml_relevance(std::vector<Quizes::MultiplexQuestion> questions={});
      void write_file_contents(std::string filename="", std::string file_contents="");
      std::string get_file_contents(std::string filename="no-file.txt");
      std::string sanitize_quotes(std::string str="");
      std::vector<std::string> split_trim_and_shuffle_by_semicolon(std::string str="");
      std::string trim(std::string str="");
   };
}



