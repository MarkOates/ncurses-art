#pragma once

#include <ncurses_art/Element/ElementBase.hpp>
#include <string>

class Text : public ElementBase
{
private:
   std::string text;
   float x, y, align_x, align_y;
   int styles;

public:
   Text(std::string text, float x, float y, float align_x=0.0, float align_y=0.0);
   ~Text();

   bool set_text(std::string text);
   bool set_x(float x);
   bool set_y(float y);
   bool set_align_x(float align_x);
   bool set_align_y(float align_y);
   void set_styles(int styles);
   float get_x();
   float get_y();
   float get_align_x();
   float get_align_y();
   Text &bold(bool on=true);
   Text &blink(bool on=true);
   Text &underline(bool on=true);
   Text &reverse(bool on=true);
   Text &color(int color_num);

   std::string get_text();

   void draw() override;
};
