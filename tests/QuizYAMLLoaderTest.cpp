
#include <gtest/gtest.h>

#include <QuizYAMLLoader.hpp>

// Tip: Examples of cpp-yaml testing techniques here:
// https://github.com/jbeder/yaml-cpp/blob/master/test/node/node_test.cpp

TEST(QuizYAMLLoaderTest, get_type_string__returns_the_expected_value)
{
   QuizYAMLLoader quiz_yaml_loader;

   YAML::Node node = YAML::Load("[1, 2, 3]");
   EXPECT_EQ("Sequence", quiz_yaml_loader.get_type_string(node));
}

TEST(QuizYAMLLoaderTest, load_and_append__opens_the_contents_of_the_expected_test_file)
{
   std::string quiz_filename = "tests/fixtures/quiz.yml";
   Quiz quiz;
   
   QuizYAMLLoader quiz_yaml_loader(&quiz, quiz_filename);

   EXPECT_TRUE(quiz_yaml_loader.load_and_append());

   Question expected_question{
      "The speed limit approaching a school crosswalk is",
      "",
      "15 mph",
      { "20 mph", "25 mph" },
   };

   std::vector<Question> actual_quiz_questions = quiz.get_questions();

   EXPECT_EQ(2, actual_quiz_questions.size());

   Question first_question = actual_quiz_questions[0];

   EXPECT_EQ(expected_question.get_question(), first_question.get_question());
   EXPECT_EQ(expected_question.get_image_filename(), first_question.get_image_filename());
   EXPECT_EQ(expected_question.get_correct_answer(), first_question.get_correct_answer());
   EXPECT_EQ(expected_question.get_incorrect_answers(), first_question.get_incorrect_answers());

   Question expected_second_question{
      "The Pythagorean Theorem is",
      "",
      "a^2 + b^2 = c^2",
      { "E = MC^2", "1 = 1" },
   };

   Question second_question = actual_quiz_questions[1];

   EXPECT_EQ(expected_second_question.get_question(), second_question.get_question());
   EXPECT_EQ(expected_second_question.get_image_filename(), second_question.get_image_filename());
   EXPECT_EQ(expected_second_question.get_correct_answer(), second_question.get_correct_answer());
   EXPECT_EQ(expected_second_question.get_incorrect_answers(), second_question.get_incorrect_answers());
}

TEST(QuizYAMLLoaderTest, load_and_append__will_append_the_questions_to_the_quiz)
{
   // TODO
}

