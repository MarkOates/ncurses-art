

#include <Blast/ProjectComponentLister.hpp>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iostream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <NcursesArt/ProjectComponentBasenameExtractor.hpp>
#include <Blast/StringSplitter.hpp>


namespace Blast
{


ProjectComponentLister::ProjectComponentLister(std::string project_root_directory)
   : project_root_directory(project_root_directory)
{
}


ProjectComponentLister::~ProjectComponentLister()
{
}


std::vector<std::string> ProjectComponentLister::components()
{
std::vector<std::string> result = {};

std::cerr << "WARNING: This function does NOT vaildate the passed project_root_directory "
          << "and injects it directly into a shell command.  This needs to be fixed."
          << std::endl;

std::stringstream find_command;
find_command << "cd " << project_root_directory << " && find quintessence -type f -name \"*.q.yml\"";
std::cout << "FIND_COMMAND: " << find_command.str() << std::endl;
Blast::ShellCommandExecutorWithCallback executor(find_command.str());
std::string executor_response = executor.execute();

std::cout << "EXECUTOR_RESPONSE: " << executor_response << std::endl;

Blast::StringSplitter splitter(executor_response, '\n');
std::vector<std::string> quintessence_filenames = splitter.split();

for (auto &item : quintessence_filenames)
{
  NcursesArt::ProjectComponentBasenameExtractor extractor(item);
  result.push_back(extractor.identify_component_basename());
}

return result;

}
} // namespace Blast


