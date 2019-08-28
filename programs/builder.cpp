#include "Projekt2.h"
#include <iostream>
#include <thread>



std::string find_project_basenames_command = std::string("find ./src/* | sed 's/\\.\\/src\\///g' | sed 's/\\.cpp$//g' > ") + TMP_OUTFILE;


class ObjectSrcComponents
{
private:
   std::string basename;
   std::string project_name;

public:
   ObjectSrcComponents(std::string basename, std::string project_name)
      : basename(basename)
      , project_name(project_name)
   {}
   std::string get_source_filename() { return std::string("src/") + basename + ".cpp"; }
   std::string get_include_filename() { return std::string("include/") + project_name + "/" + basename + ".cpp"; }
   std::string get_test_src_filename() { return std::string("tests/") + basename + "Test"; }
   std::string get_example_src_filename() { return std::string("examples/") + basename + "Example.cpp"; }

   std::string get_obj_binary() { return std::string("obj/") + basename + ".o"; }
   std::string get_test_binary() { return std::string("bin/tests/") + basename + "Test"; }
   std::string get_example_binary() { return std::string("bin/examples/") + basename + "Example"; }

   std::string get_obj_compile_notifier_str()
   {
      std::stringstream str;
      str << basename << "_OBJECT_COMPILE";
      return str.str();
   }
   std::string get_test_compile_notifier_str()
   {
      std::stringstream str;
      str << basename << "_TEST_COMPILE";
      return str.str();
   }
   std::string get_test_run_notifier_str()
   {
      std::stringstream str;
      str << basename << "_TEST_RUN";
      return str.str();
   }
   std::string get_example_compile_notifier_str()
   {
      std::stringstream str;
      str << basename << "_EXAMPLE_COMPILE";
      return str.str();
   }

   Text &get_obj_compile_notifier() {
      return find_text(get_obj_compile_notifier_str());
   }
   Text &get_test_compile_notifier() {
      return find_text(get_test_compile_notifier_str());
   }
   Text &get_test_run_notifier() {
      return find_text(get_test_run_notifier_str());
   }
   Text &get_example_compile_notifier() {
      return find_text(get_example_compile_notifier_str());
   }
};


#define MOVE_MENU_ITEM_DOWN "move_menu_item_down"
#define MOVE_MENU_ITEM_UP "move_menu_item_up"
#define COMPILE_OBJECT "COMPILE_OBJECT"
#define COMPILE_TEST "COMPILE_TEST"
#define COMPILE_EXAMPLE "COMPILE_EXAMPLE"
#define RUN_TEST "RUN_TEST"


enum color_names
{
   COLOR_PROCESSING = 32,
   COLOR_SUCCESS,
   COLOR_FAILURE,
};


int compile_obj_thread(std::string object_basename)
{
   ObjectSrcComponents object_src_components(object_basename, "Blast");
   std::stringstream system_command;
   system_command << "make " << object_src_components.get_obj_binary() << " > foobar.txt";
   int return_status = system(system_command.str().c_str());
   Text &t = object_src_components.get_obj_compile_notifier();
   if (return_status == 0) t.color(COLOR_SUCCESS).set_text("[*]");
   else t.color(COLOR_FAILURE).set_text("[x]");

   return 0;
}


int compile_test_thread(std::string object_basename)
{
   ObjectSrcComponents object_src_components(object_basename, "Blast");
   std::stringstream system_command;
   system_command << "make " << object_src_components.get_test_binary() << " > foobar.txt";
   int return_status = system(system_command.str().c_str());
   Text &t = object_src_components.get_test_compile_notifier();
   if (return_status == 0) t.color(COLOR_SUCCESS).set_text("[*]");
   else t.color(COLOR_FAILURE).set_text("[x]");

   return 0;
}


int run_test_thread(std::string object_basename)
{
   ObjectSrcComponents object_src_components(object_basename, "Blast");
   std::stringstream system_command;
   system_command << object_src_components.get_test_binary() << " > foobar.txt";
   int return_status = system(system_command.str().c_str());
   Text &t = object_src_components.get_test_run_notifier();
   if (return_status == 0) t.color(COLOR_SUCCESS).set_text("[*]");
   else t.color(COLOR_FAILURE).set_text("[x]");

   return 0;
}


int example_compile_thread(std::string object_basename)
{
   ObjectSrcComponents object_src_components(object_basename, "Blast");
   std::stringstream system_command;
   system_command << "make " << object_src_components.get_example_binary() << " > foobar.txt";
   int return_status = system(system_command.str().c_str());
   Text &t = object_src_components.get_example_compile_notifier();
   if (return_status == 0) t.color(COLOR_SUCCESS).set_text("[*]");
   else t.color(COLOR_FAILURE).set_text("[x]");

   return 0;
}


void initialize()
{
   init_color(20, (int)(224.0/255.0*1000), (int)(216.0/255.0*1000), (int)(32.0/255.0*1000));
   init_color(21, 0, (int)(255.0/255.0*1000), (int)(175.0/255.0*1000));// successful green
   init_color(22, (int)(196.0/255.0*1000), (int)(32.0/255.0*1000), (int)(64.0/255.0*1000));
   init_pair(COLOR_PROCESSING, 20, COLOR_BLACK);
   init_pair(COLOR_SUCCESS, 21, COLOR_BLACK);
   init_pair(COLOR_FAILURE, 22, COLOR_BLACK);

   std::vector<std::string> object_basenames;
   system(find_project_basenames_command.c_str());
   std::string txt = get_file_contents();
   object_basenames = split_string(txt, "\n");

   int menu_y = 2;
   create_menu("objects", 10, menu_y).set_options(object_basenames);

   int i=0;
   for (auto &object_basename : object_basenames)
   {
      int column_offset = 40;
      int column_width = 20;
      ObjectSrcComponents object_src_components(object_basename, "Blast");
      create_text(object_src_components.get_obj_compile_notifier_str(), column_offset+column_width*0, menu_y+i).set_text("[object compile]");
      create_text(object_src_components.get_test_compile_notifier_str(), column_offset+column_width*1, menu_y+i).set_text("[test compile]");
      create_text(object_src_components.get_test_run_notifier_str(), column_offset+column_width*2, menu_y+i).set_text("[test passes]");
      create_text(object_src_components.get_example_compile_notifier_str(), column_offset+column_width*3, menu_y+i).set_text("[example compiles]");
      i++;
   }

   mappings['j'] = MOVE_MENU_ITEM_DOWN;
   mappings['k'] = MOVE_MENU_ITEM_UP;
   mappings['c'] = COMPILE_OBJECT;
   mappings['t'] = COMPILE_TEST;
   mappings['r'] = RUN_TEST;
   mappings['e'] = COMPILE_EXAMPLE;

   events[EVENT_PROGRAM_INITIALIZED] = []{
   };
   events[MOVE_MENU_ITEM_UP] = []{
      find_menu("objects").move_cursor_up();
   };
   events[MOVE_MENU_ITEM_DOWN] = []{
      find_menu("objects").move_cursor_down();
   };
   events[COMPILE_OBJECT] = []{
      std::string object_basename = find_menu("objects").current_selection();
      ObjectSrcComponents object_src_components(object_basename, "Blast");
      Text &t = object_src_components.get_obj_compile_notifier();
      t.color(COLOR_PROCESSING).set_text("[_]");

      std::thread(compile_obj_thread, object_basename).detach();
   };
   events[COMPILE_TEST] = []{
      std::string object_basename = find_menu("objects").current_selection();
      ObjectSrcComponents object_src_components(object_basename, "Blast");
      Text &t = object_src_components.get_test_compile_notifier();
      t.color(COLOR_PROCESSING).set_text("[_]");

      std::thread(compile_test_thread, object_basename).detach();
   };
   events[RUN_TEST] = []{
      std::string object_basename = find_menu("objects").current_selection();
      ObjectSrcComponents object_src_components(object_basename, "Blast");
      Text &t = object_src_components.get_test_run_notifier();
      t.color(COLOR_PROCESSING).set_text("[_]");

      std::thread(run_test_thread, object_basename).detach();
   };
   events[COMPILE_EXAMPLE] = []{
      std::string object_basename = find_menu("objects").current_selection();
      ObjectSrcComponents object_src_components(object_basename, "Blast");
      Text &t = object_src_components.get_example_compile_notifier();
      t.color(COLOR_PROCESSING).set_text("[_]");

      std::thread(example_compile_thread, object_basename).detach();
   };
}


