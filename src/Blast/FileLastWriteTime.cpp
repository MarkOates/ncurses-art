

#include <Blast/FileLastWriteTime.hpp>
#include <filesystem>
#include <ctime>


namespace Blast
{


FileLastWriteTime::FileLastWriteTime(std::string filename)
   : filename(filename)
{
}


FileLastWriteTime::~FileLastWriteTime()
{
}


std::time_t FileLastWriteTime::last_write_time()
{
auto ftime = std::filesystem::last_write_time(filename);
auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
return std::chrono::system_clock::to_time_t(sctp);

//// below is the preferred implementation, but is not supported until -std=c++20 is used
//std::time_t last_write_time = decltype(ftime)::clock::to_time_t(ftime);
//return last_write_time;

}
} // namespace Blast


