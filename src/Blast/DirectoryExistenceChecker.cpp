

#include <Blast/DirectoryExistenceChecker.hpp>
#include <sys/stat.h>


namespace Blast
{


DirectoryExistenceChecker::DirectoryExistenceChecker(std::string directory_name)
   : directory_name(directory_name)
{
}


DirectoryExistenceChecker::~DirectoryExistenceChecker()
{
}


bool DirectoryExistenceChecker::exists()
{
   struct stat info;
   return stat(directory_name.c_str(), &info) == 0 && S_ISDIR(info.st_mode);
}
} // namespace Blast


