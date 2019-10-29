#pragma once


#include <string>


class StringTrimmer
{
private:
   std::string text;

public:
   StringTrimmer(std::string text="");
   ~StringTrimmer();


std::string trim();
};



