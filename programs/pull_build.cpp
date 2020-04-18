#include <iostream>
#include <allegro5/allegro.h>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <unistd.h>

int main(int argc, char **argv)
{
   if (argc != 2)
   {
      std::cout << "Usage: pull_build \"command to execute\"";
      return 1;
   }

   std::string command = argv[1];

   while(true)
   {
      Blast::ShellCommandExecutorWithCallback executor(command);
      executor.execute();
      std::cout << "==== Command finished ====" << std::endl;
      sleep(5);
   }
}
