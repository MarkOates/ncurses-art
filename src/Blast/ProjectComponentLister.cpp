

#include <Blast/ProjectComponentLister.hpp>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iostream>
#include <ShellCommandExecutorWithCallback.hpp>
#include <ProjectComponentBasenameExtractor.hpp>
#include <StringSplitter.hpp>


namespace Blast
{


ProjectComponentLister::ProjectComponentLister(std::string project_root_directory)
   : project_root_directory(project_root_directory)
{
}


ProjectComponentLister::~ProjectComponentLister()
{
}


enum component_fragment_t
{
   COMPONENT_FRAGMENT_TYPE_UNDEFINED = 0,
   COMPONENT_FRAGMENT_TYPE_HEADER,
   COMPONENT_FRAGMENT_TYPE_SOURCE,
   COMPONENT_FRAGMENT_TYPE_EXAMPLE,
   COMPONENT_FRAGMENT_TYPE_TEST,
   COMPONENT_FRAGMENT_TYPE_QUINTESSENCE,
};


std::string get_component_fragment_folder_name(component_fragment_t component_fragment)
{
   switch (component_fragment)
   {
   case COMPONENT_FRAGMENT_TYPE_HEADER:
      return "include";
      break;
   case COMPONENT_FRAGMENT_TYPE_SOURCE:
      return "src";
      break;
   case COMPONENT_FRAGMENT_TYPE_EXAMPLE:
      return "examples";
      break;
   case COMPONENT_FRAGMENT_TYPE_TEST:
      return "tests";
      break;
   case COMPONENT_FRAGMENT_TYPE_QUINTESSENCE:
      return "quintessence";
      break;
   default:
      throw std::runtime_error("get_component_fragment_folder_name error: unaccounted for component_fragment_t");
      break;
   }
}


std::vector<std::string> get_components_of_fragment_type(std::string project_root_directory, component_fragment_t component_fragment)
{
   //component_fragment

   std::stringstream find_command;
   find_command << "cd " << project_root_directory << " && find quintessence -type f -name \"*.q.yml\"";
   ShellCommandExecutorWithCallback executor(find_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   std::string executor_response = executor.execute();
   StringSplitter splitter(executor_response, '\n');
   std::vector<std::string> quintessence_filenames = splitter.split();
}


std::vector<std::string> ProjectComponentLister::components()
{
   std::vector<std::string> result = {};

   //std::cerr << "WARNING: This function does NOT vaildate the passed project_root_directory "
      //<< "and injects it directly into a shell command.  This needs to be fixed."
      //<< std::endl;

   std::stringstream find_command;
   find_command << "cd " << project_root_directory << " && find quintessence -type f -name \"*.q.yml\"";
   //std::cout << "FIND_COMMAND: " << find_command.str() << std::endl;
   ShellCommandExecutorWithCallback executor(find_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   std::string executor_response = executor.execute();

   //std::cout << "EXECUTOR_RESPONSE: " << executor_response << std::endl;

   StringSplitter splitter(executor_response, '\n');
   std::vector<std::string> quintessence_filenames = splitter.split();

   for (auto &item : quintessence_filenames)
   {
      ProjectComponentBasenameExtractor extractor(item);
      result.push_back(extractor.identify_component_basename());
   }

   std::sort(result.begin(), result.end());

   return result;

}
} // namespace Blast


