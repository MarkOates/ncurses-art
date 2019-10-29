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

TEST(ProgressBarTest, can_get_an_set_the_value)
{
   ProgressBar progress_bar(0.0, 0.0, 10.0, 10.0);

   float expected_value = 0.0;

   EXPECT_EQ(expected_value, progress_bar.get_value());

   expected_value = 1.0;
   progress_bar.set_value(expected_value);
   EXPECT_EQ(expected_value, progress_bar.get_value());

   expected_value = 0.332;
   progress_bar.set_value(expected_value);
   EXPECT_EQ(expected_value, progress_bar.get_value());

   expected_value = 0.897;
   progress_bar.set_value(expected_value);
   EXPECT_EQ(expected_value, progress_bar.get_value());
}

