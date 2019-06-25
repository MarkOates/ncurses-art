

#include <Quiz.hpp>





Quiz::Quiz()
   : questions({})
{
}


Quiz::~Quiz()
{
}


void Quiz::set_questions(std::vector<Question> questions)
{
   this->questions = questions;
}


std::vector<Question> Quiz::get_questions()
{
   return questions;
}


void Quiz::shuffle_questions()
{
return;
}


