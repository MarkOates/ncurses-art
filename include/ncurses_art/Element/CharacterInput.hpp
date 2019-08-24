#pragma once

#include <string>

class CharacterInput
{
private:
   std::string buffer;

public:
   enum input_change_t
   {
      NO_CHANGE = 0,
      CHANGED,
      ENTER_KEY_PRESSED,
   };

   CharacterInput();
   ~CharacterInput();

   input_change_t process_input(char input_ch);

   std::string get_buffer();
};
