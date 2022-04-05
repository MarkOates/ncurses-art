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
      std::string format_for_quiz_yaml(std::vector<Quizes::MultiplexQuestion> questions={});
      void write_file_contents(std::string filename="", std::string file_contents="");
      std::string get_file_contents(std::string filename="no-file.txt");
   };
}



