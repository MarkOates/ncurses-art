#pragma once

#include <string>

class ElementBase
{
protected:
   std::string type;

public:
   ElementBase(std::string type);
   virtual ~ElementBase();

   std::string get_type();
   bool is_type(std::string type);
   virtual void draw() = 0;
};
