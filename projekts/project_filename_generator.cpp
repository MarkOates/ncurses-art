

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
-s source filename
-S source binary
-h header filename
-t test filename
-T test binary
-e example filename
-E example binary
)END";



class ProjectComponentBasenameExtractor
{
private:
   std::string filename;

public:
   ProjectComponentBasenameExtractor(std::string filename)
      : filename(filename)
   {}
   std::pair<std::string, std::string> extract_component()
   {
      std::pair<std::string, std::string> result = std::pair<std::string, std::string>("", "");
      if (filename.compare(0, 4, "src/") == 0)
      {
         std::string extracted = filename.substr(4);
         std::size_t found = extracted.find_first_of(".");
         extracted = extracted.substr(0, found);
         return std::make_pair("src_file", extracted);
      }
      else if (filename.compare(0, 8, "include/") == 0)
      {
         std::string extracted = filename.substr(8);
         std::size_t found = extracted.find_first_of(".");
         extracted = extracted.substr(0, found);
         return std::make_pair("include file", extracted);
      }
      else if (filename.compare(0, 6, "tests/") == 0)
      {
         std::string extracted = filename.substr(6);
         std::size_t found = extracted.find_first_of(".");
         extracted = extracted.substr(0, found);
         found = extracted.rfind("Test");
         extracted = extracted.substr(0, found);
         return std::make_pair("test file", extracted);
      }
      else if (filename.compare(0, 9, "examples/") == 0)
      {
         std::string extracted = filename.substr(9);
         std::size_t found = extracted.find_first_of(".");
         extracted = extracted.substr(0, found);
         found = extracted.rfind("Example");
         extracted = extracted.substr(0, found);
         return std::make_pair("example file", extracted);
      }
      else if (filename.compare(0, 4, "obj/") == 0)
      {
         std::string extracted = filename.substr(4);
         std::size_t found = extracted.find_first_of(".");
         extracted = extracted.substr(0, found);
         return std::make_pair("object file", extracted);
      }
      else if (filename.compare(0, 10, "bin/tests/") == 0)
      {
         std::string extracted = filename.substr(10);
         std::size_t found = extracted.find_first_of(".");
         extracted = extracted.substr(0, found);
         found = extracted.rfind("Test");
         extracted = extracted.substr(0, found);
         return std::make_pair("bin/test file", extracted);
      }
      else if (filename.compare(0, 13, "bin/examples/") == 0)
      {
         std::string extracted = filename.substr(13);
         std::size_t found = extracted.find_first_of(".");
         extracted = extracted.substr(0, found);
         found = extracted.rfind("Example");
         extracted = extracted.substr(0, found);
         return std::make_pair("bin/example file", extracted);
      }
      else
      {
         std::string extracted = "";
         return std::make_pair("not identifiable", "");
      }
   }
   std::string identify_file_type()
   {
      return extract_component().first;
   }
   std::string identify_component_basename()
   {
      return extract_component().second;
   }
};


class ProjectFilenameGenerator
{
private:
   std::string basename;
   bool underscores;
   //std::string project_name;

public:
  // ObjectSrcComponents(std::string basename, std::string project_name)
   ProjectFilenameGenerator(std::string basename, bool underscores)
      : basename(basename)
      , underscores(underscores)
      //, project_name(project_name)
   {}
   std::string get_source_filename() { return std::string("src/") + basename + ".cpp"; }
   //std::string get_header_filename() { return std::string("include/") + project_name + "/" + basename + ".cpp"; }
   std::string get_header_filename() { return std::string("include/") + basename + ".hpp"; }
   std::string get_test_src_filename() { return std::string("tests/") + basename + (underscores ? "_test" : "Test") + ".cpp"; }
   std::string get_example_src_filename() { return std::string("examples/") + basename + (underscores ? "_example.cpp" : "Example.cpp"); }

   std::string get_obj_binary() { return std::string("obj/") + basename + ".o"; }
   std::string get_test_binary() { return std::string("bin/tests/") + basename + (underscores ? "_test" : "Test"); }
   std::string get_example_binary() { return std::string("bin/examples/") + basename + (underscores ? "_example.cpp" : "Example.cpp"); }
};


int main(int argc, char **argv)
{
   std::vector<std::string> arguments(argv, argv+argc);
   //for (int i=1; i<argc; i++) arguments.push_back(argv[i]);

   std::string basename = "";

   if (arguments.empty()) { std::cout << help_text << std::endl; return 0; }

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
         std::cout << "-s: " << project_component_filenames.get_source_filename() << std::endl;
         std::cout << "-S: " << project_component_filenames.get_obj_binary() << std::endl;
         std::cout << "-h: " << project_component_filenames.get_header_filename() << std::endl;
         std::cout << "-t: " << project_component_filenames.get_test_src_filename() << std::endl;
         std::cout << "-T: " << project_component_filenames.get_test_binary() << std::endl;
         std::cout << "-e: " << project_component_filenames.get_example_src_filename() << std::endl;
         std::cout << "-E: " << project_component_filenames.get_example_binary() << std::endl;
         return 0;
      }
      if (argument.compare(0, 3, "-s") == 0) { std::cout << project_component_filenames.get_source_filename(); return 0; }
      if (argument.compare(0, 3, "-S") == 0) { std::cout << project_component_filenames.get_obj_binary(); return 0; }
      if (argument.compare(0, 3, "-h") == 0) { std::cout << project_component_filenames.get_header_filename(); return 0; }
      if (argument.compare(0, 3, "-t") == 0) { std::cout << project_component_filenames.get_test_src_filename(); return 0; }
      if (argument.compare(0, 3, "-T") == 0) { std::cout << project_component_filenames.get_test_binary(); return 0; }
      if (argument.compare(0, 3, "-e") == 0) { std::cout << project_component_filenames.get_example_src_filename(); return 0; }
      if (argument.compare(0, 3, "-E") == 0) { std::cout << project_component_filenames.get_example_binary(); return 0; }
   }
}


