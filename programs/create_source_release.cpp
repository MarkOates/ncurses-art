#include <allegro5/allegro.h>

#include <Blast/Project/SourceReleaseBuilder.hpp>

int main(int argc, char **argv)
{
   // call from whatever project directory you're in, it will add the release to the "~/Desktop/Release/" folder.

   std::string destination_directory="/Users/markoates/Desktop/Release";
   Blast::Project::SourceReleaseBuilder source_release_builder(destination_directory);
   source_release_builder.generate_source_release();

   return 0;
}
