#include <sstream>
#include <string>
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
      , std::string interface_name
      , std::string folder_name
      , std::vector<NamedArg> attr_readers_and_named_args
      , std::vector<Method> methods
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
   return 0;
}

