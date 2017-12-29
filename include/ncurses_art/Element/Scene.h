#pragma once

#include <ncurses_art/Element/ElementBase.h>
#include <vector>

class Scene : public ElementBase
{
private:
   std::vector<ElementBase *> elements;

public:
   Scene();
   ~Scene();

   void draw() override;
};
