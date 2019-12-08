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


bool check_vim_plugins_are_in_sync_with_local_repos()
{
   std::string sha_from_plugin = get_head_sha_of_vim_plugin_first_vim_plugin();
   std::string sha_from_local_repo = get_head_sha_of_first_vim_plugin_repo();
   return sha_from_plugin == sha_from_local_repo;
}


bool check_clang_version_is_expected_version()
{
   std::string expected_version_string = "Apple clang version 11.0.0 (clang-1100.0.33.8)";
   last_test_result = new TestResultEq(expected_version_string, get_clang_version());
   return get_clang_version() == expected_version_string;
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
         { "chruby is present", run_chruby_test },
         { "Ruby version is the expected version (otherwise \"sudo ruby-install ruby 2.6.5\")", run_ruby_version_test },
         { "rerun is present and installed (otherwise \"sudo gem install rerun\", after instaling ruby)", run_rerun_version_test },
         { "Rails is present and installed (otherwise \"sudo gem install rails\", after instaling ruby. Needed by inflector components in blast)", run_rails_version_test },
         { "terminal sessions are still open despite ./dotfile changes", just_a_failing_test },
         { "project binaries are up-to-date despite project file changes", just_a_failing_test },
         { "terminal session has installed new ruby verions and chruby has been refreshed (with a terminal refresh)", just_a_failing_test },
         { "the hexagon app package is present in the hexagon repo", run_hexagon_app_package_test },
         { "the system's /Applications folder contains a symlink to the hexagon repo's app package", check_hexagon_app_package_alias_test },
         { "the /Applications/Hexagon.app symlink points to the expected hexagon app package", check_hexagon_app_package_symlink_destination },
         { "vim plugins have been updated (run \":PluginUpdate\" in vim) since version changes to first_vim_plugin", check_vim_plugins_are_in_sync_with_local_repos },
         { "clang version is the expected version", check_clang_version_is_expected_version },
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

