#pragma once

#include <ncurses_art/Element/ElementBase.hpp>
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
