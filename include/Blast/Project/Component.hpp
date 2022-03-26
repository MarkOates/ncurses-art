#pragma once


#include <Blast/ProjectComponentFileTypes.hpp>
#include <ctime>
#include <string>
#include <utility>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class Component
      {
      private:
         std::string name;
         std::string project_root;

      public:
         Component(std::string name="Unnamed/Component", std::string project_root="");
         ~Component();

         std::string get_name();
         std::string get_project_root();
         std::string generate_full_path_test_binary_filename();
         std::vector<std::string> list_existing_component_files();
         std::time_t last_write_time();
         bool check_file_existence(Blast::ProjectComponentFileTypes::project_file_type_t type=Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE);
         bool exists();
         bool has_quintessence();
         bool has_only_source_and_header();
         bool has_test();
         bool has_documentation();
         std::vector<std::pair<std::string, std::string>> read_symlinks();
      };
   }
}



