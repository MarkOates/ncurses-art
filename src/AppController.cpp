#include <ncurses_art/AppController.h>

#include <ncurses_art/Screen.h>
#include <ncurses.h>
#include <stdexcept>

AppController::AppController()
   : initialized(false)
   , screen(nullptr)
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

   printw("Hello world.");
   getch();
}

void AppController::validate_init()
{
   if (!initialized) throw std::runtime_error("AppController must be initialized before using functionality");
}
