
#include <gtest/gtest.h>

#include <StringVectorIntersection.hpp>

TEST(StringVectorIntersectionTest, run__returns_the_expected_response)
{
   StringVectorIntersection intersector;

   std::vector<std::string> v1 = { "a", "x", "b", "c", "d", "e" };
   std::vector<std::string> v2 = { "c", "a", "j", "k", "x" };

   std::vector<std::string> expected_intersection = { "a", "c", "x" };

   EXPECT_EQ(expected_intersection, intersector.intersection());
}
