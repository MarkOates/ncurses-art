#pragma once


#include <ctime>
#include <string>


namespace Blast
{
   class FileLastWriteTime
   {
   private:
      std::string filename;

   public:
      FileLastWriteTime(std::string filename="");
      ~FileLastWriteTime();


   std::time_t last_write_time();
   };
}



