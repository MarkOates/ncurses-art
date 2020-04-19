#include <ncurses_art/Element/CharacterInput.hpp>

CharacterInput::CharacterInput()
   : buffer("")
{
}

CharacterInput::~CharacterInput()
{
}

CharacterInput::input_change_t CharacterInput::process_input(char input_ch)
{
   static const int ENTER_KEY = 10;
   static const int BACKSPACE_KEY = 127;

   if (input_ch == ENTER_KEY)
   {
      return input_change_t::ENTER_KEY_PRESSED; // return key submitted
   }
   if (input_ch == BACKSPACE_KEY)
   {
      if (!buffer.empty())
      {
         std::string buff = buffer;
         buff.erase(buff.size() - 1);
         buffer = buff;
         return input_change_t::CHANGED; // return buffer change
      }
   }
   else
   {
      buffer.append(1, input_ch);
      return input_change_t::CHANGED; // return buffer change
   }

   return input_change_t::NO_CHANGE; // return buffer change
}

std::string CharacterInput::get_buffer()
{
   return buffer;
}
