#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class SymlinkChecker
      {
      private:
         std::string filename;

      public:
         SymlinkChecker(std::string filename="");
         ~SymlinkChecker();


      bool is_symlink();
      bool is_symlink__shell_call_impl();
      std::string read_symlink_target();
      std::string read_symlink_target__shell_call_impl();
      };
   }
}



