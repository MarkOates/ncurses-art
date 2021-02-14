

#include <ASCIICharacterRenderer.hpp>
#include <ncurses.h>
#include <map>
#include <vector>
#include <string>




ASCIICharacterRenderer::ASCIICharacterRenderer()
{
}


ASCIICharacterRenderer::~ASCIICharacterRenderer()
{
}


int ASCIICharacterRenderer::draw_character(std::map<char, std::vector<std::string>> letters, char c, int x, int y)
{
   std::vector<std::string> letter = {};

   if (letters.find(c) == letters.end())
   {
      letter = {
         { "????" },
         { "?  ?" },
         { "?  ?" },
         { "????" },
      };
   }
   else
   {
      letter = letters[c];
   }

   int yy=0;
   int letter_width = 0;
   for (std::string &letter_line : letter)
   {
      if (letter_line.length() > letter_width) letter_width = letter_line.length();
      mvaddnstr(y + yy, x, letter_line.c_str(), -1);
      yy++;
   }

   return letter_width/3;               // I have *no* idea why, but the letters have a width 3x as long.
}


