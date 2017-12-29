#include <ncurses_art/Element/Scene.h>

#include <ncurses.h>

Scene::Scene()
   : ElementBase()
   , elements()
{
}

Scene::~Scene()
{
}

void Scene::draw()
{
   erase();
   for (auto &element : elements) element->draw();
}
