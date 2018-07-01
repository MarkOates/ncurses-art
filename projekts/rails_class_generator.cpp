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

// The generic approach
template<typename T>
std::string pad(std::basic_string<T> string, typename std::basic_string<T>::size_type n, T c)
{
   std::string s = string;
   if (n > s.length()) s.append(n - s.length(), c);
   return s;
}

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

std::string to_camel_case(std::string camelString)
{
   for (int x = 0; x < camelString.length(); x++)
   {
      if (camelString[x] == '_'){
         std::string tempString = camelString.substr(x + 1, 1);
         transform(tempString.begin(), tempString.end(), tempString.begin(), toupper);
         camelString.erase(x, 2);
         camelString.insert(x, tempString);
      }
   }

   return camelString;
}

#include <algorithm>
#include <iostream>
#include <cctype>

//bool all_caps(const std::string &s) {
   //return std::none_of(s.begin(), s.end(), ::islower);
//}

// Convert lowerCamelCase and UpperCamelCase strings to lower_with_underscore.
std::string to_snake_case(std::string camelCase) {
   std::string str(1, tolower(camelCase[0]));

   // First place underscores between contiguous lower and upper case letters.
   // For example, `_LowerCamelCase` becomes `_Lower_Camel_Case`.
   for (auto it = camelCase.begin() + 1; it != camelCase.end(); ++it) {
      if (isupper(*it) && *(it-1) != '_' && islower(*(it-1))) {
         str += "_";
      }
      str += *it;
   }

   // Then convert it to lower case.
   std::transform(str.begin(), str.end(), str.begin(), ::tolower);

   return str;
}

std::string join(std::vector<std::string> tokens, std::string delim)
{
   std::stringstream result;
   bool last = false;

   for (unsigned i=0; i<tokens.size(); i++)
   {
      result << tokens[i];
      if (i==tokens.size()-1) last = true;
      if (!last) result << delim;
   }

   return result.str();
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

   std::string get_named_arg()
   {
      return named_arg;
   }

   std::string get_default_value()
   {
      return default_value;
   }

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

   std::vector<NamedArg> get_named_args()
   {
      return named_args;
   }

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

   std::string get_interface_name()
   {
      return interface_name;
   }

   std::string get_folder_name()
   {
      return folder_name;
   }

   std::vector<NamedArg> get_attr_readers_and_named_args()
   {
      return attr_readers_and_named_args;
   }

   std::vector<Method> get_methods()
   {
      return methods;
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

      std::vector<std::string> in_code_blocks = {
         generate_attr_reader_line(),
         generate_initializer_line(),
      };

      std::vector<std::string> method_lines = generate_methods_line();

      for (auto &method_line : method_lines) in_code_blocks.push_back(method_line);

      result << "class " << klass.get_camel_case_name() << std::endl;
      result << join(in_code_blocks, "\n");
      result << "end" << std::endl;

      return result.str();
   }

private:

   std::string generate_attr_reader_line()
   {
      std::stringstream result;

      if (has_attr_accessors())
      {
         std::vector<NamedArg> named_args = klass.get_attr_readers_and_named_args();
         result << "  attr_reader ";
         std::vector<std::string> named_args_as_symbols;

         for (auto &named_arg : named_args) { named_args_as_symbols.push_back(std::string(":") + named_arg.get_named_arg()); }
         result << join(named_args_as_symbols, ", ") << std::endl;
      }

      return result.str();
   }

   std::string generate_initializer_line()
   {
      std::stringstream result;

      if (has_attr_accessors())
      {
         std::vector<NamedArg> named_args = klass.get_attr_readers_and_named_args();
         result << "  def initializer(";
         std::vector<std::string> named_args_as_symbols;

         for (auto &named_arg : named_args) { named_args_as_symbols.push_back(named_arg.get_named_arg() + ":"); }
         result << join(named_args_as_symbols, ", ");
         result << ")" << std::endl;
         for (auto &named_arg : named_args)
         {
            std::string arg = named_arg.get_named_arg();
            result << "    @" << arg << " = " << arg << std::endl;
         }
         result << "  end" << std::endl;
      }

      return result.str();
   }

   std::vector<std::string> generate_methods_line()
   {
      std::vector<std::string> result;

      if (has_methods())
      {
         std::vector<Method> methods = klass.get_methods();

         for (auto &method : methods)
         {
            std::stringstream method_result;

            std::stringstream args_result;
            std::vector<NamedArg> named_args = method.get_named_args();
            std::vector<std::string> named_args_as_symbols;

            for (auto &named_arg : named_args) { named_args_as_symbols.push_back(named_arg.get_named_arg() + std::string(":")); }
            args_result << join(named_args_as_symbols, ", ");

            method_result << "  def " << method.get_name() << "(" << args_result.str() << ")" << std::endl;
            method_result << "  end" << std::endl;

            result.push_back(method_result.str());
         }
      }

      return result;
   }

   bool has_attr_accessors()
   {
      return !klass.get_attr_readers_and_named_args().empty();
   }

   bool has_methods()
   {
      return !klass.get_methods().empty();
   }
};

class ClassTestContentGenerator
{
private:
   Class &klass;

public:
   ClassTestContentGenerator(Class &klass)
      : klass(klass)
   {}

   std::string get_generated_content()
   {
      std::stringstream result;

      std::vector<std::string> in_code_blocks = {
         generate_class_in_question_convience_method()
      };

      for (auto &method : klass.get_methods()) in_code_blocks.push_back(generate_method_test(method));

      result << "require 'test_helper'" << std::endl;
      result << std::endl;
      result << "class " << klass.get_camel_case_name() << "Test < ActiveSupport::TestCase" << std::endl;
      result << join(in_code_blocks, "\n");
      result << "end" << std::endl;

      return result.str();
   }

private:

   std::string generate_class_in_question_convience_method()
   {
      std::stringstream result;
      result << "  def " << to_snake_case(klass.get_camel_case_name()) << std::endl;
      result << "  end" << std::endl;
      return result.str();
   }

   std::string generate_method_test(Method &method)
   {
      std::stringstream result;
      result << "  test '#" << method.get_name() << " does a thing' do" << std::endl;
      result << "  end" << std::endl;
      return result.str();
   }

   bool has_attr_accessors()
   {
      return !klass.get_attr_readers_and_named_args().empty();
   }

   bool has_methods()
   {
      return !klass.get_methods().empty();
   }
};


// component
   // dependency
   // expected usage of the dependency


class CommandLineArgumentParser
{
private:
   const std::string UNSET = "[unset]";
   std::vector<std::string> command_line_args;
   Blast::CommandLineFlaggedArgumentsParser deducer;

   std::pair<std::string, std::string> const CLASS_NAME_FLAG = { "-c", "class name" };
   std::pair<std::string, std::string> const INTERFACE_FLAG = { "-i", "interface (or parent class)" };
   std::pair<std::string, std::string> const FOLDER_FLAG = { "-f", "the folder in which the class is located" };
   std::pair<std::string, std::string> const MODULE_NAME_FLAG = { "-n", "module name that encapsulates the class" };
   std::pair<std::string, std::string> const ATTR_READERS_AND_NAMED_ARGS_FLAG = { "-a", "initializer args (also attr_readers)" };
   std::pair<std::string, std::string> const METHOD_FLAG = { "-m", "method. format: [class_name named_arg:'optional_default_value' named_arg2]" };
   std::pair<std::string, std::string> const HELP_FLAG = { "--help", "help. You're here." };

   const std::vector<std::pair<std::string, std::string>> flags = {
      CLASS_NAME_FLAG,
      INTERFACE_FLAG,
      FOLDER_FLAG,
      MODULE_NAME_FLAG,
      ATTR_READERS_AND_NAMED_ARGS_FLAG,
      METHOD_FLAG,
      HELP_FLAG
   };

public:
   CommandLineArgumentParser(std::vector<std::string> command_line_args)
      : command_line_args(command_line_args)
      , deducer(command_line_args)
   {}

   bool is_requesting_help()
   {
      return deducer.has_flag(HELP_FLAG.first);
   }

   std::string get_help()
   {
      std::stringstream result;

      result << "" << std::endl;
      result << "RAILS CLASS GENERATOR" << std::endl;
      result << "" << std::endl;
      result << "Description:" << std::endl;
      result << "Generates a Ruby class file with some pattern symatics." << std::endl;
      result << "" << std::endl;
      result << "Options:" << std::endl;
      for (auto &flag : flags)
      {
         std::string flag_flag = flag.first;
         result << "   " << pad(flag_flag, 9, ' ') << flag.second << std::endl;
      }
      result << "" << std::endl;
      result << "" << std::endl;

      return result.str();
   }

   std::string get_camel_case_name_arg()
   {
      std::vector<std::vector<std::string>> args = deducer.get_flagged_args(CLASS_NAME_FLAG.first);
      if (args.empty()) throw std::runtime_error("CommandLineArgumentParser required class name (-c) flag is missing");
      return args[0][0];
   }

   std::string get_interface_name_arg()
   {
      std::vector<std::vector<std::string>> args = deducer.get_flagged_args(INTERFACE_FLAG.first);
      if (args.empty()) return "";
      return args[0][0];
   }

   std::string get_folder_name_arg()
   {
      std::vector<std::vector<std::string>> args = deducer.get_flagged_args(FOLDER_FLAG.first);
      if (args.empty()) return "";
      return args[0][0];
   }

   std::string get_module_name_arg()
   {
      std::vector<std::vector<std::string>> args = deducer.get_flagged_args(MODULE_NAME_FLAG.first);
      if (args.empty()) return "";
      return args[0][0];
   }

   std::vector<std::vector<std::string>> get_attr_readers_and_named_args_arg()
   {
      return deducer.get_flagged_args(ATTR_READERS_AND_NAMED_ARGS_FLAG.first);
   }

   std::vector<std::vector<std::string>> get_methods_args()
   {
      return deducer.get_flagged_args(METHOD_FLAG.first);
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
      std::vector<std::string> first_named_arg = {};
      if (!named_args_args.empty()) first_named_arg = named_args_args[0];

      //std::vector<std::string> first_named_arg = {};

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

   CommandLineArgumentParser parser(args);

   if (parser.is_requesting_help())
   {
      std::cout << parser.get_help();
      return 0;
   }


   CommandLineArguemntToClassConverter converter(parser);
   Class klass = converter.get_class();

   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "SOURCE FILE:" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   ClassContentGenerator generator(klass);
   std::cout << generator.get_generated_content();

   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "TEST FILE:" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   ClassTestContentGenerator test_generator(klass);
   std::cout << test_generator.get_generated_content();

   return 0;
}
