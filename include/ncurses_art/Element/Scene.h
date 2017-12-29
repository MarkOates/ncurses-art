#pragma once

#include <ncurses_art/Element/ElementBase.h>
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
   void draw() override;
};
