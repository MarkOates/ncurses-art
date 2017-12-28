#pragma once

#include <string>

class HeaderBar
{
private:
   std::string text;

public:
   HeaderBar();
   ~HeaderBar();

   void draw();
};
