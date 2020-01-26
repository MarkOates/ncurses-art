#include <Projekt.h>
#include "projekt_helper.h"

#include <ncurses.h>

#include <iterator> // for std::ostream_iterator

#define TEST_APPEND_TEXT "test_append_text"
#define TEST_SPLIT_STRING "test_split_string"
#define MESSAGE_STARTING_TEST "message_starting_test"
#define MESSAGE_FINISHED_TEST "message_finished_test"
#define MESSAGE_FAILED_TEST "message_failed_test"

Text *output_text = nullptr;

std::string vector_to_string(std::vector<std::string> vec)
{
   std::ostringstream oss;
   oss << "[ \"";
   std::copy(vec.begin(), vec.end()-1,
         std::ostream_iterator<std::string>(oss, "\", \""));
   oss << vec.back() << "\" ]";
   return oss.str();
}

std::string compose_failed_assertion(std::string test_name, std::string expected, std::string actual)
{
   std::stringstream ss;
   ss << "Test \"" << test_name << "\" failed." << std::endl;
   ss << " - Expected: " << expected << std::endl;
   ss << " -   Actual: " << actual << std::endl;
   return ss.str();
}

std::string compose_failed_assertion(std::string test_name, std::vector<std::string> expected, std::vector<std::string> actual)
{
   std::stringstream ss;
   ss << "Test \"" << test_name << "\" failed." << std::endl;
   ss << " - Expected: " << vector_to_string(expected) << std::endl;
   ss << " -   Actual: " << vector_to_string(actual) << std::endl;
   return ss.str();
}

bool my_assert(Projekt *projekt, std::string name, std::vector<std::string> expected, std::vector<std::string> actual)
{
   if (expected != actual)
   {
      append_text(find_text("output_text"), compose_failed_assertion(name, expected, actual));
      projekt->emit_event(MESSAGE_FAILED_TEST);
   }
   return true;
}

bool my_assert(Projekt *projekt, std::string name, std::string expected, std::string actual)
{
   if (expected != actual)
   {
      append_text(find_text("output_text"), compose_failed_assertion(name, expected, actual));
      projekt->emit_event(MESSAGE_FAILED_TEST);
   }
   return true;
}

Projekt::Projekt() { current_project = this; }
bool Projekt::process_input(char ch)
{
   switch(ch)
   {
   case 'q': emit_event(EVENT_ABORT_PROGRAM); break;
   }
   return true;
}
bool Projekt::process_event(std::string e)
{
   if (e == EVENT_PROGRAM_INITIALIZED)
   {
      init_color(20, 0, (int)(255.0/255.0*1000), (int)(96.0/255.0*1000));
      init_pair(1, 20, COLOR_BLACK);
      output_text = &create_text("output_text", 0, 5);

      emit_event(TEST_APPEND_TEXT);
      emit_event(TEST_SPLIT_STRING);
   }
   else if (e == MESSAGE_STARTING_TEST)
   {
      append_text(find_text("output_text"), "\n-- Test starting");
   }
   else if (e == MESSAGE_FINISHED_TEST)
   {
      append_text(find_text("output_text"), "\n   -- Test finished");
   }
   else if (e == MESSAGE_FAILED_TEST)
   {
      append_text(find_text("output_text"), "\n   !! FAILED");
   }
   else if (e == TEST_APPEND_TEXT)
   {
      emit_event(MESSAGE_STARTING_TEST);
      std::string initial_text = "initial text";
      Text text(initial_text, 0, 0);
      std::string appending_text = "foo";
      append_text(text, appending_text);
      std::string expected_text = "initial textfoo";
      std::string returned_text = text.get_text();

      my_assert(this, TEST_APPEND_TEXT, expected_text, returned_text);

      emit_event(MESSAGE_FINISHED_TEST);
   }
   else if (e == TEST_SPLIT_STRING)
   {
      emit_event(MESSAGE_STARTING_TEST);
      std::string str = "This is a string";
      std::vector<std::string> actual = split_string(str, " ");
      std::vector<std::string> expected = {"This", "is", "a", "string"};

      my_assert(this, TEST_SPLIT_STRING, expected, actual);

      emit_event(MESSAGE_FINISHED_TEST);
   }
   return true;
}
