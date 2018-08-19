#include <ncurses_art/AppController.hpp>

#include <ncurses_art/Element/Scene.hpp>
#include <ncurses_art/Element/Text.hpp>
#include <ncurses_art/EventTypes.hpp>
#include <ncurses_art/Screen.hpp>
#include <ncurses.h>
#include <stdexcept>
#include <sstream>
#include <unistd.h>

#include <string>
#include <fstream>
#include <streambuf>

const int AppController::DEFAULT_USLEEP_DELAY = 10000;

AppController::AppController()
   : initialized(false)
   , screen()
   , event_queue()
   , usleep_delay(DEFAULT_USLEEP_DELAY)
   , program_aborted(false)
   , scene(nullptr)
{
}

AppController::~AppController()
{
}

void AppController::initialize()
{
   if (initialized) return;

   screen.initialize();
   initialized = true;
   nodelay(stdscr, true);
   emit_event(EVENT_PROGRAM_INITIALIZED);
}

void AppController::set_scene(Scene *scene)
{
   this->scene = scene;
}

void AppController::emit_event(std::string event)
{
   event_queue.append_event(event);
}

void AppController::run_loop()
{
   validate_init();

   do
   {
      char ch = getch();
      switch (ch)
      {
      case '\e':
         emit_event(EVENT_ABORT_PROGRAM);
         break;
      case ERR:
         break;
      default:
         if (scene) scene->process_input(ch);
         break;
      }

      while (!event_queue.is_empty())
      {
         std::string event = event_queue.pop_event();

         if (event == EVENT_ABORT_PROGRAM) abort_program();
         else if (scene && scene->process_event(event)) break;
         else throw std::runtime_error(std::string("unrecognized event ") + event);
      }

      if (scene) scene->draw();
      else Text("- no scene is currently active -", COLS/2, LINES/3, 0.5).draw();

      usleep(usleep_delay);
   }
   while (!program_aborted);
}

void AppController::validate_init()
{
   if (!initialized) throw std::runtime_error("AppController must be initialized before using functionality");
}

void AppController::abort_program()
{
   validate_init();
   program_aborted = true;
}
