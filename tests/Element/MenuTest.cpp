#include <gtest/gtest.h>

#include <ncurses_art/Element/Menu.h>

TEST(MenuTest, can_be_created)
{
   Menu menu(10.0f, 10.0f, { "Option1", "Option2" });
}

TEST (MenuTest, has_the_expected_type)
{
   Menu menu(10.0f, 10.0f, { "Option1", "Option2" });
   EXPECT_EQ("Menu", menu.get_type());
}

TEST(MenuTest, can_return_the_current_selection)
{
   Menu menu(0, 0, { "Option1", "Option2", "Option3" });

   ASSERT_EQ("Option1", menu.current_selection());

   menu.move_cursor_down();
   ASSERT_EQ("Option2", menu.current_selection());
   menu.move_cursor_down();
   ASSERT_EQ("Option3", menu.current_selection());
   menu.move_cursor_down();
   ASSERT_EQ("Option1", menu.current_selection());
   menu.move_cursor_down();
   ASSERT_EQ("Option2", menu.current_selection());
   menu.move_cursor_up();
   ASSERT_EQ("Option1", menu.current_selection());
}

TEST(MenuTest, when_containing_no_menu_options_current_selection_is_empty_string)
{
   Menu menu(0, 0, {});

   ASSERT_EQ("", menu.current_selection());
}

TEST(MenuTest, can_set_the_options)
{
   Menu menu(0, 0, { "Option1", "Option2", "Option3" });

   ASSERT_TRUE(menu.set_options({ "OptionA", "OptionB", "OptionC" }));

   ASSERT_EQ("OptionA", menu.current_selection());
   menu.move_cursor_down();
   ASSERT_EQ("OptionB", menu.current_selection());
   menu.move_cursor_down();
   ASSERT_EQ("OptionC", menu.current_selection());
   menu.move_cursor_down();
}

TEST(MenuTest, when_setting_the_options_the_current_selection_becomes_the_first_option)
{
   Menu menu(0, 0, { "Option1", "Option2", "Option3" });

   menu.move_cursor_down();
   menu.move_cursor_down();
   ASSERT_EQ("Option3", menu.current_selection());

   ASSERT_TRUE(menu.set_options({ "OptionA", "OptionB", "OptionC" }));
   ASSERT_EQ("OptionA", menu.current_selection());
}

TEST(MenuTest, can_get_the_x_position)
{
   Menu menu1(0, 0, {});
   ASSERT_EQ(0, menu1.get_x());
   Menu menu2(9, 0, {});
   ASSERT_EQ(9, menu2.get_x());
   Menu menu3(-10, {});
   ASSERT_EQ(-10, menu3.get_x());
}

TEST(MenuTest, can_get_the_y_position)
{
   Menu menu1(0, 0, {});
   ASSERT_EQ(0, menu1.get_y());
   Menu menu2(0, 9, {});
   ASSERT_EQ(9, menu2.get_y());
   Menu menu3(0, -10, {});
   ASSERT_EQ(-10, menu3.get_y());
}
