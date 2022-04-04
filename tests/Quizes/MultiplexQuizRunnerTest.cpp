
#include <gtest/gtest.h>

#include <Quizes/MultiplexQuizRunner.hpp>


#define QUIZ_FILE = "/Users/markoates/Repos/me/quizes/discover_canada/csv/Canada Flash Cards - Sheet2.csv";



TEST(Quizes_MultiplexQuizRunnerTest, can_be_created_without_blowing_up)
{
   Quizes::MultiplexQuizRunner multiplex_quiz_runner;
}


TEST(Quizes_MultiplexQuizRunnerTest, run__returns_the_expected_response)
{
   Quizes::MultiplexQuizRunner multiplex_quiz_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, multiplex_quiz_runner.run());
}

