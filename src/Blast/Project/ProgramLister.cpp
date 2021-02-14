

#include <Blast/Project/ProgramLister.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <algorithm>


namespace Blast
{
namespace Project
{


ProgramLister::ProgramLister(std::string project_root)
   : project_root(project_root)
{
}


ProgramLister::~ProgramLister()
{
}


std::string ProgramLister::get_project_root()
{
   return project_root;
}


std::string ProgramLister::build_program_lister_shell_command()
{
   std::stringstream find_command;
   std::string fragment_folder_name = "programs";
   std::string fragment_extension = ".exe";
   find_command << "cd " << project_root
                << " && find " << fragment_folder_name
                << " -type f -name \"*\"";
   return find_command.str();
}

std::vector<std::string> ProgramLister::program_filenames()
{
   Blast::ShellCommandExecutorWithCallback executor(
      build_program_lister_shell_command(),
      Blast::ShellCommandExecutorWithCallback::simple_silent_callback);

   std::string executor_response = executor.execute();
   StringSplitter splitter(executor_response, '\n');

   std::vector<std::string> result = splitter.split();

   std::sort(result.begin(), result.end());

   return result;
}
} // namespace Project
} // namespace Blast


