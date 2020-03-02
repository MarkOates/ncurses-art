
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::IsSubsetOf;

#include <ProjectListBuilder.hpp>

TEST(ProjectListBuilderTest, get_directories__returns_a_list_of_folders_in_the_directory)
{
   ProjectListBuilder program_runner;
   std::vector<std::string> some_expected_directories = {
      "allegro_flare",
      "beebot",
      "HomeServer",
      ".dotfiles",
      "googletest",
      "blast",
      "fullscore",
      "first_vim_plugin",
      "ncurses-art",
   };

   std::vector<std::string> actual_directories = program_runner.get_directories();

   EXPECT_THAT(some_expected_directories, IsSubsetOf(actual_directories));
}
