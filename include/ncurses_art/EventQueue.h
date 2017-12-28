#pragma once

#include <string>
#include <vector>

class EventQueue
{
private:
   std::vector<std::string> events;

public:
   EventQueue();
   ~EventQueue();

   bool append_event(std::string event);
   std::string pop_event();
   bool is_empty();
};
