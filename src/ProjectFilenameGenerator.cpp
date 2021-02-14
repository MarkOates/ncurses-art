

#include <ProjectFilenameGenerator.hpp>





ProjectFilenameGenerator::ProjectFilenameGenerator(std::string basename, bool underscores)
   : basename(basename)
   , underscores(underscores)
{
}


ProjectFilenameGenerator::~ProjectFilenameGenerator()
{
}


std::string ProjectFilenameGenerator::get_basename()
{
   return basename;
}


std::string ProjectFilenameGenerator::generate_quintessence_filename()
{
   return std::string("quintessence/") + basename + ".q.yml";
}

std::string ProjectFilenameGenerator::generate_source_filename()
{
   return std::string("src/") + basename + ".cpp";
}

std::string ProjectFilenameGenerator::generate_header_filename()
{
   return std::string("include/") + basename + ".hpp";
}

std::string ProjectFilenameGenerator::generate_test_src_filename()
{
   return std::string("tests/") + basename + (underscores ? "_test" : "Test") + ".cpp";
}

std::string ProjectFilenameGenerator::generate_example_src_filename()
{
   return std::string("examples/") + basename + (underscores ? "_example.cpp" : "Example.cpp");
}

std::string ProjectFilenameGenerator::generate_obj_binary()
{
   return std::string("obj/") + basename + ".o";
}

std::string ProjectFilenameGenerator::generate_test_binary()
{
   return std::string("bin/tests/") + basename + (underscores ? "_test" : "Test");
}

std::string ProjectFilenameGenerator::generate_example_binary()
{
   return std::string("bin/examples/") + basename + (underscores ? "_example.cpp" : "Example.cpp");
}


