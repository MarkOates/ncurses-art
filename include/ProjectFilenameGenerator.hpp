#pragma once


#include <string>


class ProjectFilenameGenerator
{
private:
   std::string basename;
   bool underscores;

public:
   ProjectFilenameGenerator(std::string basename="", bool underscores="");
   ~ProjectFilenameGenerator();


   std::string get_basename();
std::string get_quintessence_filename();
std::string get_source_filename();
std::string get_header_filename();
std::string get_test_src_filename();
std::string get_example_src_filename();
std::string get_obj_binary();
std::string get_test_binary();
std::string get_example_binary();
};



