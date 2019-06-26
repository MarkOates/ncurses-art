
#include <gtest/gtest.h>

#include <QuizYAMLLoader.hpp>

TEST(QuizYAMLLoaderTest, get_type_string__returns_the_expected_value)
{
   QuizYAMLLoader quiz_yaml_loader;

   YAML::Node node = YAML::Load("[1, 2, 3]");
   EXPECT_EQ("Sequence", quiz_yaml_loader.get_type_string(node));
}
