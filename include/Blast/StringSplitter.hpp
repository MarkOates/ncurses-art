#pragma once


#include <string>
#include <vector>


namespace Blast
{
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
}



