#include <ncurses_art/Element/ElementBase.hpp>

ElementBase::ElementBase(std::string type)
   : type(type)
   , name("")
{
}

ElementBase::~ElementBase()
{
}

bool ElementBase::set_name(std::string name)
{
   this->name = name;
   return true;
}

std::string ElementBase::get_type()
{
   return type;
}

std::string ElementBase::get_name()
{
   return name;
}

bool ElementBase::is_type(std::string type)
{
   return this->type == type;
}

bool ElementBase::is_name(std::string name)
{
   return this->name == name;
}
