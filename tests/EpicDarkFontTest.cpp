
#include <gtest/gtest.h>

#include <EpicDarkFont.hpp>

TEST(EpicDarkFontTest, run__returns_the_expected_response)
{
   EpicDarkFont program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
