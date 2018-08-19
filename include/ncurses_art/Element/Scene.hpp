#pragma once

#include <ncurses_art/Element/ElementBase.hpp>
#include <string>
#include <vector>

class AppController;

class Scene : public ElementBase
{
protected:
   AppController *app_controller;
   std::vector<ElementBase *> elements;

public:
   Scene();
   virtual ~Scene();

   void set_app_controller(AppController *app_controller);
   bool emit_event(std::string event);
   virtual bool process_input(char input_ch);
   virtual bool process_event(std::string event);

   std::vector<ElementBase *> &get_elements();

   void draw() override;
};
