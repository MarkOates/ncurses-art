#pragma once

#include <string>

class Text
{
private:
   std::string text;
   float x, y;

public:
   Text(std::string text, float x, float y);
   ~Text();

   void draw();
};
