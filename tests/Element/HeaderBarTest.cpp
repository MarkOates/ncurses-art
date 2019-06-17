#include <gtest/gtest.h>

#include <ncurses_art/Element/HeaderBar.hpp>

TEST(HeaderBarTest, can_be_created)
{
   HeaderBar header_bar;
}

TEST (HeaderBarTest, has_the_expected_type)
{
   HeaderBar header_bar;
   EXPECT_EQ("HeaderBar", header_bar.get_type());
}
