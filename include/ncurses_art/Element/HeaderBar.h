#pragma once

#include <ncurses_art/Element/ElementBase.h>
#include <string>

class HeaderBar : public ElementBase
{
private:
   std::string text;

public:
   HeaderBar();
   ~HeaderBar();

   void draw() override;
};
