

#include <HostnameExtractor.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/String/Trimmer.hpp>




HostnameExtractor::HostnameExtractor()
{
}


HostnameExtractor::~HostnameExtractor()
{
}


std::string HostnameExtractor::get_computer_name()
{
   Blast::ShellCommandExecutorWithCallback executor("hostname");
   std::string raw_shell_response = executor.execute();
   std::string result = Blast::String::Trimmer(raw_shell_response).trim();
   return result;
}


