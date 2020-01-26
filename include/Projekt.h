#include <ncurses_art/AppController.hpp>

#include <ncurses_art/Element/ElementBase.hpp>
#include <ncurses_art/Element/Frame.hpp>
#include <ncurses_art/Element/HeaderBar.hpp>
#include <ncurses_art/Element/Menu.hpp>
#include <ncurses_art/Element/ProgressBar.hpp>
#include <ncurses_art/Element/Rectangle.hpp>
#include <ncurses_art/Element/Scene.hpp>
#include <ncurses_art/Element/Table.hpp>
#include <ncurses_art/Element/TabSet.hpp>
#include <ncurses_art/Element/Text.hpp>
#include <ncurses_art/Element/TextInput.hpp>
#include <ncurses_art/Element/WcharText.hpp>
#include <ncurses_art/EventTypes.hpp>

#include <allegro5/allegro.h>

#define TMP_OUTFILE "/tmp/out.txt.tmp"

std::vector<std::string> args;

class Projekt : public Scene
{
public:
   Projekt();
   ~Projekt();

   bool process_input(char input_ch) override;
   bool process_event(std::string event) override;
};

Projekt::~Projekt() {}

int main(int argc, char **argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   AppController app_controller;
   app_controller.initialize();
   Projekt projekt;
   projekt.set_app_controller(&app_controller);
   app_controller.set_scene(&projekt);
   app_controller.run_loop();
   return 0;
}
