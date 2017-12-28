#include <ncurses_art/AppController.h>

#include <ncurses_art/Screen.h>
#include <ncurses_art/HeaderBar.h>
#include <ncurses.h>
#include <stdexcept>
#include <unistd.h>

const int AppController::DEFAULT_USLEEP_DELAY = 10000;

AppController::AppController()
   : initialized(false)
   , screen(nullptr)
   , usleep_delay(DEFAULT_USLEEP_DELAY)
   , program_aborted(false)
{
}

AppController::~AppController()
{
}

void AppController::initialize()
{
   screen = new Screen();
   initialized = true;
}

void AppController::run_loop()
{
   validate_init();

   char ch = '\0';
   nodelay(stdscr, true);

   do
   {
      switch (ch)
      {
      case 'q':
         abort_program();
         break;
      }

      erase();

      HeaderBar header_bar;
      header_bar.draw();

      usleep(usleep_delay);
      ch = getch();
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
