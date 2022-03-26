

#include <Blast/Project/Component.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/FileLastWriteTime.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <iostream>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <vector>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/Project/SymlinkChecker.hpp>


namespace Blast
{
namespace Project
{


Component::Component(std::string name, std::string project_root)
   : name(name)
   , project_root(project_root)
{
}


Component::~Component()
{
}


std::string Component::get_name()
{
   return name;
}


std::string Component::get_project_root()
{
   return project_root;
}


std::string Component::generate_full_path_test_binary_filename()
{
   std::string filename = Blast::ProjectComponentFilenameGenerator(
         name,
         Blast::ProjectComponentFileTypes::TEST_BINARY
      ).generate_filename();

   return project_root + filename;
}

std::vector<std::string> Component::list_existing_component_files()
{
   std::vector<std::string> result;

   std::time_t most_recent_file_write_time = 0;
   std::vector<Blast::ProjectComponentFileTypes::project_file_type_t> types_to_scan_for = {
      Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE,
      Blast::ProjectComponentFileTypes::SOURCE_FILE,
      Blast::ProjectComponentFileTypes::HEADER_FILE,
      Blast::ProjectComponentFileTypes::TEST_FILE,
      Blast::ProjectComponentFileTypes::EXAMPLE_FILE,
      Blast::ProjectComponentFileTypes::DOCUMENTATION_FILE,
      //Blast::ProjectComponentFileTypes::OBJECT_FILE,
      //Blast::ProjectComponentFileTypes::TEST_BINARY,
      //Blast::ProjectComponentFileTypes::EXAMPLE_BINARY,
   };

   for (auto &type_to_scan_for : types_to_scan_for)
   {
      std::string filename = Blast::ProjectComponentFilenameGenerator(name, type_to_scan_for).generate_filename();
      std::string full_filename = project_root + filename;
      bool exists = Blast::FileExistenceChecker(full_filename).exists();

      if (exists) result.push_back(full_filename);
   }

   return result;
}

std::time_t Component::last_write_time()
{
   std::time_t most_recent_file_write_time = 0;

   std::vector<Blast::ProjectComponentFileTypes::project_file_type_t> types_to_scan_for = {
      Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE,
      Blast::ProjectComponentFileTypes::SOURCE_FILE,
      Blast::ProjectComponentFileTypes::HEADER_FILE,
      Blast::ProjectComponentFileTypes::TEST_FILE,
      Blast::ProjectComponentFileTypes::EXAMPLE_FILE,
      Blast::ProjectComponentFileTypes::DOCUMENTATION_FILE,
      //Blast::ProjectComponentFileTypes::OBJECT_FILE,
      //Blast::ProjectComponentFileTypes::TEST_BINARY,
      //Blast::ProjectComponentFileTypes::EXAMPLE_BINARY,
   };

   for (auto &type_to_scan_for : types_to_scan_for)
   {
      std::string filename = Blast::ProjectComponentFilenameGenerator(name, type_to_scan_for).generate_filename();
      std::string full_filename = project_root + filename;
      if (Blast::FileExistenceChecker(full_filename).exists())
      {
         std::time_t this_file_last_write_time = Blast::FileLastWriteTime(full_filename).last_write_time();
         if (this_file_last_write_time > most_recent_file_write_time)
         {
            most_recent_file_write_time = this_file_last_write_time;
         }
      }
   }

   return most_recent_file_write_time;
}

bool Component::check_file_existence(Blast::ProjectComponentFileTypes::project_file_type_t type)
{
   std::string filename = Blast::ProjectComponentFilenameGenerator(name, type).generate_filename();
   std::string full_filename = project_root + filename;

   std::cout << std::endl;
   std::cout << "## " << full_filename << std::endl;

   return Blast::FileExistenceChecker(full_filename).exists();
}

bool Component::exists()
{
   std::vector<Blast::ProjectComponentFileTypes::project_file_type_t> types_to_scan_for = {
      Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE,
      Blast::ProjectComponentFileTypes::SOURCE_FILE,
      Blast::ProjectComponentFileTypes::HEADER_FILE,
      Blast::ProjectComponentFileTypes::TEST_FILE,
      Blast::ProjectComponentFileTypes::EXAMPLE_FILE,
      Blast::ProjectComponentFileTypes::DOCUMENTATION_FILE,
      //Blast::ProjectComponentFileTypes::OBJECT_FILE,
      //Blast::ProjectComponentFileTypes::TEST_BINARY,
      //Blast::ProjectComponentFileTypes::EXAMPLE_BINARY,
   };

   for (auto &type_to_scan_for : types_to_scan_for)
   {
      if (check_file_existence(type_to_scan_for)) return true;
   }
   return false;
}

bool Component::has_quintessence()
{
   return check_file_existence(Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE);
}

bool Component::has_only_source_and_header()
{
   return (
     !has_quintessence()
     && check_file_existence(Blast::ProjectComponentFileTypes::SOURCE_FILE)
     && check_file_existence(Blast::ProjectComponentFileTypes::HEADER_FILE)
   );
}

bool Component::has_test()
{
   return check_file_existence(Blast::ProjectComponentFileTypes::TEST_FILE);
}

bool Component::has_documentation()
{
   return check_file_existence(Blast::ProjectComponentFileTypes::DOCUMENTATION_FILE);
}

std::vector<std::pair<std::string, std::string>> Component::read_symlinks()
{
   std::vector<std::string> existing_filenames = list_existing_component_files();
   std::vector<std::pair<std::string, std::string>> result = {};

   for (auto &filename : existing_filenames)
   {
      Blast::Project::SymlinkChecker symlink_checker(filename);
      bool is_symlink = symlink_checker.is_symlink();
      if (is_symlink)
      {
         std::string symlink_target = symlink_checker.read_symlink_target();
         result.push_back({ filename, symlink_target });
      }
   }

   return result;
}
} // namespace Project
} // namespace Blast


