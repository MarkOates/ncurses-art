#pragma once


#include <string>


class HostnameExtractor
{
private:

public:
   HostnameExtractor();
   ~HostnameExtractor();

   std::string get_computer_name();
};



