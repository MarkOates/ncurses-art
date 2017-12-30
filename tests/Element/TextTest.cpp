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

TEST (TextTest, can_get_an_set_text)
{
   Text text("Hello World", 0, 0);
   EXPECT_EQ("Hello World", text.get_text());
   ASSERT_TRUE(text.set_text("How is your day?"));
   ASSERT_EQ("How is your day?", text.get_text());
   ASSERT_TRUE(text.set_text("Good, I hope :)"));
   ASSERT_EQ("Good, I hope :)", text.get_text());
}
