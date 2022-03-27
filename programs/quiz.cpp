#include "Projekt2.h"

#include <algorithm>
#include <ctime>
#include <random>

#include "Question.hpp"
#include "Quiz.hpp"
#include "QuizYAMLLoader.hpp"


#define INITIALIZE "INITIALIZE"
#define GUESS_ANSWER "GUESS_ANSWER"
#define ROTATE_QUESTION "ROTATE_QUESTION"
#define MOVE_MENU_DOWN "MOVE_MENU_DOWN"
#define MOVE_MENU_UP "MOVE_MENU_UP"
#define OPEN_IMAGE "OPEN_IMAGE"


int current_question_index = -1;
bool quiz_finished = false;

Quiz quiz;
std::vector<std::string> quiz_filenames;


Question get_current_question()
{
   return quiz.get_questions()[current_question_index];
}


void load_quiz_questions(Quiz &q, std::string quiz_yaml_filename)
{
   QuizYAMLLoader quiz_yaml_loader(&q, quiz_yaml_filename);
   quiz_yaml_loader.load_and_append();

   quiz.shuffle_questions();
}


#include <iostream>


void initialize()
{
   if (args.size() <= 1) throw std::runtime_error("You must run this quiz with a filename as a command-line arg.");

   for (int i=1; i<args.size(); i++)
   {
      quiz_filenames.push_back(args[i]);
   }

   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);

   create_text("question", 20, 8);
   create_menu("answers", 30, 12).set_styles(COLOR_PAIR(3));

   create_text("status", 30, 5, 0.5);

   mappings['\n'] = GUESS_ANSWER;
   mappings['j'] = MOVE_MENU_DOWN;
   mappings['k'] = MOVE_MENU_UP;
   mappings['o'] = OPEN_IMAGE;

   events[INITIALIZE] = []{
      for (auto &quiz_filename : quiz_filenames)
      {
         load_quiz_questions(quiz, quiz_filename);
      }
      current_question_index = -1;
      quiz_finished = false;
      emit_event(ROTATE_QUESTION);
   };
   events[ROTATE_QUESTION] = []{
      current_question_index++;
      int current_correct_answer_num = rand() % 3;

      auto current_question = get_current_question();

      std::vector<std::string> answers = current_question.get_incorrect_answers();
      answers.push_back(current_question.get_correct_answer());

      std::random_device rd;
      std::mt19937 g(rd());
      std::shuffle(answers.begin(), answers.end(), g);


      // Shuffle one more time if the first option happens to be the correct answer.
      // This is just to make it more likely that the user will have to read and consider
      // more of the options
      if (!answers.empty())
      {
         if (current_question.get_correct_answer() == answers[0])
            std::shuffle(answers.begin(), answers.end(), g);
      }


      find_text("question").set_text(current_question.get_question());
      find_menu("answers").set_options(answers);

      std::stringstream question_notification;
      question_notification << "Question " << (current_question_index+1) << " of " << quiz.get_questions().size();
      find_text("status").set_text(question_notification.str());
   };
   events[MOVE_MENU_UP] = []{
      find_menu("answers").move_cursor_up();
   };
   events[MOVE_MENU_DOWN] = []{
      find_menu("answers").move_cursor_down();
   };
   events[OPEN_IMAGE] = []{
      auto current_question = get_current_question();
      std::string image_filename = current_question.get_image_filename();
      if (image_filename == "") find_text("status").set_text("No image!");
      else
      {
         std::stringstream command;
         command << "open ./bin/images/" << image_filename;
         system(command.str().c_str());
      }
   };
   events[GUESS_ANSWER] = []{
      auto current_question = get_current_question();
      auto guessed_answer = find_menu("answers").current_selection();

      if (current_question.get_correct_answer() != guessed_answer) emit_event("CRASH!!");

      if (current_question_index == (quiz.get_questions().size()-1))
      {
         quiz_finished = true;
         find_text("status").set_text("FINISHED!");
      }
      else emit_event(ROTATE_QUESTION);
   };

   emit_event(INITIALIZE);
}


