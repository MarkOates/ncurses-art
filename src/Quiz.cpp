

#include <Quiz.hpp>
#include <random>
#include <random>
#include <algorithm>




Quiz::Quiz(std::vector<Question> questions)
   : questions(questions)
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
std::random_device rd;
std::mt19937 g(rd());
std::shuffle(questions.begin(), questions.end(), g);
std::shuffle(questions.begin(), questions.end(), g);

}


