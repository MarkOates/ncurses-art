#pragma once

class Screen;

class AppController
{
private:
   static const int DEFAULT_USLEEP_DELAY;
   bool initialized;
   Screen *screen;
   int usleep_delay;

public:
   AppController();
   ~AppController();

   void initialize();
   void run_loop();
   void validate_init();
};
