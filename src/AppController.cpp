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

   char ch = ' ';
   nodelay(stdscr, true);

   do
   {
      erase();

      HeaderBar header_bar;
      header_bar.draw();

      usleep(usleep_delay);
   }
   while ((ch = getch()) != 'q');
}

void AppController::validate_init()
{
   if (!initialized) throw std::runtime_error("AppController must be initialized before using functionality");
}
