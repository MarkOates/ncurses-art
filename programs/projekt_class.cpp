#include "projekt3.hpp"



#include <iostream>



class MyProjekt;



class MyProject : public Projekt3
{
public:
   MyProject() : Projekt3() {}
   ~MyProject() {}

   void initialize() override
   {
      mappings = {
         { 'q', EVENT_ABORT_PROGRAM },
      };
      events = {
         { EVENT_PROGRAM_INITIALIZED, MyProject::my_custom_init_func },
      };
   }

   static void my_custom_init_func()
   {
      //init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
      //init_pair(3, COLOR_BLACK, 21);

      //create_text("text", 10, 20);
      //create_frame("frame", 20, 30, 80, 7).set_styles(COLOR_PAIR(3));

      //mappings['s'] = SET_TEXT;

      //events[SET_TEXT] = []{
         //find_text("text").set_text("Hello world!");
      //};
   }
};



int main(int argc, char **argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   AppController app_controller;
   app_controller.initialize();
   MyProject projekt;
   projekt.initialize();
   projekt.set_app_controller(&app_controller);
   app_controller.set_scene(&projekt);
   app_controller.run_loop();
   return 0;
}



