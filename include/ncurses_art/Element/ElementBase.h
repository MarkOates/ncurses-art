#pragma once

class ElementBase
{
public:
   ElementBase();
   virtual ~ElementBase();

   virtual void draw() = 0;
};
