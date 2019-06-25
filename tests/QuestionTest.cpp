
#include <gtest/gtest.h>

#include <Question.hpp>

TEST(QuestionTest, run__returns_the_expected_response)
{
   Question program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
