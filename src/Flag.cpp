

#include </Flag.hpp>




Flag::Flag(std::string flag, std::vector<std::string> arguments, std::string description)
   : flag(flag)
   , arguments(arguments)
   , description(description)
{
}


Flag::~Flag()
{
}


std::string Flag::get_flag()
{
   return flag;
}


std::vector<std::string> Flag::get_arguments()
{
   return arguments;
}


std::string Flag::get_description()
{
   return description;
}




