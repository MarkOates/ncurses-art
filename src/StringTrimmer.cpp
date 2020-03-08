

#include <StringTrimmer.hpp>
#include <algorithm>




StringTrimmer::StringTrimmer(std::string text)
   : text(text)
{
}


StringTrimmer::~StringTrimmer()
{
}


std::string StringTrimmer::trim()
{
std::string s1 = text;
std::string s2 = rtrim(s1);
std::string s3 = ltrim(s2);
return s3;

}

std::string StringTrimmer::ltrim(std::string s)
{
s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
return s;

}

std::string StringTrimmer::rtrim(std::string s)
{
s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c);}).base(), s.end());
return s;

}


