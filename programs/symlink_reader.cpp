#include <unistd.h>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
   std::string filename = "/Users/markoates/Repos/LabyrinthOfLore/include/AllegroFlare/Inventory.hpp";
   char linkname[256];

/*
   // from https://linux.die.net/man/2/readlink
   //ssize_t readlink(const char *path, char *buf, size_t bufsiz);
   ssize_t r;
   r = readlink(filename.c_str(), linkname, 256);

   std::cout << filename << " -> " << linkname << std::endl;

   //if (r
*/

   std::cerr << "This program will not work because the default behavior has been diesabled so the system can compile on Windows." << std::endl;

   return 0;
}


