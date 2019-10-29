#pragma once

#include <ncurses_art/Element/ElementBase.hpp>

class ProgressBar : public ElementBase
{
private:
   float x, y, w, h;
   float value;
   int styles;

public:
   ProgressBar(float x, float y, float w, float h);
   ~ProgressBar();

   float get_value();
   void set_value(float value);

   void set_styles(int styles);
   void draw() override;
};
