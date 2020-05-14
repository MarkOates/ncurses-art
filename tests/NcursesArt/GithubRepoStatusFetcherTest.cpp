
#include <gtest/gtest.h>

#include <NcursesArt/GithubRepoStatusFetcher.hpp>

using NcursesArt::GithubRepoStatusFetcher;

TEST(GithubRepoStatusFetcherTest,
   get_current_branch_name_command__returns_the_shell_command_to_obtain_the_current_branch)
{
   GithubRepoStatusFetcher fetcher("blast");
   std::string expected_shell_command = "(cd ~/Repos/blast && git fetch && git branch | grep \\* | cut -d ' ' -f2)";
   EXPECT_EQ(expected_shell_command, fetcher.get_current_branch_name_command());
}

TEST(GithubRepoStatusFetcherTest, get_git_pull_commnd__returns_the_shell_command_to_pull_the_repo)
{
   GithubRepoStatusFetcher fetcher("blast");
   std::string expected_shell_command = "git pull";
   EXPECT_EQ(expected_shell_command, fetcher.get_git_pull_command());
}

TEST(GithubRepoStatusFetcherTest, get_pull_commnd__returns_the_shell_command_to_pull_the_repo)
{
   GithubRepoStatusFetcher fetcher("blast");
   std::string expected_shell_command = "(cd ~/Repos/blast && git fetch && git pull)";
   EXPECT_EQ(expected_shell_command, fetcher.get_pull_command());
}

TEST(GithubRepoStatusFetcherTest,
   get_current_staged_files_command__returns_the_shell_command_to_obtain_the_list_of_staged_files)
{
   GithubRepoStatusFetcher fetcher("blast");
   // from https://stackoverflow.com/a/33610683/607236
   std::string expected_shell_command = "git diff --name-only --cached";
   EXPECT_EQ(expected_shell_command, fetcher.get_git_current_staged_files_command());
}

//TEST(GithubRepoStatusFetcherTest, get_current_staged_files__returns_a_list_of_current_staged_files)
//{
   //std::vector<std::string> expected_staged_files = {
      //"include/NcursesArt/GithubRepoStatusFetcher.hpp",
      //"quintessence/NcursesArt/GithubRepoStatusFetcher.q.yml",
      //"src/NcursesArt/GithubRepoStatusFetcher.cpp",
      //"tests/NcursesArt/GithubRepoStatusFetcherTest.cpp",
   //};
   //GithubRepoStatusFetcher fetcher("ncurses-art");
   //EXPECT_EQ(expected_staged_files, fetcher.get_current_staged_files());
//}

//TEST(GithubRepoStatusFetcherTest, execute_command__is_able_to_find_the_path_specificed)
//{
   //GithubRepoStatusFetcher fetcher("blast");
   //std::string shell_command = "(cd ~/Repos/blast && git fetch && git branch | grep \\* | cut -d ' ' -f2)";
   //std::string expected_command_result = "master\n";

   //EXPECT_EQ(expected_command_result, fetcher.execute_command(shell_command));
//}

//TEST(GithubRepoStatusFetcherTest, is_current_branch_master__returns_true_if_the_current_branch_is_set_to_master)
//{
   //GithubRepoStatusFetcher fetcher("adventures-of-beary");
   //EXPECT_EQ(true, fetcher.is_current_branch_master());
//}

//TEST(GithubRepoStatusFetcherTest, branch_names_at_remote__returns_a_sorted_list_of_branch_names_at_remote)
//{
   //GithubRepoStatusFetcher fetcher("adventures-of-beary");
   //std::vector<std::string> expected_branch_names_at_remote = {
      //"origin/fix-missing-tilemap",
      //"origin/master",
   //};
   //EXPECT_EQ(expected_branch_names_at_remote, fetcher.get_branch_names_at_remote());
//}

//TEST(GithubRepoStatusFetcherTest, run__returns_the_expected_response)
//{
   //GithubRepoStatusFetcher fetcher("hexagon");
   //EXPECT_EQ(true, fetcher.is_the_repo_in_sync_with_remote());
//}

//TEST(GithubRepoStatusFetcherTest, local_repo_exists__returns_false_if_a_repo_is_not_present)
//{
   //GithubRepoStatusFetcher fetcher("a-repo-that-surely-does-not-exist");
   //EXPECT_EQ(false, fetcher.local_repo_exists());
//}

//TEST(GithubRepoStatusFetcherTest, local_repo_exists__returns_true_if_a_repo_is_not_present)
//{
   //GithubRepoStatusFetcher fetcher("ncurses-art");
   //EXPECT_EQ(true, fetcher.local_repo_exists());
//}

//TEST(GithubRepoStatusFetcherTest, is_the_local_repo_ahead__returns_true_if_the_repo_is_ahead_of_the_remote)
//{
   //GithubRepoStatusFetcher fetcher("ncurses-art");
   //EXPECT_EQ(true, fetcher.is_the_local_repo_ahead());
//}

//TEST(GithubRepoStatusFetcherTest, is_the_local_repo_behind__returns_true_if_the_repo_is_behind_remote)
//{
   //GithubRepoStatusFetcher fetcher("beebot");
   //EXPECT_EQ(true, fetcher.is_the_local_repo_behind());
//}

//TEST(GithubRepoStatusFetcherTest, has_file_changes__returns_true_if_there_are_files_in_the_repo_not_staged_for_commit)
//{
   //GithubRepoStatusFetcher fetcher("fullscore");
   //EXPECT_EQ(true, fetcher.has_file_changes());
//}

//TEST(GithubRepoStatusFetcherTest, has_file_changes__returns_false_if_there_are_files_in_the_repo_not_staged_for_commit)
//{
   //GithubRepoStatusFetcher fetcher("blast");
   //EXPECT_EQ(false, fetcher.has_file_changes());
//}

//TEST(GithubRepoStatusFetcherTest, has_untracked_files__returns_true_if_untracked_files_are_present_in_the_repo)
//{
   //GithubRepoStatusFetcher fetcher("ncurses-art");
   //EXPECT_EQ(true, fetcher.has_untracked_files());
//}

//TEST(GithubRepoStatusFetcherTest, has_untracked_files__returns_false_if_untracked_files_are_present_in_the_repo)
//{
   //GithubRepoStatusFetcher fetcher("blast");
   //EXPECT_EQ(false, fetcher.has_untracked_files());
//}

//TEST(GithubRepoStatusFetcherTest, have_the_local_and_remote_repos_diverged__returns_true_if_branches_have_diverged)
//{
   //GithubRepoStatusFetcher fetcher("blast");
   //EXPECT_EQ(true, fetcher.have_the_local_and_remote_repos_diverged());
//}

//TEST(GithubRepoStatusFetcherTest, have_the_local_and_remote_repos_diverged__returns_false_if_branches_have_not_diverged)
//{
   //GithubRepoStatusFetcher fetcher("ncurses-art");
   //EXPECT_EQ(false, fetcher.have_the_local_and_remote_repos_diverged());
//}

//TEST(GithubRepoStatusFetcherTest, branch_count__returns_the_number_of_branches_in_the_repo)
//{
   //GithubRepoStatusFetcher fetcher("fullscore");
   //EXPECT_EQ(2, fetcher.get_branch_count());
//}

//TEST(GithubRepoStatusFetcherTest, get_current_branch_name__returns_the_branch_that_is_currently_active_in_the_repo)
//{
   //std::string expected_current_branch_name = "my-extra-branch\n";
   //GithubRepoStatusFetcher fetcher("fullscore");
   //EXPECT_EQ(expected_current_branch_name, fetcher.get_current_branch_name());
//}

//TEST(GithubRepoStatusFetcherTest, get_quintessence_filenames__returns_a_list_of_components)
//{
   //std::vector<std::string> expected_quintessence_files = {
      //"quintessence/GithubRepoStatusFetcher.q.yml",
      //"quintessence/ProjectListBuilder.q.yml",
      //"quintessence/Checkbox.q.yml",
      //"quintessence/Quiz.q.yml",
      //"quintessence/ProjectComponentListBuilder.q.yml",
      //"quintessence/LivenessCheck.q.yml",
      //"quintessence/QuizYAMLLoader.q.yml",
      //"quintessence/Question.q.yml",
      //"quintessence/StringSplitter.q.yml",
   //};
   //GithubRepoStatusFetcher fetcher("ncurses-art");
   //EXPECT_EQ(expected_quintessence_files, fetcher.get_quintessence_filenames());
//}
