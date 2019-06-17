#include <gtest/gtest.h>

#include <ncurses_art/Element/TabSet.hpp>

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

TEST (TabSetTest, can_goto_the_next_tab)
{
   TabSet tab_set;
   tab_set.set_tabs({ "Tab1", "Tab2", "Tab3" });

   ASSERT_EQ("Tab1", tab_set.current_tab());
   ASSERT_TRUE(tab_set.goto_next_tab());
   ASSERT_EQ("Tab2", tab_set.current_tab());
   ASSERT_TRUE(tab_set.goto_next_tab());
   ASSERT_EQ("Tab3", tab_set.current_tab());
   ASSERT_TRUE(tab_set.goto_next_tab());
   ASSERT_EQ("Tab1", tab_set.current_tab());
}

TEST (TabSetTest, can_goto_the_previous_tab)
{
   TabSet tab_set;
   tab_set.set_tabs({ "Tab1", "Tab2", "Tab3" });

   ASSERT_EQ("Tab1", tab_set.current_tab());
   ASSERT_TRUE(tab_set.goto_previous_tab());
   ASSERT_EQ("Tab3", tab_set.current_tab());
   ASSERT_TRUE(tab_set.goto_previous_tab());
   ASSERT_EQ("Tab2", tab_set.current_tab());
   ASSERT_TRUE(tab_set.goto_previous_tab());
   ASSERT_EQ("Tab1", tab_set.current_tab());
}

TEST (TabSetTest, when_setting_tabs_resets_current_tab_to_be_the_first)
{
   TabSet tab_set;
   tab_set.set_tabs({ "Tab1", "Tab2", "Tab3" });

   ASSERT_TRUE(tab_set.goto_next_tab());
   ASSERT_EQ("Tab2", tab_set.current_tab());
   ASSERT_TRUE(tab_set.goto_next_tab());
   ASSERT_EQ("Tab3", tab_set.current_tab());

   ASSERT_TRUE(tab_set.set_tabs({ "TabA", "TabB", "TabC" }));
   ASSERT_EQ("TabA", tab_set.current_tab());
}
