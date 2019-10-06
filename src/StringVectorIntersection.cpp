

#include <StringVectorIntersection.hpp>
#include <algorithm>
#include <algorithm>




StringVectorIntersection::StringVectorIntersection(std::vector<std::string> v1, std::vector<std::string> v2)
   : v1(v1)
   , v2(v2)
{
}


StringVectorIntersection::~StringVectorIntersection()
{
}


std::vector<std::string> StringVectorIntersection::intersection()
{
std::vector<std::string> result;
std::vector<std::string>::iterator it;

it = std::set_intersection(v1.begin(), v1.begin()+5, v2.begin(), v2.begin()+5, result.begin());

result.resize(it - result.begin());

return result;

}


