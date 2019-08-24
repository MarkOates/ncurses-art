
#include <gtest/gtest.h>

#include <GithubRepoStatusFetcher.hpp>

TEST(GithubRepoStatusFetcherTest, run__returns_the_expected_response)
{
   GithubRepoStatusFetcher fetcher;

   std::string expected_output = "On branch master\nYour branch is up to date with 'origin/master'.\n\nnothing to commit (use -u to show untracked files)\n";

   EXPECT_EQ(expected_output, fetcher.is_the_repo_in_sync_with_remote());
}

// when no repo is present, raises exception

// when repo is present, returns the status

