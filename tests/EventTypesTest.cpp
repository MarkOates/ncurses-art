#include <gtest/gtest.h>

#include <ncurses_art/EventTypes.h>

TEST(EventTypesTest, constants_contain_the_expected_values)
{
   ASSERT_EQ("abort_program", EVENT_ABORT_PROGRAM);
   ASSERT_EQ("move_cursor_down", EVENT_MOVE_CURSOR_DOWN);
   ASSERT_EQ("move_cursor_up", EVENT_MOVE_CURSOR_UP);
   ASSERT_EQ("choose_current_menu_item", EVENT_CHOOSE_CURRENT_MENU_ITEM);
}
