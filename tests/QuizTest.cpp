
#include <gtest/gtest.h>

#include <Quiz.hpp>

TEST(QuizTest, run__returns_the_expected_response)
{
   Quiz program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
