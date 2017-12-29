#include <gtest/gtest.h>

#include <ncurses_art/Element/Text.h>

TEST(TextTest, can_be_created)
{
   Text text("Hello World", 10.0f, 10.0f);
}

TEST (TextTest, has_the_expected_type)
{
   Text text("Hello World", 10.0f, 10.0f);
   EXPECT_EQ("Text", text.get_type());
}
