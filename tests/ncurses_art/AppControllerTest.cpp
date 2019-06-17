#include <gtest/gtest.h>

#include <ncurses_art/AppController.hpp>

TEST(AppControllerTest, can_be_created)
{
   AppController app_controller;
}

TEST(AppControllerTest, when_running_the_loop_before_initialization_raises_an_exception)
{
   AppController app_controller;
   ASSERT_THROW(app_controller.run_loop(), std::runtime_error);
}
