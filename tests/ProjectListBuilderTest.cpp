
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::IsSubsetOf;

#include <ProjectListBuilder.hpp>

TEST(ProjectListBuilderTest, get_directories__returns_a_list_of_folders_in_the_directory)
{
   ProjectListBuilder program_runner;
   std::vector<std::string> some_expected_directories = {
      "allegro_flare",
      "macmidi",
      "vim_syntax_hilighting",
      "beebot",
      "99bottles-1",
      "gmail-api",
      "ueli",
      "vim-testing",
      "HomeServer",
      "flare_network",
      "LilyPond.app",
      ".dotfiles",
      "vim-component-arranger",
      "LilyRenderer",
      "googletest",
      "blast",
      "gpt-2",
      "fullscore",
      "imgcat",
      "first_vim_plugin",
      "ncurses-art",
   };

   std::vector<std::string> actual_directories = program_runner.get_directories();

   EXPECT_THAT(some_expected_directories, IsSubsetOf(actual_directories));
}
