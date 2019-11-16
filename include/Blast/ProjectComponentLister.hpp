#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class ProjectComponentLister
   {
   private:
      std::string project_root_directory;

   public:
      ProjectComponentLister(std::string project_root_directory="");
      ~ProjectComponentLister();


   std::vector<std::string> components();
   };
}



