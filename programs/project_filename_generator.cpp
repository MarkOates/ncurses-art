

#include <allegro5/allegro.h> // required for compliance with union/Makefile

#include <iostream>
#include <string>
#include <vector>


std::string help_text = R"END(
Project Filename Generator (C++)

This program takes a basename for a Blast project file and outputs
various parallel files based on that basename.  In the Blast project
format, each component has 7 files, listed below:

* Source file (.cpp file)
* Header file (.hpp file)
* Test file (.cpp file)
* Example file (.cpp file)
* Compiled source file (.o file)
* Compiled test binary (.exe file)
* Compiled example program (.exe file)

Use the following switches to pass arguments to the program:

Input flags:

-x extract basename (pass in filename)
-b set basename
-_ use underscore naming convention (defaults to CamelCase)

Output flags:

-a return all
-B basename
-q quintessence filename
-s source filename
-S source binary
-h header filename
-t test filename
-T test binary
-e example filename
-E example binary

Examples:

Setting the basename, and then obtaining a test filename

$> bin/programs/project_filename_generator -bFoobar -t

Passing along any project filename, and then obtaining the basename

$> bin/programs/project_filename_generator -xinclude/MyProject/Models/User.hpp -B
)END";



#include <ProjectComponentBasenameExtractor.hpp>
#include <ProjectFilenameGenerator.hpp>



int main(int argc, char **argv)
{
   std::vector<std::string> arguments(argv, argv+argc);
   //for (int i=1; i<argc; i++) arguments.push_back(argv[i]);

   std::string basename = "";

   if (arguments.size() <= 1) { std::cout << help_text << std::endl; return 0; }

   bool underscores = false;

   for (auto &argument : arguments)
   {
      if (argument.compare(0, 2, "-_") == 0) { underscores = true; }
      if (argument.compare(0, 2, "-b") == 0) { basename = argument.substr(2); }
      if (argument.compare(0, 2, "-x") == 0)
      {
         std::string filename_to_extract_from = argument.substr(2);
         ProjectComponentBasenameExtractor component_basename_extractor = ProjectComponentBasenameExtractor(filename_to_extract_from);
         //std::cout << "Extracted: " << component_basename_extractor.identify_file_type() << std::endl;
         //std::cout << "Basename: " << component_basename_extractor.identify_component_basename() << std::endl;
         basename = component_basename_extractor.identify_component_basename();
      }
   }

   ProjectFilenameGenerator project_component_filenames(basename, underscores);

   for (auto &argument : arguments)
   {
      if (argument.compare(0, 3, "-a") == 0)
      {
         std::cout << "-B: " << project_component_filenames.get_basename() << std::endl;
         std::cout << "-q: " << project_component_filenames.generate_quintessence_filename() << std::endl;
         std::cout << "-s: " << project_component_filenames.generate_source_filename() << std::endl;
         std::cout << "-S: " << project_component_filenames.generate_obj_binary() << std::endl;
         std::cout << "-h: " << project_component_filenames.generate_header_filename() << std::endl;
         std::cout << "-t: " << project_component_filenames.generate_test_src_filename() << std::endl;
         std::cout << "-T: " << project_component_filenames.generate_test_binary() << std::endl;
         std::cout << "-e: " << project_component_filenames.generate_example_src_filename() << std::endl;
         std::cout << "-E: " << project_component_filenames.generate_example_binary() << std::endl;
         return 0;
      }
      if (argument.compare(0, 3, "-B") == 0) { std::cout << project_component_filenames.get_basename(); return 0; }
      if (argument.compare(0, 3, "-q") == 0) { std::cout << project_component_filenames.generate_quintessence_filename(); return 0; }
      if (argument.compare(0, 3, "-s") == 0) { std::cout << project_component_filenames.generate_source_filename(); return 0; }
      if (argument.compare(0, 3, "-S") == 0) { std::cout << project_component_filenames.generate_obj_binary(); return 0; }
      if (argument.compare(0, 3, "-h") == 0) { std::cout << project_component_filenames.generate_header_filename(); return 0; }
      if (argument.compare(0, 3, "-t") == 0) { std::cout << project_component_filenames.generate_test_src_filename(); return 0; }
      if (argument.compare(0, 3, "-T") == 0) { std::cout << project_component_filenames.generate_test_binary(); return 0; }
      if (argument.compare(0, 3, "-e") == 0) { std::cout << project_component_filenames.generate_example_src_filename(); return 0; }
      if (argument.compare(0, 3, "-E") == 0) { std::cout << project_component_filenames.generate_example_binary(); return 0; }
   }
}


