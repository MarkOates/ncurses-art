#include "Projekt2.h"

#include <GithubRepoStatusFetcher.hpp>
#include <ShellCommandExecutorWithCallback.hpp>
#include <StringSplitter.hpp>

#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE_SCENE "INITIALIZE_SCENE"
#define REFRESH_STATUSES "REFRESH_STATUSES"


enum test_status
{
   UNRUN = 0,
   QUEUED,
   STARTED,
   FAILED,
   PASSED,
   ERROR_DURING_RUNNING,
};

#define PROPERTY_DELIMITER ": "

std::map<std::string, bool (*)()> tests = {};



std::string file_get_contents(std::string filename, bool raise_on_missing_file=true)
{
   std::ifstream file(filename.c_str());
   std::string input = "";
   if (!file)
   {
      if (raise_on_missing_file)
      {
         std::stringstream error_message;
         error_message << "Attempting to open file \"" << filename << "\" but it was not found." << std::endl;
         throw std::runtime_error(error_message.str());
      }
      else
      {
         return "";
      }
   }
   char ch;
   while (file.get(ch)) input.append(1, ch);
   if (!file.eof()) return ""; // strange error
   file.close();
   return input;
}

bool run_chruby_test()
{
   std::string expected_line = "source /usr/local/opt/chruby/share/chruby/chruby.sh";
   std::string zsh_filename = "/Users/markoates/Repos/.dotfiles/.zshrc";
   std::string file_contents = file_get_contents(zsh_filename);
   StringSplitter string_splitter(file_contents, '\n');
   std::vector<std::string> file_lines = string_splitter.split();

   bool found = false;
   for (auto &file_line : file_lines)
   {
      if (file_line == expected_line) found = true;
   }

   return found;
}

bool run_hexagon_app_package_test()
{
   std::string EXPECTED_HEXAGON_APP_PACKAGE_INFO_PLIST_FILENAME = "/Users/markoates/Repos/hexagon/bin/Hexagon.app/Contents/Info.plist";
   std::string content = file_get_contents(EXPECTED_HEXAGON_APP_PACKAGE_INFO_PLIST_FILENAME, true);
   return !content.empty();
}


std::string trim(const std::string& str,
                 const std::string& whitespace = " \t\n\r")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}


bool check_hexagon_app_package_alias_test()
{
   std::string success_message = "symlink exists";
   std::string symlink_check_command = std::string("if [ -L \"/Applications/Hexagon.app\" ]; then echo \"") + success_message + "\"; else echo \"symlink does not exist\"; fi";
   std::string COMMAND_TO_CREATE_SYMLINK = "ln -s /Users/markoates/Repos/hexagon/bin/Hexagon.app /Applications/Hexagon.app";

   ShellCommandExecutorWithCallback executor(symlink_check_command);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == success_message;
}


std::string get_head_sha_of_vim_plugin_first_vim_plugin()
{
   std::string command = "cd /Users/markoates/.vim/bundle/first_vim_plugin && git rev-parse HEAD";

   ShellCommandExecutorWithCallback executor(command);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_head_sha_of_first_vim_plugin_repo()
{
   std::string command = "cd /Users/markoates/Repos/first_vim_plugin && git rev-parse HEAD";

   ShellCommandExecutorWithCallback executor(command);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


bool check_hexagon_app_package_symlink_destination()
{
   std::string expected_destination = "/Users/markoates/Repos/hexagon/bin/Hexagon.app";
   std::string symlink_check_command = "readlink /Applications/Hexagon.app";

   ShellCommandExecutorWithCallback executor(symlink_check_command);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == expected_destination;
}


bool check_vim_plugins_are_in_sync_with_local_repos()
{
   std::string sha_from_plugin = get_head_sha_of_vim_plugin_first_vim_plugin();
   std::string sha_from_local_repo = get_head_sha_of_first_vim_plugin_repo();
   return sha_from_plugin == sha_from_local_repo;
}



bool just_a_failing_test()
{
   return false;
}


std::string diamond_it(std::string label, int number)
{
   std::stringstream result;
   bool check = number == 1;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "🔹 ";
   else result << PROPERTY_DELIMITER << "🔸 ";
   result << number;

   return result.str();
}

std::string check_it(std::string label, bool check)
{
   std::stringstream result;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "✓ yes";
   else result << PROPERTY_DELIMITER << "✗ no";
   return result.str();
}

void initialize()
{
   events[INITIALIZE_SCENE] = []{
      create_text("output");

      tests = {
         { "chruby is present", run_chruby_test },
         { "terminal sessions are still open despite ./dotfile changes", just_a_failing_test },
         { "project binaries are up-to-date despite project file changes", just_a_failing_test },
         { "the hexagon app package is present in the hexagon repo", run_hexagon_app_package_test },
         { "the system's /Applications folder contains a symlink to the hexagon repo's app package", check_hexagon_app_package_alias_test },
         { "the /Applications/Hexagon.app symlink points to the expected hexagon app package", check_hexagon_app_package_symlink_destination },
         { "vim plugins have been updated (run \":PluginUpdate\" in vim) since version changes to first_vim_plugin", check_vim_plugins_are_in_sync_with_local_repos },
      };
   };
   events[REFRESH_STATUSES] = []{
      Text &text = find_text("output");

      std::stringstream result_text;

      for (auto &test : tests)
      {
         result_text << "running \"" << test.first << "\"" << std::endl;
         bool test_result = (*test.second)();
         result_text << "   " << check_it("status", test_result) << std::endl;
      }
      
      text.set_text(result_text.str());
   };

   emit_event(INITIALIZE_SCENE);
   emit_event(REFRESH_STATUSES);
}

