
#include <gtest/gtest.h>

#include <GithubRepoStatusFetcher.hpp>

TEST(GithubRepoStatusFetcherTest, run__returns_the_expected_response)
{
   GithubRepoStatusFetcher fetcher;
   EXPECT_EQ(true, fetcher.is_the_repo_in_sync_with_remote());
}

TEST(GithubRepoStatusFetcherTest, is_the_local_repo_ahead__returns_true_if_the_repo_is_ahead_of_the_remote)
{
   GithubRepoStatusFetcher fetcher("ncurses-art");
   EXPECT_EQ(true, fetcher.is_the_local_repo_ahead());
}

TEST(GithubRepoStatusFetcherTest, local_repo_exists__returns_false_if_a_repo_is_not_present)
{
   GithubRepoStatusFetcher fetcher("a-repo-that-surely-does-not-exist");
   EXPECT_EQ(false, fetcher.local_repo_exists());
}

TEST(GithubRepoStatusFetcherTest, local_repo_exists__returns_true_if_a_repo_is_not_present)
{
   GithubRepoStatusFetcher fetcher("ncurses-art");
   EXPECT_EQ(true, fetcher.local_repo_exists());
}

// when no repo is present, raises exception

// when repo is present, returns the status

