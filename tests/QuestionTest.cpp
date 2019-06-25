
#include <gtest/gtest.h>

#include <Question.hpp>

TEST(QuestionTest, run__returns_the_expected_response)
{
   std::string expected_question = "This is the question";
   std::string expected_image = "https://www.google.com/image.jpg";
   std::string correct_answer = "This is the correct answer";
   std::vector<std::string> incorrect_answers = {
      "This is one wrong answer",
      "This is another wrong answer",
   };

   Question question(expected_question, expected_image, correct_answer, incorrect_answers);

   EXPECT_EQ(expected_question, question.get_question());
   EXPECT_EQ(expected_image, question.get_image_filename());
   EXPECT_EQ(correct_answer, question.get_correct_answer());
   EXPECT_EQ(incorrect_answers, question.get_incorrect_answers());
}
