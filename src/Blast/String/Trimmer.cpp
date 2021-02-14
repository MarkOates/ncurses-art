

#include <Blast/String/Trimmer.hpp>
#include <algorithm>


namespace Blast
{
namespace String
{


Trimmer::Trimmer(std::string text)
   : text(text)
{
}


Trimmer::~Trimmer()
{
}


std::string Trimmer::trim()
{
   std::string s1 = text;
   std::string s2 = rtrim(s1);
   std::string s3 = ltrim(s2);
   return s3;
}

std::string Trimmer::ltrim(std::string s)
{
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
   return s;
}

std::string Trimmer::rtrim(std::string s)
{
   s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c);}).base(), s.end());
   return s;
}
} // namespace String
} // namespace Blast


