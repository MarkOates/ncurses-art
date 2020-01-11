#include <Blast/Build/Celebrator.hpp>
#include <iostream>

int main(int argc, char **argv)
{
   Blast::Build::Celebrator celebrator;
   std::cout << celebrator.generate_full_width_output_banner("Hello World!") << std::endl;
   return 0;
}
