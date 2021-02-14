

#include <Blast/StringSplitter.hpp>
#include <sstream>
#include <vector>
#include <string>


namespace Blast
{


StringSplitter::StringSplitter(std::string string, char delimiter)
   : string(string)
   , delimiter(delimiter)
{
}


StringSplitter::~StringSplitter()
{
}


std::vector<std::string> StringSplitter::split()
{
   std::vector<std::string> elems;
   auto result = std::back_inserter(elems);
   std::stringstream ss(string);
   std::string item;
   while (std::getline(ss, item, delimiter)) { *(result++) = item; }
   return elems;
}
} // namespace Blast


