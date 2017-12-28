#pragma once

class Screen;

class AppController
{
private:
   bool initialized;
   Screen *screen;

public:
   AppController();
   ~AppController();

   void initialize();
   void run_loop();
   void validate_init();
};
