#pragma once

#include <ncurses_art/Element.h>

class Rectangle : public Element
{
private:
   float x, y, w, h;
   int styles;

public:
   Rectangle(float x, float y, float w, float h);
   ~Rectangle();

   void set_styles(int styles);
   void draw() override;
};
