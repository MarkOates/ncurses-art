#include <gtest/gtest.h>

#include <ncurses_art/Element/TabSet.h>

TEST(TabSetTest, can_be_created)
{
   TabSet tab_set;
}

TEST (TabSetTest, has_the_expected_type)
{
   TabSet tab_set;
   EXPECT_EQ("TabSet", tab_set.get_type());
}

TEST (TabSetTest, when_initialized_wihout_values_has_expected_defaults)
{
   TabSet tab_set;
   EXPECT_EQ(0.0f, tab_set.get_x());
   EXPECT_EQ(0.0f, tab_set.get_y());
   EXPECT_EQ(std::vector<std::string>(), tab_set.get_tabs());
}

TEST (TabSetTest, can_get_and_set_x)
{
   TabSet tab_set;
   EXPECT_EQ(0.0f, tab_set.get_x());
   ASSERT_TRUE(tab_set.set_x(1234.0f));
   EXPECT_EQ(1234.0f, tab_set.get_x());
   ASSERT_TRUE(tab_set.set_x(-99.0f));
   EXPECT_EQ(-99.0f, tab_set.get_x());
}

TEST (TabSetTest, can_get_and_set_y)
{
   TabSet tab_set;
   EXPECT_EQ(0.0f, tab_set.get_y());
   ASSERT_TRUE(tab_set.set_y(1234.0f));
   EXPECT_EQ(1234.0f, tab_set.get_y());
   ASSERT_TRUE(tab_set.set_y(-99.0f));
   EXPECT_EQ(-99.0f, tab_set.get_y());
}

TEST (TabSetTest, can_get_an_set_tabs)
{
   TabSet tab_set;
   EXPECT_EQ(std::vector<std::string>(), tab_set.get_tabs());
   ASSERT_TRUE(tab_set.set_tabs({ "Tab1", "Tab2" }));
   ASSERT_EQ(std::vector<std::string>({ "Tab1", "Tab2" }), tab_set.get_tabs());
}
