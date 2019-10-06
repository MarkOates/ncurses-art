
#include <gtest/gtest.h>

#include <StringVectorIntersection.hpp>

TEST(StringVectorIntersectionTest, run__returns_the_expected_response)
{
   StringVectorIntersection program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
