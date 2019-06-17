#include <gtest/gtest.h>

#include <ncurses_art/Element/Scene.hpp>

TEST(SceneTest, can_be_created)
{
   Scene scene;
}

TEST (SceneTest, has_the_expected_type)
{
   Scene scene;
   EXPECT_EQ("Scene", scene.get_type());
}
