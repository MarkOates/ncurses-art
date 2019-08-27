#include <ncurses_art/AppController.h>

int main(int, char**)
{
   AppController app_controller;
   app_controller.initialize();
   app_controller.run_loop();
   return 0;
}
