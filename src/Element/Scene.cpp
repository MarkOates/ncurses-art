#include <ncurses_art/Element/Scene.h>
#include <ncurses_art/AppController.h>

#include <ncurses.h>

Scene::Scene()
   : ElementBase()
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

void Scene::draw()
{
   erase();
   for (auto &element : elements) element->draw();
}
