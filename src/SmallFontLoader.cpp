

#include <SmallFontLoader.hpp>
#include <map>
#include <vector>
#include <string>




SmallFontLoader::SmallFontLoader()
{
}


SmallFontLoader::~SmallFontLoader()
{
}


std::string SmallFontLoader::sanitize_string(std::string unfiltered_phrase)
{
   // make the phrase uppercase
   std::string result;
   return result;
}

std::map<char, std::vector<std::string>> SmallFontLoader::load()
{
   std::string shade_chars_for_reference = " ░▒▓█▀▄▐▌";

   std::map<char, std::vector<std::string>> letters = {
     {
        'A',
        {
          { "▄▀▀▄" },
          { "█▄▄█" },
          { "▀  ▀" },
        }
     },
     {
        'B',
        {
          { "█▀▀▄" },
          { "█▀▀▄" },
          { "▀▀▀ " },
        }
     },
     {
        'C',
        {
          { "▄▀▀" },
          { "█  " },
          { " ▀▀" },
        }
     },
     {
        'D',
        {
          { "█▀▀▄" },
          { "█  █" },
          { "▀▀▀ " },
        }
     },
     {
        'E',
        {
          { "█▀▀" },
          { "█▀▀" },
          { "▀▀▀" },
        }
     },
     {
        'F',
        {
          { "█▀▀" },
          { "█▀▀" },
          { "▀  " },
        }
     },
     {
        'G',
        {
          { "▄▀▀▀" },
          { "█ ▀█" },
          { " ▀▀▀" },
        }
     },
     {
        'H',
        {
          { "█  █" },
          { "█▀▀█" },
          { "▀  ▀" },
        }
     },
     {
        'I',
        {
          { "▀█▀" },
          { " █ " },
          { "▀▀▀" },
        }
     },
     {
        'J',
        {
          { "   █" },
          { "▄  █" },
          { " ▀▀ " },
        }
     },
     {
        'K',
        {
          { "█ ▄▀" },
          { "█▀▄ " },
          { "▀  ▀" },
        }
     },
     {
        'L',
        {
          { "█  " },
          { "█  " },
          { "▀▀▀" },
        }
     },
     {
        'M',
        {
          { "█▄ ▄█" },
          { "█ ▀ █" },
          { "▀   ▀" },
        }
     },
     {
        'N',
        {
          { "█▄  █" },
          { "█ ▀▄█" },
          { "▀   ▀" },
        }
     },
     {
        'O',
        {
          { "▄▀▀▀▄" },
          { "█   █" },
          { " ▀▀▀ " },
        }
     },
     {
        'P',
        {
          { "█▀▀▄" },
          { "█▄▄▀" },
          { "▀   " },
        }
     },
     {
        'Q',
        {
          { "▄▀▀▀▄" },
          { "█  ▄▀" },
          { " ▀▀ ▀" },
        }
     },
     {
        'R',
        {
          { "█▀▀▄" },
          { "█▄▄▀" },
          { "▀  ▀" },
        }
     },
     {
        'S',
        {
          { "▄▀▀▀" },
          { " ▀▀▄" },
          { "▀▀▀ " },
        }
     },
     {
        'T',
        {
          { "▀█▀" },
          { " █ " },
          { " ▀ " },
        }
     },
   };

   //std::string shade_chars_for_reference = " ░▒▓█▀▄";

   return letters;
}


