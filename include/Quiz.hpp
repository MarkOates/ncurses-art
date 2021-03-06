#pragma once


#include <Question.hpp>
#include <vector>


class Quiz
{
private:
   std::vector<Question> questions;

public:
   Quiz(std::vector<Question> questions={});
   ~Quiz();

   void set_questions(std::vector<Question> questions);
   std::vector<Question> get_questions();
   void shuffle_questions();
};



