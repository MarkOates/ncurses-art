

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
s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
return s;

}

std::string StringTrimmer::rtrim(std::string s)
{
s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
return s;

}


