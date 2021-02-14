

#include <NcursesArt/Rails/ComponentFilenameGenerator.hpp>
#include <sstream>


namespace NcursesArt
{
namespace Rails
{


ComponentFilenameGenerator::ComponentFilenameGenerator(std::string component_basename)
   : component_basename(component_basename)
{
}


ComponentFilenameGenerator::~ComponentFilenameGenerator()
{
}


std::string ComponentFilenameGenerator::get_component_basename()
{
   return component_basename;
}


std::string ComponentFilenameGenerator::get_model_filename()
{
   std::stringstream result;
   result << "app/models/" << component_basename << ".rb"; 
   return result.str();
}
} // namespace Rails
} // namespace NcursesArt


