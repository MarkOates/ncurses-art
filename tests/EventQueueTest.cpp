#include <gtest/gtest.h>

#include <ncurses_art/EventQueue.hpp>

TEST(EventQueueTest, can_be_created)
{
   EventQueue event_queue;
}

TEST(EventQueueTest, can_append_events_and_pop_events)
{
   EventQueue event_queue;

   ASSERT_EQ(true, event_queue.append_event("Event 1"));
   ASSERT_EQ(true, event_queue.append_event("Event 2"));
   ASSERT_EQ(true, event_queue.append_event("Event 3"));
   ASSERT_EQ("Event 1", event_queue.pop_event());
   ASSERT_EQ("Event 2", event_queue.pop_event());
   ASSERT_EQ(true, event_queue.append_event("Event 4"));
   ASSERT_EQ("Event 3", event_queue.pop_event());
   ASSERT_EQ("Event 4", event_queue.pop_event());
}

TEST(EventQueueTest, knows_when_the_queue_is_empty)
{
   EventQueue event_queue;

   ASSERT_EQ(true, event_queue.is_empty());

   event_queue.append_event("Event");
   ASSERT_EQ(false, event_queue.is_empty());

   event_queue.pop_event();
   ASSERT_EQ(true, event_queue.is_empty());
}

TEST(EventQueueTest, when_popping_on_an_empty_event_queue_raises_an_exception)
{
   EventQueue event_queue;
   ASSERT_THROW(event_queue.pop_event(), std::runtime_error);
}
