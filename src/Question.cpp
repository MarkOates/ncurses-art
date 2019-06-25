

#include <Question.hpp>





Question::Question(std::string question, std::string image_filename, std::string correct_answer, std::vector<std::string> incorrect_answers)
   : question(question)
   , image_filename(image_filename)
   , correct_answer(correct_answer)
   , incorrect_answers(incorrect_answers)
{
}


Question::~Question()
{
}


void Question::set_question(std::string question)
{
   this->question = question;
}


void Question::set_image_filename(std::string image_filename)
{
   this->image_filename = image_filename;
}


void Question::set_correct_answer(std::string correct_answer)
{
   this->correct_answer = correct_answer;
}


void Question::set_incorrect_answers(std::vector<std::string> incorrect_answers)
{
   this->incorrect_answers = incorrect_answers;
}


std::string Question::get_question()
{
   return question;
}


std::string Question::get_image_filename()
{
   return image_filename;
}


std::string Question::get_correct_answer()
{
   return correct_answer;
}


std::vector<std::string> Question::get_incorrect_answers()
{
   return incorrect_answers;
}




