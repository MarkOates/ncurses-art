#include <iostream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

void ___replace(std::string& str, std::string from, std::string to)
{
   //static const std::string from = "\t";
   //static const std::string to = std::string(3, ' ');

   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
}

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
   std::stringstream ss(s);
   std::string item;
   while (std::getline(ss, item, delim)) {
      *(result++) = item;
   }
}

std::vector<std::string> split(const std::string &s, char delim = ' ') {
   std::vector<std::string> elems;
   split(s, delim, std::back_inserter(elems));
   return elems;
}


std::vector<std::string> args;



int tab_count = 0;

#include "lib/command_line_argument_parser.h"


// ==============================================================================


class NamedArg
{
private:
   std::string named_arg;
   std::string default_value;

public:
   NamedArg(std::string named_arg, std::string default_value)
      : named_arg(named_arg)
      , default_value(default_value)
   {}

   friend std::ostream & operator<< (std::ostream &out, NamedArg const &named_arg)
   {
      out << std::string(tab_count, ' ') << "- NAMED_ARGUMENT definition (" << named_arg.named_arg << ")" << std::endl;
      tab_count += 3;
      out << std::string(tab_count, ' ') << "- name: " << named_arg.named_arg << std::endl;
      out << std::string(tab_count, ' ') << "- default_value: " << named_arg.default_value << std::endl;
      tab_count -= 3;

      return out;
   }

   static NamedArg make_from_string(std::string string)
   {
      std::vector<std::string> tokens = split(string, ':');
      if (tokens.empty()) throw std::runtime_error("tokens is empty");

      std::string arg_name = tokens[0];
      std::string default_value = (tokens.size() < 2) ? "" : tokens[1];

      return NamedArg(arg_name, default_value);
   }
};


class Method
{
private:
   std::string name;
   std::vector<NamedArg> named_args;

public:
   std::string get_name() { return name; }

   Method(std::string name, std::vector<NamedArg> named_args)
      : name(name)
      , named_args(named_args)
   {}

   friend std::ostream & operator<< (std::ostream &out, Method const &method)
   {
      out << std::string(tab_count, ' ') << "- METHOD definition (" << method.name << ")" << std::endl;
      tab_count += 3;
      out << std::string(tab_count, ' ') << "- name: " << method.name << std::endl;
      for (auto &named_arg : method.named_args) { out << named_arg; }
      tab_count -= 3;

      return out;
   }

   static Method make_from_args(std::vector<std::string> method_string_args)
   {
      if (method_string_args.empty()) throw std::runtime_error("method_string_args is empty and required for methods");

      std::string name = method_string_args[0];
      std::vector<std::string> named_arg_args(method_string_args.begin()+1, method_string_args.end());

      std::vector<NamedArg> named_args = {};

      for (auto &named_arg_arg : named_arg_args) named_args.push_back(NamedArg::make_from_string(named_arg_arg));

      return Method(method_string_args[0], named_args);
   }
};


class Class
{
private:
   std::string camel_case_name;
   std::string interface_name;
   std::string folder_name;
   std::vector<NamedArg> attr_readers_and_named_args;
   std::vector<Method> methods;

public:
   Class(std::string camel_case_name
      , std::string interface_name=""
      , std::string folder_name=""
      , std::vector<NamedArg> attr_readers_and_named_args={}
      , std::vector<Method> methods={}
   )
      : camel_case_name(camel_case_name)
      , interface_name(interface_name)
      , folder_name(folder_name)
      , attr_readers_and_named_args(attr_readers_and_named_args)
      , methods(methods)
   {}

   std::string get_camel_case_name()
   {
      return camel_case_name;
   }

   friend std::ostream & operator<< (std::ostream &out, Class const &klass)
   {
      out << std::string(tab_count, ' ') << "- CLASS definition (" << klass.camel_case_name << ")" << std::endl;
      tab_count += 3;
      out << std::string(tab_count, ' ') << "- camel_case_name: " << klass.camel_case_name << std::endl;
      out << std::string(tab_count, ' ') << "- interface_name: " << klass.interface_name << std::endl;
      out << std::string(tab_count, ' ') << "- folder_name: " << klass.folder_name << std::endl;
      out << std::string(tab_count, ' ') << "- attr_readers_and_named_args: " << std::endl;
      tab_count += 3;
      for (auto &attr_readers_and_named_arg : klass.attr_readers_and_named_args) { out << attr_readers_and_named_arg; }
      tab_count -= 3;
      out << std::string(tab_count, ' ') << "- methods: " << std::endl;
      tab_count += 3;
      for (auto &method : klass.methods) { out << method; }
      tab_count -= 3;

      tab_count -= 3;

      return out;
   }
};
// rg ClassName -i InterfaceName -f services -x Hamster -a named_arg_1 -i named_arg_2:'deafult_value' -m method_name method_named_arg:'default_value'



class ClassContentGenerator
{
private:
   Class &klass;

public:
   ClassContentGenerator(Class &klass)
      : klass(klass)
   {}

   std::string get_generated_content()
   {
      std::stringstream result;

      result << "class " << klass.get_camel_case_name() << std::endl;
      result << "end";

      return result.str();
   }
};


class CommandLineArgumentParser
{
private:
   const std::string UNSET = "[unset]";
   std::vector<std::string> command_line_args;
   Blast::CommandLineFlaggedArgumentsParser deducer;

   std::string const CLASS_NAME_FLAG = "-c";
   std::string const INTERFACE_FLAG = "-i";
   std::string const FOLDER_FLAG = "-f";
   std::string const MODULE_NAME_FLAG = "-n";
   std::string const ATTR_READERS_AND_NAMED_ARGS_FLAG = "-a";
   std::string const METHOD_FLAG = "-m";

public:
   CommandLineArgumentParser(std::vector<std::string> command_line_args)
      : command_line_args(command_line_args)
      , deducer(command_line_args)
   {}

   std::string get_camel_case_name_arg()
   {
      std::vector<std::vector<std::string>> args = deducer.get_flagged_args(CLASS_NAME_FLAG);
      if (args.empty()) throw std::runtime_error("CommandLineArgumentParser required class name (-c) flag is missing");
      return args[0][0];
   }

   std::string get_interface_name_arg()
   {
      std::vector<std::vector<std::string>> args = deducer.get_flagged_args(INTERFACE_FLAG);
      if (args.empty()) return "";
      return args[0][0];
   }

   std::string get_folder_name_arg()
   {
      std::vector<std::vector<std::string>> args = deducer.get_flagged_args(FOLDER_FLAG);
      if (args.empty()) return "";
      return args[0][0];
   }

   std::string get_module_name_arg()
   {
      std::vector<std::vector<std::string>> args = deducer.get_flagged_args(MODULE_NAME_FLAG);
      if (args.empty()) return "";
      return args[0][0];
   }

   std::vector<std::vector<std::string>> get_attr_readers_and_named_args_arg()
   {
      return deducer.get_flagged_args(ATTR_READERS_AND_NAMED_ARGS_FLAG);
   }

   std::vector<std::vector<std::string>> get_methods_args()
   {
      return deducer.get_flagged_args(METHOD_FLAG);
   }
};


class CommandLineArguemntToClassConverter
{
private:
   CommandLineArgumentParser &command_line_argument_parser;

public:
   CommandLineArguemntToClassConverter(CommandLineArgumentParser &command_line_argument_parser)
      : command_line_argument_parser(command_line_argument_parser)
   {
   }

   Class get_class()
   {
      std::vector<Method> methods;
      std::vector<std::vector<std::string>> method_args = command_line_argument_parser.get_methods_args();
      for (auto &method_arg : method_args) { methods.push_back(Method::make_from_args(method_arg)); }

      std::vector<NamedArg> named_args = {};
      std::vector<std::vector<std::string>> named_args_args = command_line_argument_parser.get_attr_readers_and_named_args_arg();
      std::vector<std::string> first_named_arg = named_args_args[0];

      for (auto &named_arg_arg : first_named_arg) named_args.push_back(NamedArg::make_from_string(named_arg_arg));

      return Class(
         command_line_argument_parser.get_camel_case_name_arg(),
         command_line_argument_parser.get_interface_name_arg(),
         command_line_argument_parser.get_folder_name_arg(),
         named_args,
         methods
      );
   }
};


std::string class_template = R"END(
class CLASSNAME
  attr_accessor ACCESSORS

  def initialize(NAMED_ARG_LIST)
  end

  def METHOD_NAME
  end
end
)END";


std::string class_test_template = R"END(
require 'test_helper'

class CLASSNAMETest < ActiveSupport::TestCase
  def CLASSNAME_SNAKECASE(ARGS)
    @CLASSNAME_SNAKECASE ||= CLASS_CONSTRUCTOR(ARGS)
  end

  test '#FUNCTION_NAME does a thing' do
  end
end
)END";


// rg ClassName -i InterfaceName -f services -n Hamster -a named_arg_1 named_arg_2 -m method_name(method_named_arg)


int main(int argc, char** argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   // rg -c ClassName -i InterfaceName -f services -n Hamster -a named_arg_1 named_arg_2 -m method_name(method_named_arg)

   std::vector<std::string> parser_args = {
      "-c", "ClassName",
      "-i", "InterfaceName",
      "-f", "folder_name",
      "-n", "ModuleName",
      "-a", "named_arg_1", "named_arg_2:'default_value'",
      "-m", "method_name", "method_named_arg:'another_default'",
      "-m", "another_method_name", "another_method_named_arg:'another_default'",
   };

   CommandLineArgumentParser parser(parser_args);
   CommandLineArguemntToClassConverter converter(parser);
   Class klass = converter.get_class();

   std::cout << klass;

   return 0;
}


