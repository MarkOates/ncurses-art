
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq; // <<< --- this assertion matcher needs to be updated

#include <HostnameExtractor.hpp>

TEST(HostnameExtractorTest, can_be_created_without_arguments)
{
   HostnameExtractor hostname_extractor;
}

TEST(DISABLED_HostnameExtractorTest, get_computer_name__returns_the_expected_response)
{
   HostnameExtractor hostname_extractor;

   std::string expected_possible_strings = {
      "Marks-Mac-mini.local",
      "Mark-Oates-MacBook-Pro.local",
   };
   std::string actual_computer_name = hostname_extractor.get_computer_name();

   // vvv --- this assertion needs to be updated to ensure the actual matches one of the possible
   //          v actual, v expected
   EXPECT_THAT("foo", Eq("foo"));
}
