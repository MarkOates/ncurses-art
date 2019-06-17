#include <gtest/gtest.h>

#include <ncurses_art/Element/TextInput.hpp>

TEST(TextInputTest, can_be_created)
{
   TextInput text(10.0f, 10.0f, "Hello World");
}

TEST (TextInputTest, has_the_expected_type)
{
   TextInput text(10.0f, 10.0f, "Hello World");
   EXPECT_EQ("TextInput", text.get_type());
}

TEST (TextInputTest, when_initialized_without_arguments_has_the_expected_values)
{
   TextInput text_input;
   EXPECT_EQ(0, text_input.get_x());
   EXPECT_EQ(0, text_input.get_y());
   EXPECT_EQ("", text_input.get_label());
   EXPECT_EQ("", text_input.get_value());
   EXPECT_EQ(60, text_input.get_width());
}

TEST (TextInputTest, can_get_and_set_x)
{
   TextInput text_input;
   ASSERT_TRUE(text_input.set_x(1234.0f));
   EXPECT_EQ(1234.0f, text_input.get_x());
   ASSERT_TRUE(text_input.set_x(-99.0f));
   EXPECT_EQ(-99.0f, text_input.get_x());
}

TEST (TextInputTest, can_get_and_set_y)
{
   TextInput text_input;
   ASSERT_TRUE(text_input.set_y(1234.0f));
   EXPECT_EQ(1234.0f, text_input.get_y());
   ASSERT_TRUE(text_input.set_y(-99.0f));
   EXPECT_EQ(-99.0f, text_input.get_y());
}

TEST (TextInputTest, can_get_and_set_label)
{
   TextInput text_input;

   ASSERT_TRUE(text_input.set_label("How is your day?"));
   ASSERT_EQ("How is your day?", text_input.get_label());
   ASSERT_TRUE(text_input.set_label("Good, I hope :)"));
   ASSERT_EQ("Good, I hope :)", text_input.get_label());
   ASSERT_TRUE(text_input.set_label(""));
   ASSERT_EQ("", text_input.get_label());
}

TEST (TextInputTest, can_get_and_set_value)
{
   TextInput text_input;

   ASSERT_TRUE(text_input.set_value("How is your day?"));
   ASSERT_EQ("How is your day?", text_input.get_value());
   ASSERT_TRUE(text_input.set_value("Good, I hope :)"));
   ASSERT_EQ("Good, I hope :)", text_input.get_value());
   ASSERT_TRUE(text_input.set_value(""));
   ASSERT_EQ("", text_input.get_value());
}

TEST (TextInputTest, can_get_and_set_width)
{
   TextInput text_input(0, 0, "");

   ASSERT_TRUE(text_input.set_width(100));
   ASSERT_EQ(100, text_input.get_width());
   ASSERT_TRUE(text_input.set_width(999));
   ASSERT_EQ(999, text_input.get_width());
}

