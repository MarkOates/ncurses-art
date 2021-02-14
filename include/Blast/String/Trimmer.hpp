#pragma once


#include <string>


namespace Blast
{
   namespace String
   {
      class Trimmer
      {
      private:
         std::string text;

      public:
         Trimmer(std::string text="");
         ~Trimmer();

         std::string trim();
         std::string ltrim(std::string s="");
         std::string rtrim(std::string s="");
      };
   }
}



