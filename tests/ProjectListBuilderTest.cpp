
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

using ::testing::IsSubsetOf;

#include <ProjectListBuilder.hpp>

TEST(ProjectListBuilderTest, get_directories__without_a_repos_directory_that_ends_in_a_slash_throws_an_error)
{
   std::string expected_error_message = "[ProjectListBuilder::get_directories error:] " \
                                        "repos_directory must end in '/' character.";
   ProjectListBuilder program_runner("/Some/directory/that/does/not/end/in/a/slash");
   ASSERT_THROW_WITH_MESSAGE(program_runner.get_directories(), std::runtime_error, expected_error_message);
}

TEST(ProjectListBuilderTest, get_directories__returns_a_list_of_folders_in_the_directory)
{
   ProjectListBuilder program_runner("../");
   std::vector<std::string> some_expected_directories = {
      "union",
      "allegro_flare",
      ".dotfiles",
      "ncurses-art",
   };

   std::vector<std::string> actual_directories = program_runner.get_directories();

   EXPECT_THAT(some_expected_directories, IsSubsetOf(actual_directories));
}
