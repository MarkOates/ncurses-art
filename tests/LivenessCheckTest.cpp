
#include <gtest/gtest.h>

#include <LivenessCheck.hpp>

TEST(LivenessCheckTest, run__returns_the_expected_response)
{
   LivenessCheck program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
