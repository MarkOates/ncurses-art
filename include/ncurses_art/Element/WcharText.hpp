#pragma once

#include <ncurses_art/Element/ElementBase.hpp>
#include <string>
#include <ncurses.h>

class WcharText : public ElementBase
{
private:
   std::wstring text;
   float x, y, align_x;
   int styles;

public:
   WcharText(std::wstring text, float x, float y, float align_x=0.0);
   ~WcharText();

   bool set_text(std::wstring text);
   bool set_x(float x);
   bool set_y(float y);
   void set_styles(int styles);
   float get_x();
   float get_y();
   WcharText &bold(bool on=true);
   WcharText &blink(bool on=true);
   WcharText &underline(bool on=true);
   WcharText &reverse(bool on=true);
   WcharText &color(int color_num);

   std::wstring get_text();

   void draw() override;
};
