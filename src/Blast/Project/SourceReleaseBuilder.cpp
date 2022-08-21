

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
#include <Blast/TimeStamper.hpp>


namespace Blast
{
namespace Project
{


SourceReleaseBuilder::SourceReleaseBuilder(std::string destination_directory, std::string project_name, std::string source_project_directory, std::string main_program_filename, bool link_with_opengl, bool copy_allegro_flare_source, bool copy_nlohmann_json_from_allegro_flare_source, bool remove_AllegroFlare_Network_from_allegro_flare_copy, bool remove_AllegroFlare_Testing_from_allegro_flare_copy)
   : destination_directory(destination_directory)
   , project_name(project_name)
   , source_project_directory(source_project_directory)
   , main_program_filename(main_program_filename)
   , link_with_opengl(link_with_opengl)
   , copy_allegro_flare_source(copy_allegro_flare_source)
   , copy_nlohmann_json_from_allegro_flare_source(copy_nlohmann_json_from_allegro_flare_source)
   , remove_AllegroFlare_Network_from_allegro_flare_copy(remove_AllegroFlare_Network_from_allegro_flare_copy)
   , remove_AllegroFlare_Testing_from_allegro_flare_copy(remove_AllegroFlare_Testing_from_allegro_flare_copy)
{
}


SourceReleaseBuilder::~SourceReleaseBuilder()
{
}


void SourceReleaseBuilder::set_link_with_opengl(bool link_with_opengl)
{
   this->link_with_opengl = link_with_opengl;
}


void SourceReleaseBuilder::set_copy_allegro_flare_source(bool copy_allegro_flare_source)
{
   this->copy_allegro_flare_source = copy_allegro_flare_source;
}


void SourceReleaseBuilder::set_copy_nlohmann_json_from_allegro_flare_source(bool copy_nlohmann_json_from_allegro_flare_source)
{
   this->copy_nlohmann_json_from_allegro_flare_source = copy_nlohmann_json_from_allegro_flare_source;
}


void SourceReleaseBuilder::set_remove_AllegroFlare_Network_from_allegro_flare_copy(bool remove_AllegroFlare_Network_from_allegro_flare_copy)
{
   this->remove_AllegroFlare_Network_from_allegro_flare_copy = remove_AllegroFlare_Network_from_allegro_flare_copy;
}


void SourceReleaseBuilder::set_remove_AllegroFlare_Testing_from_allegro_flare_copy(bool remove_AllegroFlare_Testing_from_allegro_flare_copy)
{
   this->remove_AllegroFlare_Testing_from_allegro_flare_copy = remove_AllegroFlare_Testing_from_allegro_flare_copy;
}


std::string SourceReleaseBuilder::get_project_name()
{
   return project_name;
}


std::string SourceReleaseBuilder::get_source_project_directory()
{
   return source_project_directory;
}


std::string SourceReleaseBuilder::get_main_program_filename()
{
   return main_program_filename;
}


bool SourceReleaseBuilder::get_link_with_opengl()
{
   return link_with_opengl;
}


bool SourceReleaseBuilder::get_copy_allegro_flare_source()
{
   return copy_allegro_flare_source;
}


bool SourceReleaseBuilder::get_copy_nlohmann_json_from_allegro_flare_source()
{
   return copy_nlohmann_json_from_allegro_flare_source;
}


bool SourceReleaseBuilder::get_remove_AllegroFlare_Network_from_allegro_flare_copy()
{
   return remove_AllegroFlare_Network_from_allegro_flare_copy;
}


bool SourceReleaseBuilder::get_remove_AllegroFlare_Testing_from_allegro_flare_copy()
{
   return remove_AllegroFlare_Testing_from_allegro_flare_copy;
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
   //std::string main_program_name = "main";
   // TODO throw error if project name contains invalid characters (spaces, etc)
   // TODO throw error if main program filename does not exist, or contains invalid characters (spaces, etc)
   std::string binary_name = project_name; //"FadeToWhite"; // project_name

   bool include_opengl = get_link_with_opengl();

   MAKEFILE_CONTENT
                    //<< "SRC_FILES := $(shell find src -type f)"
                    << "SRC_FILES := $(shell find src -type f -not -path '*/.*')"
                    << std::endl
                    << "ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog "
                    << "-lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro "
                    << "-lallegro_main" << std::endl
                    << std::endl;

   if (include_opengl)
   {
                 MAKEFILE_CONTENT
                    << "ifeq ($(OS), Windows_NT)" << std::endl
                    << "\tOPENGL_LIB=-lopengl32" << std::endl
                    << "else" << std::endl
                    << "\tUNAME_S := $(shell uname -s)" << std::endl
                    << "\tifeq ($(UNAME_S),Linux)" << std::endl
                    << "\t\tOPENGL_LIB=-lGL" << std::endl
                    << "\tendif" << std::endl
                    << "\tifeq ($(UNAME_S),Darwin)" << std::endl
                    << "\t\tOPENGL_LIB=-framework OpenGL" << std::endl
                    << "\tendif" << std::endl
                    << "endif" << std::endl
                    << std::endl;
   }

   MAKEFILE_CONTENT
                    << "main: $(SRC_FILES)" << std::endl
                    << "\t"
                    << "g++ -std=c++17 $^ " << main_program_filename << " -o " << binary_name
                    << " -I./include $(ALLEGRO_LIBS)";
                    if (include_opengl) MAKEFILE_CONTENT << " $(OPENGL_LIB)";

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
      <string>0.8, Copyright 2022 Mark Oates</string>
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
      <string>Copyright 2022 Mark Oates</string>
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
   return get_project_name() + "-SourceRelease";
}

std::string SourceReleaseBuilder::get_macos_release_folder_name()
{
   return get_project_name() + "-MacOSRelease";
}

std::string SourceReleaseBuilder::get_win64_release_folder_name()
{
   return get_project_name() + "-Win64Release";
}

void SourceReleaseBuilder::generate_macos_release()
{
   // create folder "Flower.app/"
   return;
}

void SourceReleaseBuilder::recursively_remove_folder_with_prompt(std::string folder_to_remove)
{
   std::stringstream folder_removal_command;
   folder_removal_command << "rm -rdf \"" << folder_to_remove << "\"";

   std::cout << "Blast/Project/SourceReleaseBuilder will now attempt to delete the following folder:" << std::endl;
   std::cout << "   \"" << folder_to_remove << "\"" << std::endl;
   std::cout << "Using the command:" << std::endl;
   std::cout << "   " << folder_removal_command.str() << "" << std::endl;
   std::cout << "Do you wish to continue? (y/n) > ";
   char input = 'n';
   std::cin >> input;
   if (input == 'y')
   {
      //std::stringstream folder_removal_command;
      //folder_removal_command << "rm -rdf " << folder_to_remove;
      Blast::ShellCommandExecutorWithCallback folder_removal_command_executor(
            folder_removal_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );

      std::cout << "Removing folder...";
      folder_removal_command_executor.execute();
      std::cout << "done." << std::endl;
   }
   return;
}

void SourceReleaseBuilder::generate_source_release()
{
   // options:
   bool copy_allegro_flare_source_and_header_files_from_source = true;
   bool copy_allegro_flare_include_lib_nlohmann_json_from_source = true;
   Blast::TimeStamper time_stamper;

   std::string source_directory = get_source_project_directory();

   // !! WARNING: local variable name shadows class instance variable name:
   std::string xxx = destination_directory
                   + "/"
                   + get_source_release_folder_name()
                   + "-" + time_stamper.generate_now_timestamp_utc();

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


   bool manually_copy_allegro_flare_headers_and_source_files = this->get_copy_allegro_flare_source();
   if (manually_copy_allegro_flare_headers_and_source_files)
   {
      /// Build commands

      // headers
      std::string allegro_flare_include_directory = "/Users/markoates/Repos/allegro_flare/include/AllegroFlare";
      std::string allegro_flare_include_destination_directory = destination_directory + "/include/AllegroFlare";
      std::stringstream copy_allegro_flare_include_files_command;
      copy_allegro_flare_include_files_command << "cp -R " << allegro_flare_include_directory << " " << allegro_flare_include_destination_directory;

      // src
      std::string allegro_flare_src_directory = "/Users/markoates/Repos/allegro_flare/src/AllegroFlare";
      std::string allegro_flare_src_destination_directory = destination_directory + "/src/AllegroFlare";
      std::stringstream copy_allegro_flare_src_files_command;
      copy_allegro_flare_src_files_command << "cp -R " << allegro_flare_src_directory << " " << allegro_flare_src_destination_directory;


      // Create command executors

      Blast::ShellCommandExecutorWithCallback allegro_flare_include_files_copy_executor(
            copy_allegro_flare_include_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );
      Blast::ShellCommandExecutorWithCallback allegro_flare_src_files_copy_executor(
            copy_allegro_flare_src_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );


      // Execute command executors

      std::cout << "Copying AllegroFlare include files into \"" << destination_directory << "\"... ";
      allegro_flare_include_files_copy_executor.execute();
      std::cout << "done." << std::endl;

      std::cout << "Copying AllegroFlare src files into \"" << destination_directory << "\"... ";
      allegro_flare_src_files_copy_executor.execute();
      std::cout << "done." << std::endl;
   }


   bool manually_copy_allegro_flare_include_lib_nlohmann_json_from_source =
     this->get_copy_nlohmann_json_from_allegro_flare_source();
   if (manually_copy_allegro_flare_include_lib_nlohmann_json_from_source)
   {
      // build the command
      std::stringstream copy_nlohmann_json_file_command;
      std::string nlohmann_json_file_source = "/Users/markoates/Repos/allegro_flare/include/lib/nlohmann/json.hpp";
      std::string nlohmann_json_file_destination_directory = destination_directory + "/include/lib/nlohmann";
      std::string nlohmann_json_file_destination = nlohmann_json_file_destination_directory + "/json.hpp";
      // TODO: check for file existence
      copy_nlohmann_json_file_command << "cp -R " << nlohmann_json_file_source << " " << nlohmann_json_file_destination;

      // start the copy process
      std::cout << "Copying lib/nlohmann/json.hpp file from AllegroFlare into \"" << destination_directory << "\"... "
                << std::endl;

      // create the directory if it doesn't exist
      std::cout << "  Ensuring directory exists...";
      std::vector<std::string> directories_needed_for_nlohmann_json = StringSplitter(
         nlohmann_json_file_destination_directory, '/').split();
      Blast::DirectoryCreator directory_creator(directories_needed_for_nlohmann_json, true);
      bool created = directory_creator.create();
      if (!created)
      {
         std::stringstream error_message;
         error_message << "Project/ReleaseBuilder error: could not create directory \""
                      << nlohmann_json_file_destination_directory
                      << "\"";
         throw std::runtime_error(error_message.str());
      }
      std::cout << " directory exists.";

      // execute the copy command
      Blast::ShellCommandExecutorWithCallback nlohmann_json_file_copy_executor(
            copy_nlohmann_json_file_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );
      nlohmann_json_file_copy_executor.execute();
      std::cout << "done." << std::endl;
   }


   if (get_remove_AllegroFlare_Network_from_allegro_flare_copy())
   {
      std::string include_folder_to_remove = destination_directory + "/include/AllegroFlare/Network";
      recursively_remove_folder_with_prompt(include_folder_to_remove);
      std::string src_folder_to_remove = destination_directory + "/src/AllegroFlare/Network";
      recursively_remove_folder_with_prompt(src_folder_to_remove);
   }


   if (get_remove_AllegroFlare_Testing_from_allegro_flare_copy())
   {
      std::string include_folder_to_remove = destination_directory + "/include/AllegroFlare/Testing";
      recursively_remove_folder_with_prompt(include_folder_to_remove);
      std::string src_folder_to_remove = destination_directory + "/src/AllegroFlare/Testing";
      recursively_remove_folder_with_prompt(src_folder_to_remove);
   }


   return;
}
} // namespace Project
} // namespace Blast


