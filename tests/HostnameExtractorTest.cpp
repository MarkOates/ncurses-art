
#include <gtest/gtest.h>

#include <HostnameExtractor.hpp>

TEST(HostnameExtractorTest, can_be_created_without_arguments)
{
   HostnameExtractor hostname_extractor;
}

TEST(HostnameExtractorTest, get_computer_name__returns_the_expected_response)
{
   HostnameExtractor hostname_extractor;

   std::string expected_string = "Marks-Mac-mini.local";
   std::string actual_computer_name = hostname_extractor.get_computer_name();

   EXPECT_EQ(expected_string, actual_computer_name);
}
