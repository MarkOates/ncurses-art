#include <gtest/gtest.h>

#include <ncurses_art/Element/Frame.hpp>

TEST(FrameTest, can_be_created)
{
   Frame frame(0.0, 0.0, 10.0, 10.0);
}

TEST (FrameTest, has_the_expected_type)
{
   Frame frame(0.0, 0.0, 10.0, 10.0);
   EXPECT_EQ("Frame", frame.get_type());
}


