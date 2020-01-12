#include "Projekt2.h"

#include <GithubRepoStatusFetcher.hpp>
#include <ShellCommandExecutorWithCallback.hpp>
#include <StringSplitter.hpp>

#include <filesystem>
#include <iostream>
#include <utility>

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


auto command_callback = ShellCommandExecutorWithCallback::simple_silent_callback;



class TestResultInterface
{
public:
   TestResultInterface() {}
   virtual ~TestResultInterface() {}
   virtual bool assessment() = 0;
   virtual std::string message() = 0;
};



class TestResultEq : public TestResultInterface
{
public:
   std::string expected;
   std::string actual;

public:
   TestResultEq(std::string expected="foo", std::string actual="foo")
      : TestResultInterface()
      , expected(expected)
      , actual(actual)
   {}

   bool assessment() override
   {
      return expected == actual;
   }

   std::string message() override
   {
      std::string result;
      if (expected != actual)
      {
         std::stringstream msg;
         msg << "Test condition not met:" << std::endl
             << "  expected: " << expected << std::endl
             << "  actual: " << actual << std::endl
             ;
         result = msg.str();
      }
      else
      {
         result = "pass";
      }
      return result;
   }
};


#include <Hexagon/RegexMatcher.hpp>


class TestResultMatcher : public TestResultInterface
{
public:
   std::string expression;
   std::string actual;

public:
   TestResultMatcher(std::string expression=".*", std::string actual="foo")
      : TestResultInterface()
      , expression(expression)
      , actual(actual)
   {}

   bool assessment() override
   {
      return !RegexMatcher(actual, expression).get_match_info().empty();
   }

   std::string message() override
   {
      std::string result;
      if (!assessment())
      {
         std::stringstream msg;
         msg << "Test condition not met:" << std::endl
             << "  expression: " << expression << std::endl
             << "  actual: " << actual << std::endl
             ;
         result = msg.str();
      }
      else
      {
         result = "pass";
      }
      return result;
   }
};


TestResultInterface *last_test_result = nullptr;



std::time_t get_last_write_time(std::string filename)
{
   auto ftime = std::__fs::filesystem::last_write_time(filename);
   std::time_t last_write_time = decltype(ftime)::clock::to_time_t(ftime);

   return last_write_time;
}


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


bool compare_last_write_time(std::string file_a, std::string file_b)
{
   std::time_t source_last_write_time = get_last_write_time(file_a);
   std::time_t executable_last_write_time = get_last_write_time(file_b);

   //std::cout << "Source file write time is " << source_last_write_time << '\n';
   //std::cout << "Executable file write time is " << executable_last_write_time << '\n';
   //std::cout << "File write time is " << std::asctime(std::localtime(&last_write_time)) << '\n';

   return executable_last_write_time >= source_last_write_time;
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

   ShellCommandExecutorWithCallback executor(symlink_check_command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == success_message;
}


std::string get_head_sha_of_vim_plugin_first_vim_plugin()
{
   std::string command = "cd /Users/markoates/.vim/bundle/first_vim_plugin && git rev-parse HEAD";

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_head_sha_of_first_vim_plugin_repo()
{
   std::string command = "cd /Users/markoates/Repos/first_vim_plugin && git rev-parse HEAD";

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_ruby_version()
{
   std::string command = "ruby --version";

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_clang_version()
{
   std::string command = "clang --version";

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   std::string first_line = tokens.empty() ? "" : tokens[0];

   return first_line;
}


std::string get_brew_yaml_info_string()
{
   std::string command = "brew info yaml-cpp";

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   std::string first_line = tokens.empty() ? "" : tokens[0];

   return first_line;
}



std::string get_bundler_version()
{
   std::string command = "bundler --version";

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_rerun_version()
{
   std::string command = "rerun --version";

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_rails_version()
{
   std::string command = "rails --version";

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


bool check_beebot_response_ping()
{
   std::string command = "ruby /Users/markoates/Repos/beebot/lib/runner.rb ping";

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   for (auto &token : tokens)
   {
      if (token == "pong") return true;
   }

   return false;
}


bool check_hexagon_app_package_symlink_destination()
{
   std::string expected_destination = "/Users/markoates/Repos/hexagon/bin/Hexagon.app";
   std::string symlink_check_command = "readlink /Applications/Hexagon.app";

   ShellCommandExecutorWithCallback executor(symlink_check_command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == expected_destination;
}


bool run_ruby_version_test()
{
   std::string match_expression = "ruby 2\\.6\\.5p114 \\(2019-10-01 revision 67812\\).+";
   std::string actual_string = get_ruby_version();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool run_yaml_cpp_presence_test()
{
   std::string match_expression = "^yaml-cpp: ";
   std::string actual_string = get_brew_yaml_info_string();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool check_vim_plugins_are_in_sync_with_local_repos()
{
   std::string sha_from_plugin = get_head_sha_of_vim_plugin_first_vim_plugin();
   std::string sha_from_local_repo = get_head_sha_of_first_vim_plugin_repo();
   return sha_from_plugin == sha_from_local_repo;
}


bool celebrate_executable_presence_check()
{
   std::string expected_program_location = "/Users/markoates/Repos/ncurses-art/bin/programs/celebrate";
   std::string command = "command -v " + expected_program_location;

   ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == expected_program_location;
}


bool celebrate_is_up_to_date()
{
   std::string source_file_location = "/Users/markoates/Repos/ncurses-art/programs/celebrate.cpp";
   std::string executable_file_location = "/Users/markoates/Repos/ncurses-art/bin/programs/celebrate";
   return compare_last_write_time(source_file_location, executable_file_location);
}


bool all_executables_are_up_to_date_to_their_source()
{
   std::vector<std::tuple<bool, std::string, std::string>> source_executable_pairs = {
      { false, "/Users/markoates/Repos/ncurses-art/programs/celebrate.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/celebrate" },

      // blast files

      //component_generator.cpp
      //generator.cpp
      //quintessence_from_yaml.cpp
      //symlink_component_from_another_project.cpp

      // ncurses-art files

      //builder.cpp
      //builder2.cpp
      //project_filename_generator.cpp
      //system_test.cpp
      //component_generator.cpp
      //celebrate.cpp
      //create_release.cpp
      //fancy_branch.cpp
      //fancy_component.cpp
      //fancy_component_lister.cpp
      //fancy_find.cpp
      //fancy_list.cpp
      //fancy_log.cpp
      //fancy_stager.cpp
      //quiz.cpp
      //status_fetcher.cpp
   };

   bool all_are_up_to_date = true;
   for (auto &source_executable_pair : source_executable_pairs)
   {
      bool &is_up_to_date = std::get<0>(source_executable_pair);
      std::string &source_filename = std::get<1>(source_executable_pair);
      std::string &executable_filename = std::get<2>(source_executable_pair);

      is_up_to_date = compare_last_write_time(source_filename, executable_filename);

      if (!is_up_to_date) all_are_up_to_date = false;
   }

   return all_are_up_to_date;
}


bool check_clang_version_is_expected_version()
{
   std::string expected_version_string = "Apple clang version 11.0.0 (clang-1100.0.33.8)";
   last_test_result = new TestResultEq(expected_version_string, get_clang_version());
   return get_clang_version() == expected_version_string;
}



bool run_bundler_version_test()
{
   last_test_result = new TestResultMatcher("^Bundler version [0-9]+\\.[0-9]+\\.[0-9]+$).+", get_bundler_version());
   return last_test_result->assessment();
}



bool run_rerun_version_test()
{
   last_test_result = new TestResultMatcher("^[0-9]+\\.[0-9]+\\.[0-9]+$).+", get_rerun_version());
   return last_test_result->assessment();
}



bool run_rails_version_test()
{
   last_test_result = new TestResultMatcher("^Rails [0-9]+\\.[0-9]+\\.[0-9]+$).+", get_rails_version());
   return last_test_result->assessment();
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
   if (check) result << PROPERTY_DELIMITER << "✅ pass";
   else
   {
      result << PROPERTY_DELIMITER << "🔺 FAIL" << std::endl;
      if (last_test_result) result << last_test_result->message() << std::endl;
   }
   return result.str();
}

void initialize()
{
   events[INITIALIZE_SCENE] = []{
      create_text("output");

      tests = {
         { "yaml-cpp is installed through homebrew", run_yaml_cpp_presence_test },
         { "chruby is present", run_chruby_test },
         { "Ruby version is the expected version (otherwise \"sudo ruby-install ruby 2.6.5\", then \"sudo ruby-install --system ruby 2.6.5\")", run_ruby_version_test },
         { "rerun is present and installed (otherwise \"sudo gem install rerun\", after instaling ruby)", run_rerun_version_test },
         { "beebot is responsive", check_beebot_response_ping },
         { "bundler is present and installed (otherwise \"sudo gem install bundler:2.0.1\", after instaling ruby)", run_bundler_version_test },
         { "Rails is present and installed (otherwise \"sudo gem install rails\", after instaling ruby. Needed by inflector components in blast)", run_rails_version_test },
         //{ "terminal sessions are still open despite ./dotfile changes", just_a_failing_test },
         //{ "project binaries are up-to-date despite project file changes", just_a_failing_test },
         { "celebrate executable is present", celebrate_executable_presence_check },
         { "celebrate executable is up-to-date (executable been created at a time later than the last change to its source file)", celebrate_is_up_to_date },
         { "all custom executables are up-to-date to their source files", all_executables_are_up_to_date_to_their_source },
         //{ "terminal session has installed new ruby verions and chruby has been refreshed (with a terminal refresh)", just_a_failing_test },
         { "the hexagon app package is present in the hexagon repo", run_hexagon_app_package_test },
         { "the system's /Applications folder contains a symlink to the hexagon repo's app package", check_hexagon_app_package_alias_test },
         { "the /Applications/Hexagon.app symlink points to the expected hexagon app package", check_hexagon_app_package_symlink_destination },
         { "vim plugins have been updated (run \":PluginUpdate\" in vim) since version changes to first_vim_plugin", check_vim_plugins_are_in_sync_with_local_repos },
         { "clang version is the expected version (consider running \"brew install llvm\" to update to a more recent version)", check_clang_version_is_expected_version },
         //{ "generating a blast project adds ./.keep files for the necessary created directories", just_a_failing_test },
      };
   };
   events[REFRESH_STATUSES] = []{
      Text &text = find_text("output");

      std::stringstream result_text;

      for (auto &test : tests)
      {
         last_test_result = new TestResultEq();
         result_text << "running \"" << test.first << "\"" << std::endl;
         bool test_result = (*test.second)();
         result_text << "   " << check_it("status", test_result) << std::endl << std::endl;
      }
      
      text.set_text(result_text.str());
   };

   emit_event(INITIALIZE_SCENE);
   emit_event(REFRESH_STATUSES);
}

