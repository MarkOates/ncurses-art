#pragma once

#include <string>

class Text
{
private:
   std::string text;
   float x, y, align_x;

public:
   Text(std::string text, float x, float y, float align_x=0.0);
   ~Text();

   void draw();
};
