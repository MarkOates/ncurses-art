
#include <gtest/gtest.h>

#include <ProjectListBuilder.hpp>

TEST(ProjectListBuilderTest, run__returns_the_expected_response)
{
   ProjectListBuilder program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
