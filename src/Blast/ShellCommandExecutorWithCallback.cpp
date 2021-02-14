

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <cstdio>
#include <string>
#include <array>
#include <memory>
#include <cstdio>
#include <cstdio>
#include <cstdio>
#include <cstdio>
#include <cstdio>
#include <stdexcept>


namespace Blast
{


ShellCommandExecutorWithCallback::ShellCommandExecutorWithCallback(std::string command, std::function<void(std::string)> callback)
   : command(command)
   , callback(callback)
{
}


ShellCommandExecutorWithCallback::~ShellCommandExecutorWithCallback()
{
}


void ShellCommandExecutorWithCallback::simple_silent_callback(std::string string_for_appending)
{
   return;
}

void ShellCommandExecutorWithCallback::simple_cout_callback(std::string string_for_appending)
{
   std::cout << string_for_appending;
}

std::string ShellCommandExecutorWithCallback::execute()
{
   static const int BUFFER_SIZE = 128;

   std::array<char, BUFFER_SIZE> buffer;
   std::string result;
   std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);

   if (!pipe) throw std::runtime_error("ShellCommandExecutor::execute(): Error: popen() failed.");

   while (!feof(pipe.get()))
      if (fgets(buffer.data(), BUFFER_SIZE, pipe.get()) != nullptr)
      {
         result += buffer.data();
         callback(buffer.data());
      }

   return result;
}
} // namespace Blast


