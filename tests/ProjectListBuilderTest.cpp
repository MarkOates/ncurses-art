
#include <gtest/gtest.h>

#include <ProjectListBuilder.hpp>

TEST(ProjectListBuilderTest, run__returns_a_list_of_folders_in_the_directory)
{
   ProjectListBuilder program_runner;
   std::vector<std::string> expected_string = { "Hello World!", "Hello Buddy!" };
   EXPECT_EQ(expected_string, program_runner.list());
}
