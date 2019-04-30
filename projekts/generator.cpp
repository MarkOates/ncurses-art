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



std::string const PROGRAM_RUNNER_FILE_CONTENT = R"END(functions:
  - name: run
    type: std::string
    body: return "Hello Buddy!";
)END";



std::string const GITIGNORE_FILE_CONTENT = R"END(
bin/*
!bin/data/*
.DS_Store
obj/*
.DS_Store
)END";



std::string const RERUN_SCRIPT_FILENAME = "rr";
std::string const RERUN_SCRIPT_CONTENT = R"END(
#!/bin/bash

yellow='\033[1;33m'
reset_text='\033[0m'

if [ "$#" == "0" ]
then
  echo "Error: You must provide an argument, which should be a name of a component."
  echo "Example: \"./rr ProgramRunner\""
else
  chruby 2.5.1
  declare -a commands=(
    "echo \"\n$yellow===== STAGE 0: Compose componets from all yamls =====$reset_text\n\"; ./build"
    "echo \"\n$yellow===== STAGE 1: Make all the components =====$reset_text\n\"; make"
    "echo \"\n$yellow===== STAGE 2: Make the test for this component =====$reset_text\n\"; make ./bin/tests/$@Test"
    "echo \"\n$yellow===== STAGE 3: Run the test for this component =====$reset_text\n\"; ./bin/tests/$@Test"
  )

  rerun_command="${commands[0]} && ${commands[1]} && ${commands[2]} && ${commands[3]}"

  rerun -c $rerun_command -p "**/$@{Test.cpp,_test.cpp,.q.*}"
fi
)END";



std::string TEST_RUNNER_CLASS_NAME = "TestRunner";
std::string const TEST_RUNNER_FILE_CONTENT = R"END(
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
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



std::string PROGRAM_RUNNER_TEST_FILE_CONTENT = R"END(
#include <gtest/gtest.h>

#include <[[PROGRAM_RUNNER_CLASS_NAME]].hpp>

TEST([[PROGRAM_RUNNER_CLASS_NAME]]Test, run__returns_the_expected_response)
{
   [[PROGRAM_RUNNER_CLASS_NAME]] program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
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



tests: $(INDIVIDUAL_TEST_EXECUTABLES) bin/tests/[[TEST_RUNNER_CLASS_NAME]]



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



bin/tests/%: obj/tests/%.o obj/tests/[[TEST_RUNNER_CLASS_NAME]].o
	@mkdir -p $(@D)
	@printf "compiling standalone test \e[1m\e[36m$<\033[0m...\n"
	g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< obj/tests/[[TEST_RUNNER_CLASS_NAME]].o -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) $(ALLEGRO_LIBS_LINK_ARGS)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/tests/[[TEST_RUNNER_CLASS_NAME]]: $(TEST_OBJECTS) obj/tests/[[TEST_RUNNER_CLASS_NAME]].o
	@mkdir -p $(@D)
	@printf "compiling test_runer \e[1m\e[36m$<\033[0m...\n"
	g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) obj/tests/[[TEST_RUNNER_CLASS_NAME]].o $< -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) $(ALLEGRO_LIBS_LINK_ARGS)
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
	bin/tests/[[TEST_RUNNER_CLASS_NAME]]
)END";



std::string build_file_template = R"END(#!/bin/bash
find . -path "./quintessence/*.yml" | xargs ../blast/bin/programs/quintessence_from_yaml
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
   ___replace(makefile_content, "[[TEST_RUNNER_CLASS_NAME]]", TEST_RUNNER_CLASS_NAME);
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

   //std::stringstream program_runner_path_name;
   //program_runner_path_name << generator.get_project_name();
   //program_runner_path_name << "/quintessence/" << PROGRAM_RUNNER_CLASS_NAME << ".q.yml";

   //std::ofstream outfile4(program_runner_path_name.str());
   //std::string program_runner_quintessence_file_content = PROGRAM_RUNNER_FILE_CONTENT;
   //outfile4 << program_runner_quintessence_file_content;
   //outfile4.close();

   std::ofstream outfile5(generator.get_project_name() + "/programs/main.cpp");
   std::string main_file_content = main_file_content_template;
   ___replace(main_file_content, "[[PROJECT_NAME]]", generator.get_project_name());
   ___replace(main_file_content, "[[PROGRAM_RUNNER_CLASS_NAME]]", PROGRAM_RUNNER_CLASS_NAME);
   outfile5 << main_file_content;
   outfile5.close();

   std::ofstream outfile6(generator.get_project_name() + "/tests/" + TEST_RUNNER_CLASS_NAME + ".cpp");
   outfile6 << TEST_RUNNER_FILE_CONTENT;
   outfile6.close();

   //std::ofstream outfile7(generator.get_project_name() + "/tests/" + PROGRAM_RUNNER_CLASS_NAME + "Test.cpp");
   //std::string program_runner_test_file_content = PROGRAM_RUNNER_TEST_FILE_CONTENT;
   //___replace(program_runner_test_file_content, "[[PROGRAM_RUNNER_CLASS_NAME]]", PROGRAM_RUNNER_CLASS_NAME);
   //outfile7 << program_runner_test_file_content;
   //outfile7.close();

   std::string rerun_script_filename = generator.get_project_name() + "/rr";
   std::ofstream outfile8(rerun_script_filename);
   outfile8 << RERUN_SCRIPT_CONTENT;
   outfile8.close();
   system((std::string("chmod +x ") + rerun_script_filename).c_str());

   system((std::string("chmod +x ") + build_file_filename).c_str());

   std::stringstream finish_message;
   finish_message << "✅ Project files under \"" << generator.get_project_name() << "/\" generated." << std::endl;
   finish_message << "⚠️ Important: You should now generate your first component by first cd-ing into your " << std::endl;
   finish_message << "project directory (\"cd " << generator.get_project_name() << "\") and running the command:" << std::endl;
   finish_message << std::endl;
   finish_message << "  ../ncurses-art/bin/component_generator NameOfYourComponent" << std::endl;
   finish_message << std::endl;
   finish_message << "📝 Once in the \"" << generator.get_project_name() << "\" directory, use the rerun \"./rr\" "
                  << "script in a separate terminal window to develop your component.  It will run the \"./build\" script "
                  << "to generate and build the first source files from the "
                  << "quintessence/ directory (\"quintessence/" << PROGRAM_RUNNER_CLASS_NAME << ".q.yml\"). "
                  << "as well as build and run the test file \"tests/" << PROGRAM_RUNNER_CLASS_NAME << "Test.cpp\" for the "
                  << "component." << std::endl;

   console_output.output_line(finish_message.str());

   std::runtime_error("You must pass a project name");

   return 0;
}
