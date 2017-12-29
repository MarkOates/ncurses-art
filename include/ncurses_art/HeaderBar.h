#pragma once

#include <ncurses_art/Element.h>
#include <string>

class HeaderBar : public Element
{
private:
   std::string text;

public:
   HeaderBar();
   ~HeaderBar();

   void draw() override;
};
