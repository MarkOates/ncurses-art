
#include <gtest/gtest.h>

#include <GithubRepoStatusFetcher.hpp>

TEST(GithubRepoStatusFetcherTest, run__returns_the_expected_response)
{
   GithubRepoStatusFetcher program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
