#include <gtest/gtest.h>

#include <ncurses_art/EventTypes.h>

TEST(EventTypesTest, constants_contain_the_expected_values)
{
   ASSERT_EQ("abort_program", EVENT_ABORT_PROGRAM);
   ASSERT_EQ("program_initialized", EVENT_PROGRAM_INITIALIZED);
}
