
#include <gtest/gtest.h>

#include <GithubRepoStatusFetcher.hpp>

TEST(GithubRepoStatusFetcherTest, run__returns_the_expected_response)
{
   GithubRepoStatusFetcher fetcher("hexagon");
   EXPECT_EQ(true, fetcher.is_the_repo_in_sync_with_remote());
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

TEST(GithubRepoStatusFetcherTest, is_the_local_repo_ahead__returns_true_if_the_repo_is_ahead_of_the_remote)
{
   GithubRepoStatusFetcher fetcher("ncurses-art");
   EXPECT_EQ(true, fetcher.is_the_local_repo_ahead());
}

TEST(GithubRepoStatusFetcherTest, is_the_local_repo_behind__returns_true_if_the_repo_is_behind_remote)
{
   GithubRepoStatusFetcher fetcher("beebot");
   EXPECT_EQ(true, fetcher.is_the_local_repo_behind());
}

TEST(GithubRepoStatusFetcherTest, has_file_changes__returns_true_if_there_are_files_in_the_repo_not_staged_for_commit)
{
   GithubRepoStatusFetcher fetcher("fullscore");
   EXPECT_EQ(true, fetcher.has_file_changes());
}

TEST(GithubRepoStatusFetcherTest, has_file_changes__returns_false_if_there_are_files_in_the_repo_not_staged_for_commit)
{
   GithubRepoStatusFetcher fetcher("blast");
   EXPECT_EQ(false, fetcher.has_file_changes());
}

TEST(GithubRepoStatusFetcherTest, has_new_files__returns_true_if_new_files_are_present_in_the_repo)
{
   GithubRepoStatusFetcher fetcher("ncurses-art");
   EXPECT_EQ(true, fetcher.has_new_files());
}

TEST(GithubRepoStatusFetcherTest, has_new_files__returns_false_if_new_files_are_present_in_the_repo)
{
   GithubRepoStatusFetcher fetcher("blast");
   EXPECT_EQ(false, fetcher.has_new_files());
}

