#pragma once


#include <string>
#include <vector>


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
   void set_image_filename(std::string image_filename);
   void set_correct_answer(std::string correct_answer);
   void set_incorrect_answers(std::vector<std::string> incorrect_answers);
   std::string get_question();
   std::string get_image_filename();
   std::string get_correct_answer();
   std::vector<std::string> get_incorrect_answers();
};



