

#include <ProjectComponentBasenameExtractor.hpp>





ProjectComponentBasenameExtractor::ProjectComponentBasenameExtractor(std::string filename)
   : filename(filename)
{
}


ProjectComponentBasenameExtractor::~ProjectComponentBasenameExtractor()
{
}


std::string ProjectComponentBasenameExtractor::identify_file_type()
{
return extract_component().first;
}

std::string ProjectComponentBasenameExtractor::identify_component_basename()
{
return extract_component().second;
}

std::pair<std::string, std::string> ProjectComponentBasenameExtractor::extract_component()
{
std::pair<std::string, std::string> result = std::pair<std::string, std::string>("", "");
if (filename.compare(0, 13, "quintessence/") == 0)
{
   std::string extracted = filename.substr(13);
   std::string search_string = ".q.yml";
   std::size_t found = extracted.rfind(search_string);
   extracted = extracted.substr(0, found);
   return std::make_pair("quintessence file", extracted);
}
else if (filename.compare(0, 4, "src/") == 0)
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
   found = extracted.rfind("_test");
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
   found = extracted.rfind("_example");
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
   found = extracted.rfind("_test");
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
   found = extracted.rfind("_example");
   extracted = extracted.substr(0, found);
   return std::make_pair("bin/example file", extracted);
}
else
{
   std::string extracted = "";
   return std::make_pair("not identifiable", "");
}

}


