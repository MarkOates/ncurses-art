
#include <gtest/gtest.h>

#include <QuizYAMLLoader.hpp>

TEST(QuizYAMLLoaderTest, run__returns_the_expected_response)
{
   QuizYAMLLoader program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
