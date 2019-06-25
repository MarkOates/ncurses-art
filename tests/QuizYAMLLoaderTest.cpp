
#include <gtest/gtest.h>

#include <QuizYAMLLoader.hpp>

TEST(QuizYAMLLoaderTest, run__returns_the_expected_response)
{
   QuizYAMLLoader quiz_yaml_loader;
   EXPECT_TRUE(quiz_yaml_loader.load());
}
