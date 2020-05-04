

#include <Blast/Project/SymlinkChecker.hpp>
#include <sstream>
#include <filesystem>
#include <filesystem>
#include <filesystem>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <filesystem>
#include <filesystem>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


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
std::filesystem::path path(filename);
if (!std::filesystem::exists(path))
{
   std::stringstream error_message;
   error_message << "an error occurred when trying to read_symlink_target in "
                 << "Blast/Project/SymlinkChecker: "
                 << "The file \"" << filename << "\" does not exist.";
   throw std::runtime_error(error_message.str());
}

return is_symlink__shell_call_impl();

// This is the expected implementation below, but std::filesystem::is_symlink is returning false
// on Windows so these lines are disabled and the shell call is used in its place

//std::filesystem::file_status file_status = std::filesystem::symlink_status(path);
//return std::filesystem::is_symlink(file_status);

}

bool SymlinkChecker::is_symlink__shell_call_impl()
{
std::stringstream command;
command << "ls -l " << filename;
Blast::ShellCommandExecutorWithCallback executor(
   command.str(),
   Blast::ShellCommandExecutorWithCallback::simple_silent_callback);
std::string command_result = executor.execute();
if (!command_result.empty() && command_result[0] == 'l') return true;
return false;

}

std::string SymlinkChecker::read_symlink_target()
{
return read_symlink_target__shell_call_impl();

// This is the expected implementation below, but std::filesystem::read_symlink is
// throwing an error on Windows so has been disabled and the shell call is used in its place

//if (!is_symlink())
//{
//   std::string error_message = "an error occurred when trying to read_symlink_target in Blast/Project/SymlinkChecker";
//   throw std::runtime_error(error_message);
//}
//std::filesystem::path path(filename);
//return std::filesystem::read_symlink(path).string();

}

std::string SymlinkChecker::read_symlink_target__shell_call_impl()
{
std::stringstream command;
command << "readlink " << filename;
Blast::ShellCommandExecutorWithCallback executor(
   command.str(),
   Blast::ShellCommandExecutorWithCallback::simple_silent_callback);
std::string command_result = executor.execute();
if (!command_result.empty() && command_result.back() == '\n') command_result.pop_back();
return command_result;

}
} // namespace Project
} // namespace Blast


