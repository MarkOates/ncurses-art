#include <gtest/gtest.h>

#include <ncurses_art/Element/ProgressBar.hpp>

TEST(ProgressBarTest, can_be_created)
{
   ProgressBar progress_bar(0.0, 0.0, 10.0, 10.0);
}

TEST (ProgressBarTest, has_the_expected_type)
{
   ProgressBar progress_bar(0.0, 0.0, 10.0, 10.0);
   EXPECT_EQ("ProgressBar", progress_bar.get_type());
}
