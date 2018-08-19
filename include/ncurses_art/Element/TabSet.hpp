#pragma once

#include <ncurses_art/Element/ElementBase.hpp>
#include <string>
#include <vector>

class TabSet : public ElementBase
{
private:
   float x, y;
   std::vector<std::string> tabs;
   float horizontal_padding;
   int active_tab;

public:
   TabSet(float x=0, float y=0, std::vector<std::string> tabs={});
   ~TabSet();

   bool set_x(float x);
   bool set_y(float y);
   bool set_tabs(std::vector<std::string> tabs={});

   float get_x();
   float get_y();
   std::vector<std::string> get_tabs();

   bool goto_next_tab();
   bool goto_previous_tab();
   std::string current_tab();

   void draw() override;
};
