#pragma once

#include <string>

class ElementBase
{
protected:
   std::string type;
   std::string name;

public:
   ElementBase(std::string type);
   virtual ~ElementBase();

   bool set_name(std::string name);

   std::string get_type();
   std::string get_name();

   bool is_type(std::string type);
   bool is_name(std::string name);

   virtual void draw() = 0;
};
