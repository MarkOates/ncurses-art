#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>



class ConsoleOutputter
{
public:
   ConsoleOutputter() {}
   ~ConsoleOutputter() {}
   void output_line(std::string message)
   {
      std::cout << message << std::endl;
   }
};



std::string const PROGRAM_RUNNER_FILE_CONTENT = R"END(
parent_classes: []
properties: []
namespaces: []
functions:
  - name: run
    type: void
    parameters: []
    body: |
      std::cout << "Hello World!" << std::endl;
function_body_symbol_dependencies: [ 'std::cout', 'std::endl' ]
dependencies:
  - symbol: std::cout
    headers: [ 'iostream' ]
    include_directories: []
    linked_libraries: []
  - symbol: std::endl
    headers: [ 'iostream' ]
    include_directories: []
    linked_libraries: []
  - symbol: void
    headers: []
    include_directories: []
    linked_libraries: []
)END";



std::string const GITIGNORE_FILE_CONTENT = R"END(
bin/*
!bin/data/*
.DS_Store
obj/*
.DS_Store
)END";



std::string PROGRAM_RUNNER_CLASS_NAME = "ProgramRunner";
std::string main_file_content_template = R"END(
#include <[[PROGRAM_RUNNER_CLASS_NAME]].hpp>

int main(int argc, char **argv)
{
   [[PROGRAM_RUNNER_CLASS_NAME]]().run();
   return 0;
}
)END";


std::string makefile_template = R"END(
LIBS_ROOT=/Users/markoates/Repos
ALLEGRO_INCLUDE_DIR=$(LIBS_ROOT)/allegro5/build/include
ALLEGRO_LIB_DIR=$(LIBS_ROOT)/allegro5/build/lib
GOOGLE_TEST_DIR=$(LIBS_ROOT)/googletest
GOOGLE_TEST_LIB_DIR=$(GOOGLE_TEST_DIR)/build/googlemock/gtest
GOOGLE_TEST_INCLUDE_DIR=$(GOOGLE_TEST_DIR)/googletest/include



# this is the directory of the project (it's auto_generated)
PROJECT_BINARY_NAME=[[PROJECT_NAME]]



GOOGLE_TEST_LIBS=gtest
ALLEGRO_LIBS=allegro_color allegro_font allegro_ttf allegro_dialog allegro_audio allegro_acodec allegro_primitives allegro_image allegro
ALLEGRO_LIBS_MAIN=$(ALLEGRO_LIBS) allegro_main



.PHONY: all clean main fresh



SOURCES := $(shell find src -name '*.cpp')
PROGRAM_SOURCES := $(shell find programs -name '*.cpp')
EXAMPLE_SOURCES := $(shell find examples -name '*.cpp')
TEST_SOURCES := $(shell find tests -name '*Test.cpp')
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)
PROGRAMS := $(PROGRAM_SOURCES:programs/%.cpp=bin/programs/%)
EXAMPLES := $(EXAMPLE_SOURCES:examples/%.cpp=bin/examples/%)
TEST_OBJECTS := $(TEST_SOURCES:tests/%.cpp=obj/tests/%.o)
INDIVIDUAL_TEST_EXECUTABLES := $(TEST_SOURCES:tests/%.cpp=bin/tests/%)
ALLEGRO_LIBS_LINK_ARGS := $(ALLEGRO_LIBS:%=-l%)
ALLEGRO_LIBS_LINK_MAIN_ARGS := $(ALLEGRO_LIBS_MAIN:%=-l%)



programs: $(PROGRAMS)



examples: $(EXAMPLES)



bin/programs/%: programs/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling program \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS_LINK_ARGS)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/examples/%: examples/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling program \e[1m\e[36m$<\033[0m..."
	g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include -I$(ALLEGRO_INCLUDE_DIR) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS_LINK_ARGS)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/$(PROJECT_BINARY_NAME): programs/$(PROJECT_BINARY_NAME).cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling program \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS_LINK_ARGS)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



tests: $(INDIVIDUAL_TEST_EXECUTABLES) bin/tests/test_runner



run_tests: tests
	find bin/tests -type f -exec {} \;



obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	@printf "compiling object for \e[1m\e[34m$<\033[0m...\n"
	@g++ -c -std=gnu++11 -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(ALLEGRO_INCLUDE_DIR)
	@echo "done. object at \033[1m\033[32m$@\033[0m"



obj/tests/%.o: tests/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling test obj file \e[1m\e[36m$<\033[0m...\n"
	@g++ -c -std=gnu++11 -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(GOOGLE_TEST_INCLUDE_DIR)
	@echo "done. Object at \033[1m\033[32m$@\033[0m"



bin/tests/%: obj/tests/%.o obj/tests/test_runner.o
	@mkdir -p $(@D)
	@printf "compiling standalone test \e[1m\e[36m$<\033[0m...\n"
	g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< obj/tests/test_runner.o -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) $(ALLEGRO_LIBS_LINK_ARGS)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/tests/test_runner: $(TEST_OBJECTS) obj/tests/test_runner.o
	@mkdir -p $(@D)
	@printf "compiling test_runer \e[1m\e[36m$<\033[0m...\n"
	g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) obj/tests/test_runner.o $< -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) $(ALLEGRO_LIBS_LINK_ARGS)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



clean:
	-rm -rdf obj/
	-rm $(OBJECTS)
	-rm $(PROGRAMS)
	-rm $(EXAMPLES)
	-rm $(TEST_OBJECTS)
	-rm $(INDIVIDUAL_TEST_EXECUTABLES)



fresh:
	make clean
	make -j8
	make examples -j8
	make tests -j8
	bin/tests/test_runner
)END";



std::string build_file_template = R"END(#!/bin/bash
find quintessence/*.yml | xargs ../blast/bin/programs/quintessence_from_yaml && make
)END";



void ___replace(std::string& str, std::string from, std::string to)
{
   //static const std::string from = "\t";
   //static const std::string to = std::string(3, ' ');

   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
}


std::vector<std::string> args;


class Generator
{
private:
   std::string project_name;

public:
   Generator(std::string project_name)
      : project_name(project_name)
   {}

   std::string get_project_name()
   {
      return project_name;
   }
   std::string get_command_for_make_dir()
   {
      std::stringstream command;
      command << "mkdir \"" << project_name << "\"";
      return command.str();
   }
   std::string mkprojdir(std::string dir)
   {
      std::stringstream command;
      command << "mkdir \"" << project_name << "/" << dir << "\"";
      return command.str();
   }
};


int main(int argc, char **argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   if (args.size() <= 1) throw std::runtime_error("You must pass a project name");

   Generator generator(argv[1]);
   ConsoleOutputter console_output;

   system(generator.get_command_for_make_dir().c_str());
   system(generator.mkprojdir("bin").c_str());
   system(generator.mkprojdir("include").c_str());
   system(generator.mkprojdir("examples").c_str());
   system(generator.mkprojdir(std::string("include/") + generator.get_project_name()).c_str());
   system(generator.mkprojdir("obj").c_str());
   system(generator.mkprojdir("programs").c_str());
   system(generator.mkprojdir("src").c_str());
   system(generator.mkprojdir("tests").c_str());
   system(generator.mkprojdir("quintessence").c_str());

   std::ofstream outfile(generator.get_project_name() + "/Makefile");
   std::string makefile_content = makefile_template;
   ___replace(makefile_content, "[[PROJECT_NAME]]", generator.get_project_name());
   outfile << makefile_content;
   outfile.close();

   std::string build_file_filename = generator.get_project_name() + "/build";
   std::ofstream outfile2(build_file_filename);
   std::string build_file_content = build_file_template;
   outfile2 << build_file_content;
   outfile.close();

   std::string gitignore_file_filename = generator.get_project_name() + "/.gitignore";
   std::ofstream outfile3(gitignore_file_filename);
   outfile3 << GITIGNORE_FILE_CONTENT;
   outfile.close();

   std::stringstream program_runner_path_name;
   program_runner_path_name << generator.get_project_name();
   program_runner_path_name << "/quintessence/" << PROGRAM_RUNNER_CLASS_NAME << ".q.yml";

   std::ofstream outfile4(program_runner_path_name.str());
   std::string program_runner_quintessence_file_content = PROGRAM_RUNNER_FILE_CONTENT;
   outfile4 << program_runner_quintessence_file_content;
   outfile4.close();

   std::ofstream outfile5(generator.get_project_name() + "/programs/main.cpp");
   std::string main_file_content = main_file_content_template;
   ___replace(main_file_content, "[[PROJECT_NAME]]", generator.get_project_name());
   ___replace(main_file_content, "[[PROGRAM_RUNNER_CLASS_NAME]]", PROGRAM_RUNNER_CLASS_NAME);
   outfile5 << main_file_content;
   outfile5.close();

   system((std::string("chmod +x ") + build_file_filename).c_str());

   std::stringstream finish_message;
   finish_message << "✅ Project files under \"" << generator.get_project_name() << "/\" generated." << std::endl;
   finish_message << "📝 Once in the \"" << generator.get_project_name() << "\" directory, use the \"./build\" "
                  << "script to generate and build the first source files "
                  << "(\"quintessence/" << PROGRAM_RUNNER_CLASS_NAME << ".q.yml\")." << std::endl;

   console_output.output_line(finish_message.str());

   std::runtime_error("You must pass a project name");

   return 0;
}


