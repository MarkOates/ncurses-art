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

std::vector<std::string> args;

int tab_count = 0;

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
};


class Method
{
private:
   std::string name;
   std::vector<NamedArg> named_args;

public:
   Method(std::string name, std::vector<NamedArg> named_args)
      : name(name)
      , named_args(named_args)
   {}

   friend std::ostream & operator<< (std::ostream &out, Method const &method)
   {
      out << std::string(tab_count, ' ') << "- METHOD definition (" << method.name << ")" << std::endl;
      tab_count += 3;
      out << std::string(tab_count, ' ') << "- name: " << method.name << std::endl;
      for (auto &named_arg : method.named_args)
      {
         out << std::string(tab_count, ' ') << named_arg << std::endl;
      }
      tab_count -= 3;

      return out;
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
      return "[CamelCaseNameNotImplemented]";
   }

   friend std::ostream & operator<< (std::ostream &out, Class const &klass)
   {
      out << std::string(tab_count, ' ') << "- CLASS definition (" << klass.camel_case_name << ")" << std::endl;
      tab_count += 3;
      out << std::string(tab_count, ' ') << "- camel_case_name: " << klass.camel_case_name << std::endl;
      out << std::string(tab_count, ' ') << "- interface_name: " << klass.interface_name << std::endl;
      out << std::string(tab_count, ' ') << "- folder_name: " << klass.folder_name << std::endl;
      out << std::string(tab_count, ' ') << "- attr_readers_and_named_args: " << "stream not implemented" << std::endl;
      out << std::string(tab_count, ' ') << "- methods: " << "stream not implemented" << std::endl;

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

public:
   CommandLineArgumentParser(std::vector<std::string> command_line_args)
      : command_line_args(command_line_args)
   {}

   std::string get_camel_case_name()
   {
      if (command_line_args.empty()) throw std::runtime_error("CommandLineArgumentParser required class name is missing");
      return command_line_args[0];
   }

   std::string get_interface_name() { return UNSET; }
   std::string get_folder_name() { return UNSET; }
   std::vector<NamedArg> get_attr_readers_and_named_args() { return {}; }
   std::vector<Method> get_methods() { return {}; }
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
      return Class(
         command_line_argument_parser.get_camel_case_name(),
         command_line_argument_parser.get_interface_name(),
         command_line_argument_parser.get_folder_name(),
         command_line_argument_parser.get_attr_readers_and_named_args(),
         command_line_argument_parser.get_methods()
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
      "-f", "services",
      "-n", "Hamster",
      "-a", "named_arg_1", "named_arg_2:'default_value'",
      "-m", "method_name", "method_named_arg:'another_default'",
   };

   CommandLineArgumentParser parser(parser_args);
   CommandLineArguemntToClassConverter converter(parser);
   Class klass = converter.get_class();

   std::cout << klass;

   return 0;
}

