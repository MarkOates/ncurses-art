

#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class CommandLineFlaggedArgumentsParser
   {
   private:
      std::vector<std::string> command_line_args;

   public:
      CommandLineFlaggedArgumentsParser(std::vector<std::string> command_line_args);
      ~CommandLineFlaggedArgumentsParser();

      bool is_flag_present(std::string flag);
      std::vector<std::vector<std::string>> get_flagged_args(std::string flag);

   private:

      std::vector<int> find_flag_positions(std::string flag);
      std::vector<std::string> get_args_within_flag(int arg_position);
      bool is_flag(std::string potential_flag_value);
   };
} // namespace Blast




//#include <Blast/CommandLineFlaggedArgumentsParser.hpp>

#include <sstream>


namespace Blast
{


CommandLineFlaggedArgumentsParser::CommandLineFlaggedArgumentsParser(std::vector<std::string> command_line_args)
   : command_line_args(command_line_args)
{}


CommandLineFlaggedArgumentsParser::~CommandLineFlaggedArgumentsParser()
{}


bool CommandLineFlaggedArgumentsParser::is_flag_present(std::string flag)
{
   if (!is_flag(flag))
   {
      std::stringstream error_message;
      error_message << "[CommandLineFlaggedArgumentsParser::is_flag_present] error: \"" << flag << "\" is not a valid formatted flag; It must start with '-' character.";
      throw std::runtime_error(error_message.str());
   }

   std::vector<std::vector<std::string>> results;
   for (auto &command_line_arg : command_line_args) { if (command_line_arg == flag) return true; }
   return false;
}


std::vector<std::vector<std::string>> CommandLineFlaggedArgumentsParser::get_flagged_args(std::string flag)
{
   std::vector<std::vector<std::string>> results;

   std::vector<int> positions = find_flag_positions(flag);
   for (int i=0; i<positions.size(); i++)
   {
      results.push_back(get_args_within_flag(positions[i]));
   }
   return results;
}


std::vector<int> CommandLineFlaggedArgumentsParser::find_flag_positions(std::string flag)
{
   std::vector<int> positions;
   for (int i=0; i<command_line_args.size(); i++) { if (command_line_args[i] == flag) positions.push_back(i); }
   return positions;
}


std::vector<std::string> CommandLineFlaggedArgumentsParser::get_args_within_flag(int arg_position)
{
   std::vector<std::string> args;
   for (int i=(arg_position+1); i<command_line_args.size(); i++)
   {
      if (is_flag(command_line_args[i])) break;
      else args.push_back(command_line_args[i]);
   }
   return args;
}


bool CommandLineFlaggedArgumentsParser::is_flag(std::string potential_flag_value)
{
   if (potential_flag_value.size() < 2) return false;
   if (potential_flag_value[0] == '-') return true;
   return false;
}


} // namespace Blast



