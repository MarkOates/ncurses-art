
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq; // <<< --- this assertion matcher needs to be updated
using ::testing::Contains; // <<< --- this assertion matcher needs to be updated

#include <HostnameExtractor.hpp>

TEST(HostnameExtractorTest, can_be_created_without_arguments)
{
   HostnameExtractor hostname_extractor;
}

TEST(HostnameExtractorTest, get_computer_name__returns_the_expected_response)
{
   HostnameExtractor hostname_extractor;

   std::vector<std::string> expected_possible_strings = {
      "DESKTOP-NC9M1BH",
      "Marks-Mac-mini.local",
      "Mark-Oates-MacBook-Pro.local",
      "Marks-13-MacBook-Pro.local",
   };
   std::string actual_computer_name = hostname_extractor.get_computer_name();

   EXPECT_THAT(expected_possible_strings, Contains(actual_computer_name));
}
