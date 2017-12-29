#include <gtest/gtest.h>

#include <ncurses_art/Element/Rectangle.h>

TEST(RectangleTest, can_be_created)
{
   Rectangle rectangle(0.0, 0.0, 10.0, 10.0);
}
