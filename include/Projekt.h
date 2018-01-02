#include <ncurses_art/AppController.h>

#include <ncurses_art/Element/ElementBase.h>
#include <ncurses_art/Element/Frame.h>
#include <ncurses_art/Element/HeaderBar.h>
#include <ncurses_art/Element/Menu.h>
#include <ncurses_art/Element/Rectangle.h>
#include <ncurses_art/Element/Scene.h>
#include <ncurses_art/Element/TabSet.h>
#include <ncurses_art/Element/Text.h>
#include <ncurses_art/EventTypes.h>

class Projekt : public Scene
{
public:
   Projekt();
   ~Projekt();

   bool process_input(char input_ch) override;
   bool process_event(std::string event) override;
};

Projekt::~Projekt() {}

int main(int, char**)
{
   AppController app_controller;
   app_controller.initialize();
   Projekt projekt;
   projekt.set_app_controller(&app_controller);
   app_controller.set_scene(&projekt);
   app_controller.run_loop();
   return 0;
}
