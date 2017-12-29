#include <ncurses_art/Element/ElementBase.h>

ElementBase::ElementBase(std::string type)
   : type(type)
{
}

ElementBase::~ElementBase()
{
}

std::string ElementBase::get_type()
{
   return type;
}

bool ElementBase::is_type(std::string type)
{
   return this->type == type;
}
