#include <sstream>

int main(int argc, char **argv)
{
   std::strinstream output_message;
   output_message << "This executable is no longer the target.  The executable has been moved to the Blast project.";
   throw std::runtime_error(output_message.str());
}
