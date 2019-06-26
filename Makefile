PROJECT_NAME_SNAKE_CASE=ncurses_art



LIBS_ROOT=/Users/markoates/Repos
GOOGLE_TEST_DIR=$(LIBS_ROOT)/googletest
GOOGLE_TEST_LIB_DIR=$(GOOGLE_TEST_DIR)/build/googlemock/gtest
GOOGLE_TEST_INCLUDE_DIR=$(GOOGLE_TEST_DIR)/googletest/include
NCURSES_INCLUDE_DIR=/usr/local/opt/ncurses/include
NCURSES_LIB_DIR=/usr/local/opt/ncurses/lib
YAML_CPP_DIR=$(LIBS_ROOT)/yaml-cpp
YAML_CPP_LIB_DIR=$(YAML_CPP_DIR)/build
YAML_CPP_INCLUDE_DIR=$(YAML_CPP_DIR)/include


# this is the directory of the project (it's auto_generated)
PROJECT_DIR=$(LIBS_ROOT)/$(PROJECT_NAME_SNAKE_CASE)


GOOGLE_TEST_LIBS=gtest
NCURSES_LIB=ncurses
YAML_CPP_LIBS=yaml-cpp


.PHONY: all clean main fresh



SOURCES := $(shell find src -name '*.cpp')
PROJEKTS := $(shell find projekts -name '*.cpp')
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)
TEST_SOURCES := $(shell find tests -name '*.cpp')
TEST_OBJECTS := $(TEST_SOURCES:tests/%.cpp=obj/tests/%.o)
INDIVIDUAL_TEST_EXECUTABLES := $(TEST_SOURCES:tests/%.cpp=bin/tests/%)
PROJEKT_EXECUTABLES := $(PROJEKTS:projekts/%.cpp=bin/%)



projekts: $(PROJEKT_EXECUTABLES)



bin/%: projekts/%.cpp $(OBJECTS)
	@printf "compiling projekt \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) -D_XOPEN_SOURCE_EXTENDED
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/$(PROJECT_NAME_SNAKE_CASE): programs/$(PROJECT_NAME_SNAKE_CASE).cpp $(OBJECTS)
	@printf "compiling program \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) -D_XOPEN_SOURCE_EXTENDED
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



tests: $(INDIVIDUAL_TEST_EXECUTABLES) bin/test_runner



run_tests: tests
	find bin/tests -type f -exec {} \;



obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	@printf "compiling object for \e[1m\e[34m$<\033[0m...\n"
	@g++ -c -std=gnu++11 -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -D_XOPEN_SOURCE_EXTENDED
	@echo "done. object at \033[1m\033[32m$@\033[0m"



obj/tests/%.o: tests/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling test obj file \e[1m\e[36m$<\033[0m...\n"
	@g++ -c -std=gnu++11 -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(GOOGLE_TEST_INCLUDE_DIR)
	@echo "done. Object at \033[1m\033[32m$@\033[0m"



obj/programs/test_runner.o: programs/test_runner.cpp
	@mkdir -p $(@D)
	@printf "compiling test obj file \e[1m\e[36m$<\033[0m...\n"
	@g++ -c -std=gnu++11 -Wall -Wuninitialized -Weffc++ $< -o $@ -I$(GOOGLE_TEST_INCLUDE_DIR)
	@echo "done. Object at \033[1m\033[32m$@\033[0m"



bin/tests/%: obj/tests/%.o obj/programs/test_runner.o
	@mkdir -p $(@D)
	@printf "compiling standalone test \e[1m\e[36m$<\033[0m...\n"
	@g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< obj/programs/test_runner.o -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/test_runner: programs/test_runner.cpp $(TEST_OBJECTS)
	echo $(TEST_OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling test_runer \e[1m\e[36m$<\033[0m...\n"
	@g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $(TEST_OBJECTS) $< -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



clean:
	-rm -rdf obj/
	-rm $(PROGRAM_EXECUTABLES)



fresh:
	make clean
	make -j8
	make bin/test_runner
