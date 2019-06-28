
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

TEST(QuizYAMLLoaderTest, load__opens_a_file)
{
   QuizYAMLLoader quiz_yaml_loader;

   YAML::Node response = quiz_yaml_loader.load();
   YAML::Node expected_response = YAML::Load("Hello World!");

   EXPECT_EQ(expected_response.as<std::string>(), response.as<std::string>());
}
