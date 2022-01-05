

#include <Blast/Project/SourceReleaseBuilder.hpp>
#include <fstream>
#include <fstream>
#include <fstream>
#include <iostream>
#include <Blast/Project/SymlinkChecker.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/Project/ProjectSymlinkFixer.hpp>
#include <cstdio>
#include <sstream>
#include <cstdio>
#include <Blast/DirectoryCreator.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <sstream>


namespace Blast
{
namespace Project
{


SourceReleaseBuilder::SourceReleaseBuilder(std::string destination_directory, std::string project_name, std::string source_project_directory)
   : destination_directory(destination_directory)
   , project_name(project_name)
   , source_project_directory(source_project_directory)
{
}


SourceReleaseBuilder::~SourceReleaseBuilder()
{
}


std::string SourceReleaseBuilder::get_project_name()
{
   return project_name;
}


std::string SourceReleaseBuilder::get_source_project_directory()
{
   return source_project_directory;
}


void SourceReleaseBuilder::write_file_contents(std::string filename, std::string file_contents)
{
   std::ofstream out(filename);
   out << file_contents;
   out.close();
}

std::string SourceReleaseBuilder::get_makefile_content()
{
   std::stringstream MAKEFILE_CONTENT;
   std::string binary_name = "FadeToWhite"; // project_name
   MAKEFILE_CONTENT << "SRC_FILES := $(shell find src -type f)"
                    << std::endl
                    << "ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog "
                    << "-lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro "
                    << "-lallegro_main" << std::endl
                    << std::endl
                    << "main: $(SRC_FILES)" << std::endl
                    << "\t"
                    << "g++ -std=c++17 $^ programs/" << project_name << ".cpp -o " << binary_name
                    << " -I./include $(ALLEGRO_LIBS)"
                    ;
   return MAKEFILE_CONTENT.str();
}

std::string SourceReleaseBuilder::get_pinfo_content()
{
   std::string PINFO_CONTENT = R"HEREDOC(
   <?xml version="1.0" encoding="UTF-8"?>
   <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
   <plist version="1.0">
   <dict>
      <key>CFBundleDevelopmentRegion</key>
      <string>English</string>
      <key>CFBundleExecutable</key>
      <string>Hexagon</string>
      <key>CFBundleGetInfoString</key>
      <string>0.8, Copyright 2019 Mark Oates</string>
      <key>CFBundleIconFile</key>
      <string>Icon.icns</string>
      <key>CFBundleIdentifier</key>
      <string>org.markoates.Hexagon</string>
      <key>CFBundleInfoDictionaryVersion</key>
      <string>6.0</string>
      <key>CFBundleLongVersionString</key>
      <string>Hexagon</string>
      <key>CFBundleName</key>
      <string></string>
      <key>CFBundlePackageType</key>
      <string>APPL</string>
      <key>CFBundleShortVersionString</key>
      <string>0.8</string>
      <key>CFBundleSignature</key>
      <string>????</string>
      <key>CFBundleVersion</key>
      <string></string>
      <key>CSResourcesFileMapped</key>
      <true/>
      <key>LSRequiresCarbon</key>
      <true/>
      <key>NSHumanReadableCopyright</key>
      <string>Copyright 2019 Mark Oates</string>
   </dict>
   </plist>
   )HEREDOC";
   return PINFO_CONTENT;
}

void SourceReleaseBuilder::copy_file(std::string source_filename, std::string destination_filename)
{
   std::ifstream src(source_filename, std::ios::binary);
   std::ofstream dst(destination_filename,   std::ios::binary);
   dst << src.rdbuf();
}

std::vector<std::pair<std::string, std::string>> SourceReleaseBuilder::list_symlinks()
{
   std::string command = std::string("find ") + destination_directory;
   Blast::ShellCommandExecutorWithCallback executor(
      command,
      ShellCommandExecutorWithCallback::simple_silent_callback
   );
   std::string executor_result = executor.execute();
   StringSplitter splitter(executor_result, '\n');

   std::vector<std::string> filenames = splitter.split();
   std::vector<std::pair<std::string, std::string>> result;

   for (auto &filename : filenames)
   {
      Blast::Project::SymlinkChecker symlink_checker(filename);
      bool symlink_status = symlink_checker.is_symlink();

      if (symlink_status)
      {
         std::pair<std::string, std::string> this_symlink_info{ filename, symlink_checker.read_symlink_target() };
         result.push_back(this_symlink_info);
      }
   }

   std::sort(result.begin(), result.end());

   return result;
}

void SourceReleaseBuilder::fix_symlink_targets_from_relative_to_absolute()
{
   Blast::Project::ProjectSymlinkFixer symlink_fixer(destination_directory);
   symlink_fixer.run();
   return;
}

void SourceReleaseBuilder::replace_symlinks_with_copies_of_linked_files()
{
   std::cout << "Reading symlinks... " << std::endl;
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

   std::cout << "Finished reading symlinks (" << symlinks.size() << ")." << std::endl;
   return;
}

std::string SourceReleaseBuilder::get_source_release_folder_name()
{
   return get_project_name() + "SourceRelease";
}

std::string SourceReleaseBuilder::get_macos_release_folder_name()
{
   return get_project_name() + "MacOSRelease";
}

std::string SourceReleaseBuilder::get_win64_release_folder_name()
{
   return get_project_name() + "Win64Release";
}

void SourceReleaseBuilder::generate_macos_release()
{
   // create folder "Flower.app/"
   return;
}

void SourceReleaseBuilder::generate_source_release()
{
   std::string source_directory = get_source_project_directory();
   // !! WARNING: local variable name shadows class instance variable name:
   std::string xxx = destination_directory + "/" + get_source_release_folder_name();

   // create the directory
   std::vector<std::string> directories_that_will_exist = StringSplitter(xxx, '/').split();
   Blast::DirectoryCreator directory_creator(directories_that_will_exist, true);
   bool created = directory_creator.create();
   if (!created)
   {
      std::stringstream error_message;
      error_message << "Project/ReleaseBuilder error: could not create directory \""
                   << xxx
                   << "\"";
      throw std::runtime_error(error_message.str());
   }

   std::string destination_directory = xxx;


   std::stringstream copy_include_files_command;
   copy_include_files_command << "cp -R " << source_directory << "/include " << destination_directory << "/include";
   std::stringstream copy_src_files_command;
   copy_src_files_command << "cp -R " << source_directory << "/src " << destination_directory << "/src";
   std::stringstream copy_data_files_command;
   copy_data_files_command << "cp -R " << source_directory << "/bin/programs/data " << destination_directory << "/data";
   std::stringstream copy_program_files_command;
   copy_program_files_command << "cp -R " << source_directory << "/programs " << destination_directory << "/programs";
   std::stringstream copy_readme_file_command;
   copy_readme_file_command << "cp " << source_directory << "/README.md " << destination_directory << "/README.md";

   // copy files
   Blast::ShellCommandExecutorWithCallback include_file_copy_executor(copy_include_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   Blast::ShellCommandExecutorWithCallback src_file_copy_executor(copy_src_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   Blast::ShellCommandExecutorWithCallback data_file_copy_executor(copy_data_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   Blast::ShellCommandExecutorWithCallback program_file_copy_executor(copy_program_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   Blast::ShellCommandExecutorWithCallback readme_file_copy_executor(copy_readme_file_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);

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

   std::cout << "Copying README.md file into \"" << destination_directory << "\"... ";
   readme_file_copy_executor.execute();
   std::cout << "done." << std::endl;

   std::cout << "Creating rudimentary Makefile...";
   std::string makefile_full_filename = destination_directory + "/Makefile";
   write_file_contents(makefile_full_filename, get_makefile_content());
   std::cout << "done." << std::endl;

   std::cout << "Fixing symlinks from relative to absolute...";
   fix_symlink_targets_from_relative_to_absolute();
   std::cout << "done." << std::endl;

   replace_symlinks_with_copies_of_linked_files();

   return;
}
} // namespace Project
} // namespace Blast


