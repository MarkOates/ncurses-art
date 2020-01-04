#include <Blast/Project/ReleaseBuilder.hpp>

int main(int argc, char **argv)
{
   std::string destination_directory="/Users/markoates/Desktop/Release";
   Blast::Project::ReleaseBuilder release_builder(destination_directory);
   release_builder.generate_source_release();

   return 0;
}
