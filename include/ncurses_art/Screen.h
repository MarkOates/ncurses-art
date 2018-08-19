#pragma once

#include <ncurses.h>

class Screen
{
private:
   bool initialized;
   WINDOW *window;

public:
   Screen();
   ~Screen();

   bool initialize();
};
