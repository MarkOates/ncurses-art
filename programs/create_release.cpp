#include <Blast/Project/ReleaseBuilder.hpp>

int main(int argc, char **argv)
{
   // call from whatever project directory you're in, it will add the release to the "~/Desktop/Release/" folder.

   std::string destination_directory="/Users/markoates/Desktop/Release";
   Blast::Project::ReleaseBuilder release_builder(destination_directory);
   release_builder.generate_source_release();

   return 0;
}
