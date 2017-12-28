#include <ncurses_art/AppController.h>

#include <ncurses_art/Screen.h>
#include <ncurses_art/HeaderBar.h>
#include <ncurses_art/EventTypes.h>
#include <ncurses.h>
#include <stdexcept>
#include <unistd.h>

const int AppController::DEFAULT_USLEEP_DELAY = 10000;

AppController::AppController()
   : initialized(false)
   , screen()
   , event_queue()
   , usleep_delay(DEFAULT_USLEEP_DELAY)
   , program_aborted(false)
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
}

void AppController::run_loop()
{
   validate_init();

   nodelay(stdscr, true);

   do
   {
      switch (getch())
      {
      case 'j':
         event_queue.append_event(EVENT_MOVE_CURSOR_DOWN);
         break;
      case 'k':
         event_queue.append_event(EVENT_MOVE_CURSOR_UP);
         break;
      case 13:
         event_queue.append_event(EVENT_CHOOSE_CURRENT_MENU_ITEM);
         break;
      case 'q':
         event_queue.append_event(EVENT_ABORT_PROGRAM);
         break;
      }

      while (!event_queue.is_empty())
      {
         std::string event = event_queue.pop_event();

         if (event == EVENT_ABORT_PROGRAM) abort_program();
      }

      erase();

      HeaderBar header_bar;
      header_bar.draw();

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
