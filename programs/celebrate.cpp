#include <Blast/Build/Celebrator.hpp>
#include <Blast/StringJoiner.hpp>
#include <Blast/CommandLineFlaggedArgumentsParser.hpp>
#include <AllegroFlare/ConsoleColor.hpp>
#include <iostream>
#include <stdlib.h> // for atoi


using Blast::CommandLineFlaggedArgumentsParser;


int main(int argc, char **argv)
{
   std::vector<std::string> raw_args;
   for (int i=0; i<argc; i++) raw_args.push_back(argv[i]);

   CommandLineFlaggedArgumentsParser args(raw_args);

   std::string message = "";
   if (!args.has_flag("-m"))
   {
      throw std::runtime_error("you must pass a message behind a \"-m\" flag.");
   }
   else
   {
      auto first_set = args.get_flagged_args("-m")[0];
      message = Blast::StringJoiner(first_set, " ").join();
   }

   int length = 80;
   if (args.has_flag("-l"))
   {
      std::vector<std::vector<std::string>> number = args.get_flagged_args("-l");
      length = atoi(number[0][0].c_str());
   }

   std::string color_string = "";
   std::string closing_color_string = "";
   if (args.has_flag("-c"))
   {
      std::vector<std::vector<std::string>> number = args.get_flagged_args("-c");
      std::string color_arg = number[0][0].c_str();
      if (color_arg == "yellow")
      {
         color_string = CONSOLE_COLOR_YELLOW;
         closing_color_string = CONSOLE_COLOR_DEFAULT;
      }
   }

   Blast::Build::Celebrator celebrator;
   std::cout
      << color_string
      << celebrator.generate_full_width_output_banner(message, length)
      << closing_color_string
      << std::endl;
   return 0;
}
