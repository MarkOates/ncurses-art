
#include <gtest/gtest.h>

#include <StringTrimmer.hpp>


TEST(StringTrimmerTest, can_be_created_without_arguments)
{
   StringTrimmer trimmer;
}


TEST(StringTrimmerTest, trim__returns_the_string_with_leading_and_trailing_whitespace_removed)
{
   std::string untrimmed_string = " \n  \t  This is the string  \t\n";
   StringTrimmer trimmer(untrimmed_string);

   std::string expected_trimmed_string = "This is the string";
   EXPECT_EQ(expected_trimmed_string, trimmer.trim());
}


