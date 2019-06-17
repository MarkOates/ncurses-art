
#include <gtest/gtest.h>

#include <ProjectListBuilder.hpp>

TEST(ProjectListBuilderTest, list__returns_a_response)
{
   ProjectListBuilder program_runner;
   std::vector<std::string> expected_string = { "Hello World!", "Hello Buddy!" };
   EXPECT_EQ(expected_string, program_runner.list());
}

TEST(ProjectListBuilderTest, get_directories__returns_a_list_of_folders_in_the_directory)
{
   ProjectListBuilder program_runner;
   std::vector<std::string> expected_string = {
      "allegro_flare",
      "macmidi",
      "vim_syntax_hilighting",
      "beebot",
      "99bottles-1",
      "gmail-api",
      "ThisIsMyGeneratedThingDelete",
      "EraseMe",
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
   EXPECT_EQ(expected_string, program_runner.get_directories());
}
