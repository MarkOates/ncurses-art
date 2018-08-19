#pragma once

#include <ncurses_art/EventQueue.h>
#include <ncurses_art/Screen.h>

class Scene;

class AppController
{
private:
   static const int DEFAULT_USLEEP_DELAY;
   bool initialized;
   Screen screen;
   EventQueue event_queue;
   int usleep_delay;
   bool program_aborted;
   Scene *scene;

public:
   AppController();
   ~AppController();

   WINDOW *get_window();
   void initialize();
   void set_scene(Scene *scene);
   void emit_event(std::string event);
   void run_loop();
   void validate_init();
   void abort_program();
};
