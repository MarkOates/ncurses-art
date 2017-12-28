#include <gtest/gtest.h>

#include <ncurses_art/Menu.h>

TEST(MenuTest, can_be_created)
{
   Menu menu(10.0f, 10.0f, { "Option1", "Option2" });
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
