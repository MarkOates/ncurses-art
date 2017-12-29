#pragma once

#include <ncurses_art/EventQueue.h>
#include <ncurses_art/Screen.h>

class ElementBase;

class AppController
{
private:
   static const int DEFAULT_USLEEP_DELAY;
   bool initialized;
   Screen screen;
   EventQueue event_queue;
   int usleep_delay;
   bool program_aborted;
   std::vector<ElementBase *> elements;

public:
   AppController();
   ~AppController();

   void initialize();
   void run_loop();
   void validate_init();
   void abort_program();
};
