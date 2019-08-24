
#include <gtest/gtest.h>

#include <GithubRepoStatusFetcher.hpp>

TEST(GithubRepoStatusFetcherTest, run__returns_the_expected_response)
{
   GithubRepoStatusFetcher fetcher;
   EXPECT_EQ(true, fetcher.is_the_repo_in_sync_with_remote());
}

// when no repo is present, raises exception

// when repo is present, returns the status

