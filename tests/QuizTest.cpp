
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
