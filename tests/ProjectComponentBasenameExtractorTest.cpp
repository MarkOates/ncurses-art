
#include <gtest/gtest.h>

#include <ProjectComponentBasenameExtractor.hpp>

TEST(ProjectComponentBasenameExtractorTest, run__returns_the_expected_response)
{
   ProjectComponentBasenameExtractor program_runner;
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, program_runner.run());
}
