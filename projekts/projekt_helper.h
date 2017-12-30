
#include <sstream>

Projekt *current_project = nullptr;

std::vector<Menu *> menus()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve menus on a nullptr current_project");
   std::vector<Menu *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("Menu")) results.push_back(static_cast<Menu *>(element));
   return results;
}

std::vector<Text *> texts()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve tests on a nullptr current_project");
   std::vector<Text *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("Text")) results.push_back(static_cast<Text *>(element));
   return results;
}

Menu &find_menu(std::string name)
{
   std::vector<Menu *> results;
   for (Menu *menu : menus()) if (menu->is_name(name)) return *menu;

   std::stringstream error_message;
   error_message << "Cannot find menu with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
}

Text &find_text(std::string name)
{
   std::vector<Text *> results;
   for (Text *text : texts()) if (text->is_name(name)) return *text;

   std::stringstream error_message;
   error_message << "Cannot find text with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
}

Menu &last_menu()
{
   return (*menus().back());
}

ElementBase &last_element()
{
   if (!current_project) throw std::runtime_error("Cannot last_element on a nullptr current_project");
   if (current_project->get_elements().empty()) throw std::runtime_error("Cannot retrieve last_element on an empty set of elements");
   return *current_project->get_elements().back();
}

const std::string MOVE_CURSOR_DOWN = "move_cursor_down";
const std::string MOVE_CURSOR_UP = "move_cursor_up";
const std::string CHOOSE_CURRENT_MENU_ITEM = "choose_current_menu_item";

void throwit(std::string message)
{
   throw std::runtime_error(message);
}


// file content reader

#include <fstream>
#include <streambuf>

std::string get_file_contents()
{
   std::ifstream t("out.tmp");
   std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
   return str;
}

// string tokenizer

std::vector<std::string> split_string(std::string s, std::string delimiter)
{
   std::vector<std::string> results;

   size_t pos = 0;
   std::string token;
   while ((pos = s.find(delimiter)) != std::string::npos) {
       token = s.substr(0, pos);
       results.push_back(token);
       s.erase(0, pos + delimiter.length());
   }
   results.push_back(s);

   return results;
}
