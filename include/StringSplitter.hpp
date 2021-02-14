#pragma once


#include <string>
#include <vector>


class StringSplitter
{
private:
   std::string string;
   char delimiter;

public:
   StringSplitter(std::string string="", char delimiter=' ');
   ~StringSplitter();

   std::vector<std::string> split();
};



