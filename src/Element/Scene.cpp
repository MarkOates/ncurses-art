#include <ncurses_art/Element/Scene.h>
#include <ncurses_art/AppController.h>

#include <ncurses.h>

Scene::Scene()
   : ElementBase("Scene")
   , app_controller(nullptr)
   , elements()
{
}

Scene::~Scene()
{
}

void Scene::set_app_controller(AppController *app_controller)
{
   this->app_controller = app_controller;
}

bool Scene::emit_event(std::string event)
{
   if (app_controller) app_controller->emit_event(event);
   return true;
}

bool Scene::process_input(char input_ch)
{
   return true;
}

bool Scene::process_event(std::string event)
{
   return true;
}

std::vector<ElementBase *> &Scene::get_elements()
{
   return elements;
}

WINDOW *Scene::get_window()
{
   return app_controller->get_window();
}

void Scene::draw()
{
   erase();
   for (auto &element : elements) element->draw();
}
