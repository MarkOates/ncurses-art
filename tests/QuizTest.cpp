
#include <gtest/gtest.h>

#include <Quiz.hpp>


TEST(QuizTest, can_be_created)
{
   Quiz quiz;
}


TEST(QuizTest, with_questions_returns_them)
{
   std::vector<Question> questions = { {"A"}, {"B"}, {"C"}, {"D"}, {"E"}, {"F"}, {"G"} };

   Quiz quiz(questions);
   //EXPECT_EQ(questions, quiz.get_questions());
}


TEST(QuizTest, shuffle_questions__will_randomly_shuffle_the_questions)
{
   std::vector<Question> questions = { {"A"}, {"B"}, {"C"}, {"D"}, {"E"}, {"F"}, {"G"} };

   Quiz quiz(questions);
   quiz.shuffle_questions();
}


TEST(QuizTest, append_questions__will_append_questions_to_the_existing_set)
{
   std::vector<Question> questions = { {"A"}, {"B"}, {"C"}, };
   std::vector<Question> questions_to_append = { {"D"}, {"E"}, {"F"}, {"G"} };

   std::vector<Question> expeced_questions = { {"A"}, {"B"}, {"C"}, {"D"}, {"E"}, {"F"}, {"G"} };

   Quiz quiz(questions);
   quiz.append_questions(questions_to_append);
   // TODO: get this collection to compare properly
   //EXPECT_EQ(true, sameset(expeced_questions, quiz.get_questions()));
}


