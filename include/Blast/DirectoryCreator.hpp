#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class DirectoryCreator
   {
   private:
      std::vector<std::string> directory_components;
      bool path_is_absolute;

   public:
      DirectoryCreator(std::vector<std::string> directory_components={}, bool path_is_absolute=false);
      ~DirectoryCreator();

      bool create();
   };
}



