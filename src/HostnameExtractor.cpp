

#include <HostnameExtractor.hpp>
#include <ShellCommandExecutorWithCallback.hpp>
#include <StringTrimmer.hpp>




HostnameExtractor::HostnameExtractor()
{
}


HostnameExtractor::~HostnameExtractor()
{
}


std::string HostnameExtractor::get_computer_name()
{
ShellCommandExecutorWithCallback executor("hostname");
std::string raw_shell_response = executor.execute();
std::string result = StringTrimmer(raw_shell_response).trim();
return result;

}


