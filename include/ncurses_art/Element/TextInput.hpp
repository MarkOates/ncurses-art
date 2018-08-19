#pragma once

#include <ncurses_art/Element/ElementBase.hpp>

class TextInput : public ElementBase
{
private:
   float x;
   float y;
   std::string label;
   std::string value;
   float width;

public:
   TextInput(float x=0, float y=0, std::string label="", float width=60);
   ~TextInput();

   bool set_x(float x);
   bool set_y(float y);
   bool set_label(std::string label);
   bool set_value(std::string value);
   bool set_width(float width);

   float get_x();
   float get_y();
   std::string get_label();
   std::string get_value();
   float get_width();

   virtual void draw() override;
};

