
#include <gtest/gtest.h>

#include <Checkbox.hpp>

TEST(CheckboxTest, run__returns_the_expected_response)
{
   Checkbox program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
