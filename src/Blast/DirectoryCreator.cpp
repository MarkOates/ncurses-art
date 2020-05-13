

#include <Blast/DirectoryCreator.hpp>
#include <sys/stat.h>
#include <sstream>
#include <string>
#include <Blast/DirectoryExistenceChecker.hpp>


namespace Blast
{


DirectoryCreator::DirectoryCreator(std::vector<std::string> directory_components, bool path_is_absolute)
   : directory_components(directory_components)
   , path_is_absolute(path_is_absolute)
{
}


DirectoryCreator::~DirectoryCreator()
{
}


bool DirectoryCreator::create()
{
for (auto &directory_component : directory_components)
{
   // TODO: improve this to raise an exception
   if (directory_component.find('/') != std::string::npos) return false;
}

std::stringstream result_directories;
const std::string SEPARATOR = "/";
if (path_is_absolute) result_directories << "/";
for (auto &directory_component : directory_components)
{
  result_directories << directory_component << SEPARATOR;
  std::string directory_to_create = result_directories.str();
  if (Blast::DirectoryExistenceChecker(directory_to_create).exists()) continue;
  #ifdef _WIN32
    int mkdir_result = mkdir(directory_to_create.c_str());
  #else
    int mkdir_result = mkdir(directory_to_create.c_str(), 0777);
  #endif
  if (mkdir_result == -1) return false;
}
return true;

}
} // namespace Blast


