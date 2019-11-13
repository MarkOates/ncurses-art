
#include <gtest/gtest.h>

#include <HostnameExtractor.hpp>

TEST(HostnameExtractorTest, run__returns_the_expected_response)
{
   HostnameExtractor program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
