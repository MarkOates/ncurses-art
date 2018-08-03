#pragma once


#include <string>
#include <vector>


class Flag
{
private:
   std::string flag;
   std::vector<std::string> arguments;
   std::string description;

public:
   Flag(std::string flag="", std::vector<std::string> arguments={}, std::string description="[description not provided]");
   ~Flag();


   std::string get_flag();
   std::vector<std::string> get_arguments();
   std::string get_description();
};



