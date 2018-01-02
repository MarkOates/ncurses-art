
#include <sstream>

Projekt *current_project = nullptr;

std::vector<TabSet *> tab_sets()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve tab_sets on a nullptr current_project");
   std::vector<TabSet *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("TabSet")) results.push_back(static_cast<TabSet *>(element));
   return results;
}

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

std::vector<Frame *> frames()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve tests on a nullptr current_project");
   std::vector<Frame *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("Frame")) results.push_back(static_cast<Frame *>(element));
   return results;
}

TabSet &find_tab_set(std::string name)
{
   std::vector<TabSet *> results;
   for (TabSet *tab_set : tab_sets()) if (tab_set->is_name(name)) return *tab_set;

   std::stringstream error_message;
   error_message << "Cannot find tab_set with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
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

Frame &find_frame(std::string name)
{
   std::vector<Frame *> results;
   for (Frame *frame : frames()) if (frame->is_name(name)) return *frame;

   std::stringstream error_message;
   error_message << "Cannot find frame with the name \"" << name << "\"";
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

Text &create_text(std::string name="", int x=0, int y=0, float align_x=0)
{
   if (!current_project) throw std::runtime_error("Cannot create a text, current_project is not set");
   Text *text = new Text("", x, y, align_x);
   current_project->get_elements().push_back(text);
   last_element().set_name(name);
   return (*text);
}

Menu &create_menu(std::string name="", float x=0, float y=0)
{
   if (!current_project) throw std::runtime_error("Cannot create a menu, current_project is not set");
   Menu *menu = new Menu(x, y, {});
   current_project->get_elements().push_back(menu);
   last_element().set_name(name);
   return (*menu);
}

Frame &create_frame(std::string name="", int x=0, int y=0, int w=20, int h=6)
{
   if (!current_project) throw std::runtime_error("Cannot create a menu, current_project is not set");
   Frame *frame = new Frame(x, y, w, h);
   current_project->get_elements().push_back(frame);
   last_element().set_name(name);
   return (*frame);
}

HeaderBar &create_header_bar(std::string name="")
{
   if (!current_project) throw std::runtime_error("Cannot create a header_bar, current_project is not set");
   HeaderBar *header_bar = new HeaderBar();
   current_project->get_elements().push_back(header_bar);
   last_element().set_name(name);
   return (*header_bar);
}

const std::string MOVE_CURSOR_DOWN = "move_cursor_down";
const std::string MOVE_CURSOR_UP = "move_cursor_up";
const std::string CHOOSE_CURRENT_MENU_ITEM = "choose_current_menu_item";

void throwit(std::string message)
{
   throw std::runtime_error(message);
}

void emit_event(std::string event)
{
   if (!current_project)
   {
      std::stringstream ss;
      ss << "Cannot emit_event " << event << ", current_project is not set";
      throw std::runtime_error(ss.str());
   }
   current_project->emit_event(event);
};

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

// append new line to text

bool append_text(Text &text, std::string str_to_append)
{
   std::string str = text.get_text();
   str += str_to_append;
   text.set_text(str);
   return true;
}

