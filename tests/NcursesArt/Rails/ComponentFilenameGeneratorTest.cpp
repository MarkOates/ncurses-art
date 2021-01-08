
#include <gtest/gtest.h>

#include <NcursesArt/Rails/ComponentFilenameGenerator.hpp>

TEST(NcursesArt_Rails_ComponentFilenameGeneratorTest, can_be_created_without_blowing_up)
{
   NcursesArt::Rails::ComponentFilenameGenerator component_filename_generator;
}

TEST(NcursesArt_Rails_ComponentFilenameGeneratorTest, run__returns_the_expected_response)
{
   NcursesArt::Rails::ComponentFilenameGenerator component_filename_generator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, component_filename_generator.run());
}
