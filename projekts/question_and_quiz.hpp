
#include <string>
#include <vector>
#include <random>
#include <ctime>


class Question
{
private:
   std::string question;
   std::string image_filename;
   std::string correct_answer;
   std::vector<std::string> incorrect_answers;

public:
   Question(std::string question="", std::string image_filename="", std::string correct_answer="", std::vector<std::string> incorrect_answers={});
   ~Question();

   void set_question(std::string question);
   void set_correct_answer(std::string correct_answer);
   void set_incorrect_answers(std::vector<std::string> incorrect_answers);

   std::string get_question();
   std::string get_image_filename();
   std::string get_correct_answer();
   std::vector<std::string> get_incorrect_answers();
};


#pragma once


//#include <Blast/Question.hpp>
#include <vector>


class Quiz
{
private:
   std::vector<Question> questions;

public:
   Quiz();
   ~Quiz();

   void set_questions(std::vector<Question> questions);
   void shuffle_questions();

   std::vector<Question> get_questions();
};





//#include <Blast/Question.hpp>




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






//#include <Blast/Quiz.hpp>




Quiz::Quiz()
   : questions()
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


