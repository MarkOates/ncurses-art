LIBS_ROOT=/Users/markoates/Repos
NCURSES_INCLUDE_DIR=/usr/local/opt/ncurses/include
NCURSES_LIB_DIR=/usr/local/opt/ncurses/lib
YAML_CPP_DIR=$(LIBS_ROOT)/yaml-cpp
YAML_CPP_LIB_DIR=$(YAML_CPP_DIR)/build
YAML_CPP_INCLUDE_DIR=$(YAML_CPP_DIR)/include
GOOGLE_TEST_DIR=$(LIBS_ROOT)/googletest
GOOGLE_TEST_LIB_DIR=$(GOOGLE_TEST_DIR)/build/googlemock/gtest
GOOGLE_TEST_INCLUDE_DIR=$(GOOGLE_TEST_DIR)/googletest/include



GOOGLE_TEST_LIBS=gtest
NCURSES_LIB=ncurses
YAML_CPP_LIBS=yaml-cpp



SOURCES := $(shell find src -name '*.cpp')
PROGRAM_SOURCES := $(shell find programs -name '*.cpp')
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)
TEST_SOURCES := $(shell find tests -name '*.cpp')
TEST_OBJECTS := $(TEST_SOURCES:tests/%.cpp=obj/tests/%.o)
INDIVIDUAL_TEST_EXECUTABLES := $(TEST_SOURCES:tests/%.cpp=bin/tests/%)
PROGRAMS := $(PROGRAM_SOURCES:programs/%.cpp=bin/programs/%)
ALL_COMPILED_EXECUTABLES_IN_BIN := $(shell find bin/**/* -perm +111 -type f)



TERMINAL_COLOR_YELLOW=\033[1;33m
TERMINAL_COLOR_RESET=\033[0m



define output_terminal_message
	$(eval compteur=$(shell echo $$(($(compteur)+1))))
	@echo "\n$(TERMINAL_COLOR_YELLOW)===== Stage $(compteur): $(1) =====$(TERMINAL_COLOR_RESET)\n"
endef



main:
	$(call output_terminal_message,"Compose componets from all quintessence files")
	@make quintessences
	$(call output_terminal_message,"Make all the object files")
	@make objects
	#$(call output_terminal_message,"Make all the test files")
	#@make tests
	#$(call output_terminal_message,"Run the tests for all the components")
	#@make run_tests
	$(call output_terminal_message,"Make all the programs")
	@make programs
	$(call output_terminal_message,"Make all the example programs")
	@make examples
	$(call output_terminal_message,"================= FINISHED! ===================")



quintessences: $(QINTESSENCE_SOURCES)
	@./build



programs: $(PROGRAMS)



objects: $(OBJECTS)



bin/programs/%: programs/%.cpp $(OBJECTS)
	@printf "compiling projekt \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) -D_XOPEN_SOURCE_EXTENDED
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



tests: $(INDIVIDUAL_TEST_EXECUTABLES) bin/test_runner



run_tests: tests
	find bin/tests -type f -exec {} \;



obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	@printf "compiling object for \e[1m\e[34m$<\033[0m..."
	@g++ -c -std=gnu++11 -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -D_XOPEN_SOURCE_EXTENDED -Qunused-arguments
	@echo "done. object at \033[1m\033[32m$@\033[0m"



obj/tests/%.o: tests/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling test obj file \e[1m\e[36m$<\033[0m..."
	@g++ -c -std=gnu++11 -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -I$(YAML_CPP_INCLUDE_DIR) -Qunused-arguments
	@echo "done. Object at \033[1m\033[32m$@\033[0m"



obj/tests/test_runner.o: tests/test_runner.cpp
	@mkdir -p $(@D)
	@printf "compiling test obj file \e[1m\e[36m$<\033[0m..."
	@g++ -c -std=gnu++11 -Wall -Wuninitialized -Weffc++ $< -o $@ -I$(GOOGLE_TEST_INCLUDE_DIR) -Qunused-arguments
	@echo "done. Object at \033[1m\033[32m$@\033[0m"



bin/tests/%: obj/tests/%.o obj/tests/test_runner.o
	@mkdir -p $(@D)
	@printf "compiling standalone test \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< obj/tests/test_runner.o -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) -Qunused-arguments
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



#bin/test_runner: tests/test_runner.cpp $(TEST_OBJECTS)
	#echo $(TEST_OBJECTS)
	#@mkdir -p $(@D)
	#@printf "compiling test_runer \e[1m\e[36m$<\033[0m..."
	#@g++ -std=gnu++11 -Wall -Wuninitialized -Weffc++ $(OBJECTS) $(TEST_OBJECTS) $< -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) -Qunused-arguments
	#@echo "done. Executable at \033[1m\033[32m$@\033[0m"



clean:
	-rm -rdf obj/
	-rm $(PROGRAMS)
	-rm $(ALL_COMPILED_EXECUTABLES_IN_BIN)



fresh:
	make clean
	make -j8
	make bin/test_runner
