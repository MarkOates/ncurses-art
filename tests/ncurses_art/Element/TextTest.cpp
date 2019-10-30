#include <gtest/gtest.h>

#include <ncurses_art/Element/Text.hpp>

TEST(TextTest, can_be_created)
{
   Text text("Hello World", 10.0f, 10.0f);
}

TEST (TextTest, has_the_expected_type)
{
   Text text("Hello World", 10.0f, 10.0f);
   EXPECT_EQ("Text", text.get_type());
}

TEST (TextTest, can_get_and_set_x)
{
   Text text("Hello World", 10.0f, 10.0f);
   EXPECT_EQ(10.0f, text.get_x());
   ASSERT_TRUE(text.set_x(1234.0f));
   EXPECT_EQ(1234.0f, text.get_x());
   ASSERT_TRUE(text.set_x(-99.0f));
   EXPECT_EQ(-99.0f, text.get_x());
}

TEST (TextTest, can_get_and_set_y)
{
   Text text("Hello World", 10.0f, 10.0f);
   EXPECT_EQ(10.0f, text.get_y());
   ASSERT_TRUE(text.set_y(1234.0f));
   EXPECT_EQ(1234.0f, text.get_y());
   ASSERT_TRUE(text.set_y(-99.0f));
   EXPECT_EQ(-99.0f, text.get_y());
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

TEST (TextTest, can_get_and_set_align_x)
{
   Text text("Hello World", 10.0f, 10.0f);
   EXPECT_EQ(0.0f, text.get_align_x());
   ASSERT_TRUE(text.set_align_x(1.0f));
   EXPECT_EQ(1.0f, text.get_align_x());
   ASSERT_TRUE(text.set_align_x(-0.5f));
   EXPECT_EQ(-0.5f, text.get_align_x());
}

TEST (TextTest, can_get_and_set_align_y)
{
   Text text("Hello World", 10.0f, 10.0f);
   EXPECT_EQ(0.0f, text.get_align_y());
   ASSERT_TRUE(text.set_align_y(1.0f));
   EXPECT_EQ(1.0f, text.get_align_y());
   ASSERT_TRUE(text.set_align_y(-0.5f));
   EXPECT_EQ(-0.5f, text.get_align_y());
}

