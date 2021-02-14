#pragma once


#include <map>
#include <string>
#include <vector>


class SmallFontLoader
{
private:

public:
   SmallFontLoader();
   ~SmallFontLoader();

   std::string sanitize_string(std::string unfiltered_phrase="");
   std::map<char, std::vector<std::string>> load();
};



