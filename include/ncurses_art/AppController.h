#pragma once

#include <ncurses_art/EventQueue.h>
#include <ncurses_art/Screen.h>

class Element;

class AppController
{
private:
   static const int DEFAULT_USLEEP_DELAY;
   bool initialized;
   Screen screen;
   EventQueue event_queue;
   int usleep_delay;
   bool program_aborted;
   std::vector<Element *> elements;

public:
   AppController();
   ~AppController();

   void initialize();
   void run_loop();
   void validate_init();
   void abort_program();
};
