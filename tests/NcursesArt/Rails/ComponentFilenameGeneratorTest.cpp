
#include <gtest/gtest.h>

#include <NcursesArt/Rails/ComponentFilenameGenerator.hpp>

TEST(NcursesArt_Rails_ComponentFilenameGeneratorTest, can_be_created_without_blowing_up)
{
   NcursesArt::Rails::ComponentFilenameGenerator component_filename_generator;
}

TEST(NcursesArt_Rails_ComponentFilenameGeneratorText, component_basename__has_a_getter_and_is_set_with_the_default_value)
{
   NcursesArt::Rails::ComponentFilenameGenerator component_filename_generator;
   std::string expected_default_value = "unnamed/component";
   std::string actual_default_value = component_filename_generator.get_component_basename();
   EXPECT_EQ(expected_default_value, actual_default_value);
}

TEST(NcursesArt_Rails_ComponentFilenameGeneratorTest, get_model_filename__returns_the_expected_response)
{
   std::string component_name = "namespaced/component_name";
   NcursesArt::Rails::ComponentFilenameGenerator component_filename_generator(component_name);
   std::string expected_string = "app/models/namespaced/component_name.rb";
   EXPECT_EQ(expected_string, component_filename_generator.get_model_filename());
}
