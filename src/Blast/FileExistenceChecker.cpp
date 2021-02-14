

#include <Blast/FileExistenceChecker.hpp>
#include <filesystem>


namespace Blast
{


FileExistenceChecker::FileExistenceChecker(std::string filename)
   : filename(filename)
{
}


FileExistenceChecker::~FileExistenceChecker()
{
}


std::string FileExistenceChecker::get_filename()
{
   return filename;
}


bool FileExistenceChecker::exists()
{
   return std::filesystem::exists(filename);
}
} // namespace Blast


