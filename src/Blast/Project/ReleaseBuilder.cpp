

#include <Blast/Project/ReleaseBuilder.hpp>
#include <fstream>
#include <fstream>
#include <fstream>
#include <iostream>
#include <Blast/Project/SymlinkChecker.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <cstdio>
#include <sstream>
#include <cstdio>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <sstream>


namespace Blast
{
namespace Project
{


ReleaseBuilder::ReleaseBuilder(std::string destination_directory)
   : destination_directory(destination_directory)
{
}


ReleaseBuilder::~ReleaseBuilder()
{
}


void ReleaseBuilder::write_file_contents(std::string filename, std::string file_contents)
{
std::ofstream out(filename);
out << file_contents;
out.close();

}

std::string ReleaseBuilder::get_makefile_content()
{
std::string MAKEFILE_CONTENT = R"HEREDOC(SRC_FILES := $(shell find src -type f)
ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro -lallegro_main
main: $(SRC_FILES)
)HEREDOC";
MAKEFILE_CONTENT += "\t";
MAKEFILE_CONTENT += "g++ -std=c++17 $^ programs/Flowers.cpp -o Flowers -I./include $(ALLEGRO_LIBS)";
return MAKEFILE_CONTENT;

}

void ReleaseBuilder::copy_file(std::string source_filename, std::string destination_filename)
{
std::ifstream src(source_filename, std::ios::binary);
std::ofstream dst(destination_filename,   std::ios::binary);
dst << src.rdbuf();

}

std::vector<std::pair<std::string, std::string>> ReleaseBuilder::list_symlinks()
{
std::string command = std::string("find ") + destination_directory;
Blast::ShellCommandExecutorWithCallback executor(command, ShellCommandExecutorWithCallback::simple_silent_callback);
std::string executor_result = executor.execute();
StringSplitter splitter(executor_result, '\n');

std::vector<std::string> filenames = splitter.split();
std::vector<std::pair<std::string, std::string>> result;

for (auto &filename : filenames)
{
   Blast::Project::SymlinkChecker symlink_checker(filename);
   if (symlink_checker.is_symlink())
   {
      std::pair<std::string, std::string> this_symlink_info{ filename, symlink_checker.read_symlink_target() };
      result.push_back(this_symlink_info);
   }
}

return result;

}

void ReleaseBuilder::replace_symlinks_with_copies_of_linked_files()
{
std::vector<std::pair<std::string, std::string>> symlinks = list_symlinks();

for (auto &symlink : symlinks)
{
   std::string file_to_remove = symlink.first;
   std::string file_to_copy_source = symlink.second;
   std::string file_to_copy_destination = symlink.first;

   if (remove(file_to_remove.c_str()) != 0)
   {
      std::stringstream error_message;
      error_message << "There was an error trying to delete the file \"" << file_to_remove << "\"" << std::endl;
      throw std::runtime_error(error_message.str());
   }

   copy_file(file_to_copy_source, file_to_copy_destination);
}
return;

}

void ReleaseBuilder::generate_source_release()
{
std::string source_directory = "/Users/markoates/Repos/Flowers";

std::stringstream copy_include_files_command;
copy_include_files_command << "cp -R " << source_directory << "/include " << destination_directory << "/include";
std::stringstream copy_src_files_command;
copy_src_files_command << "cp -R " << source_directory << "/src " << destination_directory << "/src";
std::stringstream copy_data_files_command;
copy_data_files_command << "cp -R " << source_directory << "/bin/programs/data " << destination_directory << "/data";
std::stringstream copy_program_files_command;
copy_program_files_command << "cp -R " << source_directory << "/programs " << destination_directory << "/programs";

// copy files
Blast::ShellCommandExecutorWithCallback include_file_copy_executor(copy_include_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
Blast::ShellCommandExecutorWithCallback src_file_copy_executor(copy_src_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
Blast::ShellCommandExecutorWithCallback data_file_copy_executor(copy_data_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
Blast::ShellCommandExecutorWithCallback program_file_copy_executor(copy_program_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);

std::cout << "Copying include files into \"" << destination_directory << "\"... ";
include_file_copy_executor.execute();
std::cout << "done." << std::endl;

std::cout << "Copying src files into \"" << destination_directory << "\"... ";
src_file_copy_executor.execute();
std::cout << "done." << std::endl;

std::cout << "Copying program files into \"" << destination_directory << "\"... ";
program_file_copy_executor.execute();
std::cout << "done." << std::endl;

std::cout << "Copying data files into \"" << destination_directory << "\"... ";
data_file_copy_executor.execute();
std::cout << "done." << std::endl;

std::cout << "Creating rudimentary Makefile...";
std::string makefile_full_filename = destination_directory + "/Makefile";
write_file_contents(makefile_full_filename, get_makefile_content());
std::cout << "done." << std::endl;

replace_symlinks_with_copies_of_linked_files();

return;

}
} // namespace Project
} // namespace Blast


