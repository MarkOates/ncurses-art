
#include <gtest/gtest.h>

#include <ProjectComponentListBuilder.hpp>

TEST(ProjectComponentListBuilderTest, run__returns_the_expected_response)
{
   ProjectComponentListBuilder program_runner;
   std::string expected_string = "TODO: Build this class up, similar to ProjectListBuilder";
   EXPECT_EQ(expected_string, program_runner.run());
}
