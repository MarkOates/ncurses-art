#pragma once

#include <ncurses_art/Element/ElementBase.hpp>

class Frame : public ElementBase
{
private:
   float x, y, w, h;
   int styles;

public:
   Frame(float x, float y, float w, float h);
   ~Frame();

   void set_styles(int styles);
   void draw() override;
};
