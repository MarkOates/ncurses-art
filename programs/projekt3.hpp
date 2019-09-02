/// #include "Projekt3.h"








/// #include <Projekt.h>


#include <ncurses_art/AppController.hpp>

#include <ncurses_art/Element/ElementBase.hpp>
#include <ncurses_art/Element/Frame.hpp>
#include <ncurses_art/Element/HeaderBar.hpp>
#include <ncurses_art/Element/Menu.hpp>
#include <ncurses_art/Element/Rectangle.hpp>
#include <ncurses_art/Element/Scene.hpp>
#include <ncurses_art/Element/Table.hpp>
#include <ncurses_art/Element/TabSet.hpp>
#include <ncurses_art/Element/Text.hpp>
#include <ncurses_art/Element/TextInput.hpp>
#include <ncurses_art/Element/WcharText.hpp>
#include <ncurses_art/EventTypes.hpp>

#define TMP_OUTFILE "/tmp/out.txt.tmp"

#include <ncurses.h>
#include <sstream>
#include <map>





std::vector<std::string> args;

class Projekt3 : public Scene
{
private:
   Projekt3 *current_project = nullptr;

public:
   Projekt3();
   ~Projekt3();

   std::map<char, std::string> mappings;
   std::map<std::string, void(*)()> events;

   virtual void initialize() = 0;

   void emit_event(std::string event);
   bool process_input(char input_ch) override;
   bool process_event(std::string event) override;

   std::vector<Table *> tables();
   std::vector<TabSet *> tab_sets();
   std::vector<Menu *> menus();
   std::vector<Text *> texts();
   std::vector<WcharText *> wchar_texts();
   std::vector<TextInput *> text_inputs();
   std::vector<Frame *> frames();
   TabSet &find_tab_set(std::string name);
   Table &find_table(std::string name);
   Menu &find_menu(std::string name);
   Text &find_text(std::string name);
   WcharText &find_wchar_text(std::string name);
   TextInput &find_text_input(std::string name);
   Frame &find_frame(std::string name);
   Menu &last_menu();
   ElementBase &last_element();
   Table &create_table(std::string name="", int x=0, int y=0, std::vector<std::vector<std::string>> elements={});
   Text &create_text(std::string name="", int x=0, int y=0, float align_x=0, float align_y=0);
   WcharText &create_wchar_text(std::string name="", int x=0, int y=0, float align_x=0);
   TextInput &create_text_input(std::string name="", int x=0, int y=0);
   Menu &create_menu(std::string name="", float x=0, float y=0);
   Frame &create_frame(std::string name="", int x=0, int y=0, int w=20, int h=6);
   HeaderBar &create_header_bar(std::string name="");
};

Projekt3::~Projekt3() {}



Projekt3::Projekt3()
{
   current_project = this;
   //mappings = {
      //{ 'q', EVENT_ABORT_PROGRAM },
   //};
   //events = {
      //{ EVENT_PROGRAM_INITIALIZED, initialize },
   //};


   //init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   //init_pair(3, COLOR_BLACK, 21);

   //create_text("text", 10, 20);
   //create_frame("frame", 20, 30, 80, 7).set_styles(COLOR_PAIR(3));

   //mappings['s'] = SET_TEXT;

   //events[SET_TEXT] = []{
      //find_text("text").set_text("Hello world!");
   //};
}




void Projekt3::emit_event(std::string event)
{
   if (!current_project)
   {
      std::stringstream ss;
      ss << "Cannot emit_event " << event << ", current_project is not set";
      throw std::runtime_error(ss.str());
   }
   current_project->emit_event(event);
};

bool Projekt3::process_input(char input_ch)
{
   if (mappings.find(input_ch) == mappings.end()) return false;
   emit_event(mappings[input_ch]);
   return true;
}

bool Projekt3::process_event(std::string e)
{
   if (events.find(e) == events.end()) return false;
   events[e]();
   return true;
}




/// #include "projekt_helper.h"

//#include <sstream>

//Projekt3 *current_project = nullptr;

std::vector<Table *> Projekt3::tables()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve tables on a nullptr current_project");
   std::vector<Table *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("Table")) results.push_back(static_cast<Table *>(element));
   return results;
}

std::vector<TabSet *> Projekt3::tab_sets()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve tab_sets on a nullptr current_project");
   std::vector<TabSet *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("TabSet")) results.push_back(static_cast<TabSet *>(element));
   return results;
}

std::vector<Menu *> Projekt3::menus()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve menus on a nullptr current_project");
   std::vector<Menu *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("Menu")) results.push_back(static_cast<Menu *>(element));
   return results;
}

std::vector<Text *> Projekt3::texts()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve texts on a nullptr current_project");
   std::vector<Text *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("Text")) results.push_back(static_cast<Text *>(element));
   return results;
}

std::vector<WcharText *> Projekt3::wchar_texts()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve wchar_texts on a nullptr current_project");
   std::vector<WcharText *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("WcharText")) results.push_back(static_cast<WcharText *>(element));
   return results;
}

std::vector<TextInput *> Projekt3::text_inputs()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve text_inputs on a nullptr current_project");
   std::vector<TextInput *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("TextInput")) results.push_back(static_cast<TextInput *>(element));
   return results;
}

std::vector<Frame *> Projekt3::frames()
{
   if (!current_project) throw std::runtime_error("Cannot retrieve frames on a nullptr current_project");
   std::vector<Frame *> results;
   for (ElementBase *element : current_project->get_elements())
      if (element->is_type("Frame")) results.push_back(static_cast<Frame *>(element));
   return results;
}

TabSet &Projekt3::find_tab_set(std::string name)
{
   std::vector<TabSet *> results;
   for (TabSet *tab_set : tab_sets()) if (tab_set->is_name(name)) return *tab_set;

   std::stringstream error_message;
   error_message << "Cannot find tab_set with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
}

Table &Projekt3::find_table(std::string name)
{
   std::vector<Table *> results;
   for (Table *table : tables()) if (table->is_name(name)) return *table;

   std::stringstream error_message;
   error_message << "Cannot find table with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
}

Menu &Projekt3::find_menu(std::string name)
{
   std::vector<Menu *> results;
   for (Menu *menu : menus()) if (menu->is_name(name)) return *menu;

   std::stringstream error_message;
   error_message << "Cannot find menu with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
}

Text &Projekt3::find_text(std::string name)
{
   std::vector<Text *> results;
   for (Text *text : texts()) if (text->is_name(name)) return *text;

   std::stringstream error_message;
   error_message << "Cannot find text with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
}

WcharText &Projekt3::find_wchar_text(std::string name)
{
   std::vector<WcharText *> results;
   for (WcharText *text : wchar_texts()) if (text->is_name(name)) return *text;

   std::stringstream error_message;
   error_message << "Cannot find wchar_text with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
}

TextInput &Projekt3::find_text_input(std::string name)
{
   std::vector<TextInput *> results;
   for (TextInput *text_input : text_inputs()) if (text_input->is_name(name)) return *text_input;

   std::stringstream error_message;
   error_message << "Cannot find text_input with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
}

Frame &Projekt3::find_frame(std::string name)
{
   std::vector<Frame *> results;
   for (Frame *frame : frames()) if (frame->is_name(name)) return *frame;

   std::stringstream error_message;
   error_message << "Cannot find frame with the name \"" << name << "\"";
   throw std::runtime_error(error_message.str());
}

Menu &Projekt3::last_menu()
{
   return (*menus().back());
}

ElementBase &Projekt3::last_element()
{
   if (!current_project) throw std::runtime_error("Cannot last_element on a nullptr current_project");
   if (current_project->get_elements().empty()) throw std::runtime_error("Cannot retrieve last_element on an empty set of elements");
   return *current_project->get_elements().back();
}

Table &Projekt3::create_table(std::string name, int x, int y, std::vector<std::vector<std::string>> elements)
{
   if (!current_project) throw std::runtime_error("Cannot create a table, current_project is not set");
   Table *table = new Table(x, y, elements);
   current_project->get_elements().push_back(table);
   last_element().set_name(name);
   return (*table);
}

Text &Projekt3::create_text(std::string name, int x, int y, float align_x, float align_y)
{
   if (!current_project) throw std::runtime_error("Cannot create a text, current_project is not set");
   Text *text = new Text("", x, y, align_x, align_y);
   current_project->get_elements().push_back(text);
   last_element().set_name(name);
   return (*text);
}

WcharText &Projekt3::create_wchar_text(std::string name, int x, int y, float align_x)
{
   if (!current_project) throw std::runtime_error("Cannot create a text, current_project is not set");
   WcharText *text = new WcharText(L"", x, y, align_x);
   current_project->get_elements().push_back(text);
   last_element().set_name(name);
   return (*text);
}

TextInput &Projekt3::create_text_input(std::string name, int x, int y)
{
   if (!current_project) throw std::runtime_error("Cannot create a text_input, current_project is not set");
   TextInput *text_input = new TextInput(x, y);
   current_project->get_elements().push_back(text_input);
   last_element().set_name(name);
   return (*text_input);
}

Menu &Projekt3::create_menu(std::string name, float x, float y)
{
   if (!current_project) throw std::runtime_error("Cannot create a menu, current_project is not set");
   Menu *menu = new Menu(x, y, {});
   current_project->get_elements().push_back(menu);
   last_element().set_name(name);
   return (*menu);
}

Frame &Projekt3::create_frame(std::string name, int x, int y, int w, int h)
{
   if (!current_project) throw std::runtime_error("Cannot create a menu, current_project is not set");
   Frame *frame = new Frame(x, y, w, h);
   current_project->get_elements().push_back(frame);
   last_element().set_name(name);
   return (*frame);
}

HeaderBar &Projekt3::create_header_bar(std::string name)
{
   if (!current_project) throw std::runtime_error("Cannot create a header_bar, current_project is not set");
   HeaderBar *header_bar = new HeaderBar();
   current_project->get_elements().push_back(header_bar);
   last_element().set_name(name);
   return (*header_bar);
}










//const std::string MOVE_CURSOR_DOWN = "move_cursor_down";
//const std::string MOVE_CURSOR_UP = "move_cursor_up";
//const std::string CHOOSE_CURRENT_MENU_ITEM = "choose_current_menu_item";


//// file content reader

//#include <fstream>
//#include <streambuf>

//std::string get_file_contents()
//{
   //std::ifstream t(TMP_OUTFILE);
   //std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
   //return str;
//}

//// string tokenizer

//std::vector<std::string> split_string(std::string s, std::string delimiter)
//{
   //std::vector<std::string> results;

   //size_t pos = 0;
   //std::string token;
   //while ((pos = s.find(delimiter)) != std::string::npos) {
       //token = s.substr(0, pos);
       //results.push_back(token);
       //s.erase(0, pos + delimiter.length());
   //}
   //results.push_back(s);

   //return results;
//}

//// append new line to text

//bool append_text(Text &text, std::string str_to_append)
//{
   //std::string str = text.get_text();
   //str += str_to_append;
   //text.set_text(str);
   //return true;
//}




//#define SET_TEXT "set_text"







//void initialize();



//Projekt3::Projekt3()
//{
   //current_project = this;
   //mappings = {
      //{ 'q', EVENT_ABORT_PROGRAM },
   //};
   //events = {
      //{ EVENT_PROGRAM_INITIALIZED, initialize },
   //};


   //init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   //init_pair(3, COLOR_BLACK, 21);

   //create_text("text", 10, 20);
   //create_frame("frame", 20, 30, 80, 7).set_styles(COLOR_PAIR(3));

   //mappings['s'] = SET_TEXT;

   //events[SET_TEXT] = []{
      //find_text("text").set_text("Hello world!");
   //};
//}

//std::map<char, std::string> Projekt3::mappings = {
   //{ 'q', EVENT_ABORT_PROGRAM },
//};

//void initialize();

//std::map<std::string, void(*)()> Projekt3::events = {
   //{ EVENT_PROGRAM_INITIALIZED, initialize },
//};

/// finished #include "Projekt2.h"




//Projekt3 projekt;




//void initialize()
//{
   //init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   //init_pair(3, COLOR_BLACK, 21);

   //projekt.create_text("text", 10, 20);
   //projekt.create_frame("frame", 20, 30, 80, 7).set_styles(COLOR_PAIR(3));

   //projekt.mappings['s'] = SET_TEXT;

   //projekt.events[SET_TEXT] = []{
      //projekt.find_text("text").set_text("Hello world!");
   //};
//}

