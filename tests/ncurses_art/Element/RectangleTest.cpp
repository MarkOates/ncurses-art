#include <gtest/gtest.h>

#include <ncurses_art/Element/Rectangle.hpp>

TEST(RectangleTest, can_be_created)
{
   Rectangle rectangle(0.0, 0.0, 10.0, 10.0);
}

TEST (RectangleTest, has_the_expected_type)
{
   Rectangle rectangle(0.0, 0.0, 10.0, 10.0);
   EXPECT_EQ("Rectangle", rectangle.get_type());
}
