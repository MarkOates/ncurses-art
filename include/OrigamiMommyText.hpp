#pragma once

#include <ncurses_art/Element/ElementBase.hpp>
#include <string>

class OrigamiMommyText : public ElementBase
{
private:
   std::string text;
   float x, y, align_x, align_y;
   int styles;

public:
   OrigamiMommyText(std::string text, float x, float y, float align_x=0.0, float align_y=0.0);
   ~OrigamiMommyText();

   bool set_text(std::string text);
   bool set_x(float x);
   bool set_y(float y);
   void set_styles(int styles);
   float get_x();
   float get_y();
   OrigamiMommyText &bold(bool on=true);
   OrigamiMommyText &blink(bool on=true);
   OrigamiMommyText &underline(bool on=true);
   OrigamiMommyText &reverse(bool on=true);
   OrigamiMommyText &color(int color_num);

   std::string get_text();

   void draw() override;
};
