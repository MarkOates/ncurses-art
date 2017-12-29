#pragma once

#include <ncurses_art/Element/ElementBase.h>
#include <string>

class Text : public ElementBase
{
private:
   std::string text;
   float x, y, align_x;
   int styles;

public:
   Text(std::string text, float x, float y, float align_x=0.0);
   ~Text();

   void set_styles(int styles);
   Text &bold(bool on=true);
   Text &blink(bool on=true);
   Text &underline(bool on=true);
   Text &reverse(bool on=true);
   Text &color(int color_num);
   void draw() override;
};
