#pragma once


#include <map>
#include <string>
#include <vector>


class ASCIICharacterRenderer
{
private:

public:
   ASCIICharacterRenderer();
   ~ASCIICharacterRenderer();

   int draw_character(std::map<char, std::vector<std::string>> letters={}, char c='a', int x=0, int y=0);
};



