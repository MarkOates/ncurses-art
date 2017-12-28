#include <gtest/gtest.h>

#include <ncurses_art/Text.h>

TEST(TextTest, can_be_created)
{
   Text text("Hello World", 10.0f, 10.0f);
}
