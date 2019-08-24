
#include <gtest/gtest.h>

#include <GithubRepoStatusFetcher.hpp>

TEST(GithubRepoStatusFetcherTest, run__returns_the_expected_response)
{
   GithubRepoStatusFetcher fetcher;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}

// when no repo is present, raises exception

// when repo is present, returns the status

