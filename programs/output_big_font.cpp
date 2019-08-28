#include <sstream>
#include <iostream>

int main()
{
   // text from https://psfonttk.com/big-text-generator/
std::stringstream ss;
ss <<
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░" << std::endl <<
"░░░░█▀▀█ █▀▀█ █▀▀█ ░░▀ █▀▀ █▀▀ ▀▀█▀▀ ▄░░░░" << std::endl <<
"░░░░█░░█ █▄▄▀ █░░█ ░░█ █▀▀ █░░ ░░█░░ ░░░░░" << std::endl <<
"░░░░█▀▀▀ ▀░▀▀ ▀▀▀▀ █▄█ ▀▀▀ ▀▀▀ ░░▀░░ ▀░░░░" << std::endl <<
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░" << std::endl <<
std::endl;

   std::cout << ss.str();
}
