

#include <Blast/Project/SymlinkChecker.hpp>
#include <sys/stat.h>
#include <unistd.h>
#include <string>


namespace Blast
{
namespace Project
{


SymlinkChecker::SymlinkChecker(std::string filename)
   : filename(filename)
{
}


SymlinkChecker::~SymlinkChecker()
{
}


bool SymlinkChecker::is_symlink()
{
struct stat p_statbuf;

if (lstat(filename.c_str(), &p_statbuf) < 0)
{
   throw std::runtime_error("[Project/SymlinkChecker error:] An error occurred while attempting to is_symlink");
}

return (S_ISLNK(p_statbuf.st_mode) == 1);

}

std::string SymlinkChecker::read_symlink_target()
{
char buff[512];
ssize_t len = ::readlink(filename.c_str(), buff, sizeof(buff)-1);
if (len != -1) {
   buff[len] = '\0';
   return std::string(buff);
}
throw std::runtime_error("an error occurred when trying to read_symlink_target in Blast/Project/SymlinkChecker");

}
} // namespace Project
} // namespace Blast


