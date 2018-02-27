#include "Projekt2.h"
#include <iostream>
#include <thread>



std::string find_project_basenames_command = std::string("find ./src/* | sed 's/\\.\\/src\\///g' | sed 's/\\.cpp$//g' > ") + TMP_OUTFILE;


#define COMPILE_DEPENDENCIES_COLUMN 1
#define COMPILE_OBJECT_COLUMN 2
#define COMPILE_TEST_COLUMN 3
#define RUN_TEST_COLUMN 4
#define COMPILE_EXAMPLE_COLUMN 5
#define RUN_EXAMPLE_COLUMN 6

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
};


#define MOVE_MENU_ITEM_UP "move_menu_item_up"
#define MOVE_MENU_ITEM_DOWN "move_menu_item_down"
#define MOVE_MENU_ITEM_LEFT "move_menu_item_left"
#define MOVE_MENU_ITEM_RIGHT "move_menu_item_right"
#define MAKE_CLEAN "make_clean"
#define COMPILE_DEPENDENCIES "COMPILE_DEPENDENCIES"
#define COMPILE_OBJECT "COMPILE_OBJECT"
#define COMPILE_TEST "COMPILE_TEST"
#define COMPILE_EXAMPLE "COMPILE_EXAMPLE"
#define COMPILE_SELECTED_COLUMN "COMPILE_SELECTED_COLUMN"
#define RUN_EXAMPLE "RUN_EXAMPLE"
#define RUN_TEST "RUN_TEST"


int get_row_for_basename(std::string basename)
{
   Table &t = find_table("table");
   int row = 0;
   for (auto &rows : t.get_elements())
   {
      if (rows[0] == basename) return row;
      row++;
   }

   std::stringstream error_message;
   error_message << "get_row_for_basename error: could not find row number for basename " << basename;
   throw std::runtime_error(error_message.str());

   return -1;
}

std::string get_row_basename(int row)
{
   Table &t = find_table("table");
   if (row < 0) throw std::runtime_error("[get_row_basename error]: row can not be less than 0");
   if (row >= t.get_num_rows()) throw std::runtime_error("[get_row_basename error]: row can not be greater than the number of rows");

   return t.get_elements()[row][0];
}


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
   Table &table = find_table("table");
   int row = get_row_for_basename(object_basename);
   int column = COMPILE_OBJECT_COLUMN;

   if (return_status == 0)
   {
      table.set_element(column, row, "[*]");
   }
   else
   {
      table.set_element(column, row, "[x]");
   }

   return 0;
}


int compile_test_thread(std::string object_basename)
{
   ObjectSrcComponents object_src_components(object_basename, "Blast");
   std::stringstream system_command;
   system_command << "make " << object_src_components.get_test_binary() << " > foobar.txt";
   int return_status = system(system_command.str().c_str());
   Table &table = find_table("table");
   int row = get_row_for_basename(object_basename);
   int column = COMPILE_TEST_COLUMN;

   if (return_status == 0)
   {
      table.set_element(column, row, "[*]");
   }
   else
   {
      table.set_element(column, row, "[x]");
   }

   return 0;
}


int run_test_thread(std::string object_basename)
{
   ObjectSrcComponents object_src_components(object_basename, "Blast");
   std::stringstream system_command;
   system_command << object_src_components.get_test_binary() << " > foobar.txt";
   int return_status = system(system_command.str().c_str());
   Table &table = find_table("table");
   int row = get_row_for_basename(object_basename);
   int column = RUN_TEST_COLUMN;

   if (return_status == 0)
   {
      table.set_element(column, row, "[*]");
   }
   else
   {
      table.set_element(column, row, "[x]");
   }

   return 0;
}


int example_compile_thread(std::string object_basename)
{
   ObjectSrcComponents object_src_components(object_basename, "Blast");
   std::stringstream system_command;
   system_command << "make " << object_src_components.get_example_binary() << " > foobar.txt";
   int return_status = system(system_command.str().c_str());
   Table &table = find_table("table");
   int row = get_row_for_basename(object_basename);
   int column = COMPILE_EXAMPLE_COLUMN;

   if (return_status == 0)
   {
      table.set_element(column, row, "[*]");
   }
   else
   {
      table.set_element(column, row, "[x]");
   }

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

   std::vector<std::vector<std::string>> elements;
   create_table("table", 10, 5);

   int i=0;
   for (auto &object_basename : object_basenames)
   {
      ObjectSrcComponents object_src_components(object_basename, "Blast");
      std::vector<std::string> element = {
         object_basename,
         "[deps compiled]",
         "[obj compile]",
         "[test compile]",
         "[test pass]",
         "[example compile]",
         "[run example]",
         };
      elements.push_back(element);
      i++;
   }

   find_table("table").set_elements(elements);

   mappings['k'] = MOVE_MENU_ITEM_UP;
   mappings['j'] = MOVE_MENU_ITEM_DOWN;
   mappings['h'] = MOVE_MENU_ITEM_LEFT;
   mappings['l'] = MOVE_MENU_ITEM_RIGHT;
   mappings['c'] = MAKE_CLEAN;
   mappings['\n'] = COMPILE_SELECTED_COLUMN;

   events[EVENT_PROGRAM_INITIALIZED] = []{
   };
   events[MOVE_MENU_ITEM_UP] = []{
      find_table("table").move_cursor_up();
   };
   events[MOVE_MENU_ITEM_DOWN] = []{
      find_table("table").move_cursor_down();
   };
   events[MOVE_MENU_ITEM_LEFT] = []{
      find_table("table").move_cursor_left();
   };
   events[MOVE_MENU_ITEM_RIGHT] = []{
      find_table("table").move_cursor_right();
   };
   events[MAKE_CLEAN] = []{
      std::stringstream system_command;
      system_command << "make clean > foobar.txt";
      system(system_command.str().c_str());
   };
   events[COMPILE_OBJECT] = []{
      Table &table = find_table("table");
      std::string object_basename = get_row_basename(table.get_cursor_pos_y());

      ObjectSrcComponents object_src_components(object_basename, "Blast");

      int row = get_row_for_basename(object_basename);
      int column = COMPILE_OBJECT_COLUMN;
      table.set_element(column, row, "[_]");

      std::thread(compile_obj_thread, object_basename).detach();
   };
   events[COMPILE_TEST] = []{
      Table &table = find_table("table");
      std::string object_basename = get_row_basename(table.get_cursor_pos_y());

      ObjectSrcComponents object_src_components(object_basename, "Blast");

      int row = get_row_for_basename(object_basename);
      int column = COMPILE_TEST_COLUMN;
      table.set_element(column, row, "[_]");

      std::thread(compile_test_thread, object_basename).detach();
   };
   events[RUN_TEST] = []{
      Table &table = find_table("table");
      std::string object_basename = get_row_basename(table.get_cursor_pos_y());

      ObjectSrcComponents object_src_components(object_basename, "Blast");

      int row = get_row_for_basename(object_basename);
      int column = RUN_TEST_COLUMN;
      table.set_element(column, row, "[_]");

      std::thread(run_test_thread, object_basename).detach();
   };
   events[COMPILE_EXAMPLE] = []{
      Table &table = find_table("table");
      std::string object_basename = get_row_basename(table.get_cursor_pos_y());

      ObjectSrcComponents object_src_components(object_basename, "Blast");

      int row = get_row_for_basename(object_basename);
      int column = COMPILE_EXAMPLE_COLUMN;
      table.set_element(column, row, "[_]");

      std::thread(example_compile_thread, object_basename).detach();
   };
   events[RUN_EXAMPLE] = []{
      Table &table = find_table("table");
      std::string object_basename = get_row_basename(table.get_cursor_pos_y());

      ObjectSrcComponents object_src_components(object_basename, "Blast");

      int row = get_row_for_basename(object_basename);
      int column = RUN_EXAMPLE_COLUMN;
      table.set_element(column, row, "[_]");

      std::stringstream command;
      command << object_src_components.get_example_binary();

      def_prog_mode(); endwin();
      system(command.str().c_str());
      refresh();
   };
   events[COMPILE_SELECTED_COLUMN] = []{
      Table &table = find_table("table");
      std::string object_basename = get_row_basename(table.get_cursor_pos_y());

      std::string leftmost_column_value = table.get_element_at(0, table.get_cursor_pos_y());

      switch (table.get_cursor_pos_x())
      {
      case 0: break; // column 0 is the object_basename
      case COMPILE_DEPENDENCIES_COLUMN: emit_event(COMPILE_DEPENDENCIES); break;
      case COMPILE_OBJECT_COLUMN:       emit_event(COMPILE_OBJECT); break;
      case COMPILE_TEST_COLUMN:         emit_event(COMPILE_TEST); break;
      case RUN_TEST_COLUMN:             emit_event(RUN_TEST); break;
      case COMPILE_EXAMPLE_COLUMN:      emit_event(COMPILE_EXAMPLE); break;
      case RUN_EXAMPLE_COLUMN:          emit_event(RUN_EXAMPLE); break;
      default:
         {
            std::stringstream error_message;
            error_message << "unknown column " << table.get_cursor_pos_x();
            throw std::runtime_error(error_message.str());
         }
         break;
      }
   };
}


