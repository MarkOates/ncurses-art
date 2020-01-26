#include <ncurses_art/EventQueue.hpp>
#include <stdexcept>

EventQueue::EventQueue()
{
}

EventQueue::~EventQueue()
{
}

bool EventQueue::is_empty()
{
   return events.empty();
}

bool EventQueue::append_event(std::string event)
{
   events.push_back(event);
   return true;
}

std::string EventQueue::pop_event()
{
   if (events.empty()) throw std::runtime_error("Cannot pop_event on an empty queue");

   std::string event = events.front();
   events.erase(events.begin());

   return event;
}
