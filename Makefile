#Top-level directories
#Where to find source files
SRC_DIR = src
#Where to put intermediate compiled build files
BUILD_DIR = build
#Where to put created documentation
DOCS_DIR = docs
#Natural Docs project directory
NATDOCS_DIR = natdoc

#Source file subdirectories
GTEST_DIR = $(SRC_DIR)/lib/gtest-1.7.0
MAIN_DIR  = $(SRC_DIR)/main
TEST_DIR  = $(SRC_DIR)/test

#Outputs
TESTS = TestRoglick.out

#Compiler flags
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread

#Source file names
MAIN_SOURCES = $(shell find $(MAIN_DIR) -name *.cpp)
#Objects are placed in the build directory, mirroring source directory structure
MAIN_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MAIN_SOURCES))
#Dependency files go alongside our compiled object files
MAIN_DEPS = $(MAIN_OBJECTS:.o=.d)

#Test sources follow identical principles, of course
TEST_SOURCES = $(shell find $(TEST_DIR) -name *.cpp)
TEST_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SOURCES))
TEST_DEPS = $(TEST_OBJECTS:.o=.d)

#Our "phony" targets
.PHONY : all, tests, runtests, todolist, clean

#Default target
#NB: Eventually this will not build the tests, but for now that's all it does
all : todolist docs tests

todolist :
	-@for file in $(MAIN_SOURCES); do fgrep -Hn -e TODO -e FIXME $$file | sed 's#//##'; done; true

#Build all of our unit tests
tests : $(TESTS)

#Run unit tests after ensuring they're all up-to-date
runtests : tests
	./$(TESTS)

#Clean everything up
clean :
	-@rm -rf $(TESTS) $(BUILD_DIR)/*

##
## Natural Docs build targets
##

.PHONY : docs, fulldocs, docsdir

#Command for building our documentation
NATURALDOCS = -naturaldocs -i $(MAIN_DIR)/ -o HTML $(DOCS_DIR)/ -p $(NATDOCS_DIR)/

#A "normal" build
docs : docsdir
	$(NATURALDOCS)

#A full build/rebuild
fulldocs : docsdir
	$(NATURALDOCS) -r

#Ensure our docs directory exists
docsdir :
	@mkdir -p $(DOCS_DIR)

##
## END Natural Docs
##

#BEGIN RULES FOR BUILDING GTEST-ALL
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

$(BUILD_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc -o $@
#END GTEST-ALL BUILD RULES

#This is our unit test output target
TestRoglick.out : $(MAIN_OBJECTS) $(TEST_OBJECTS) $(BUILD_DIR)/gtest-all.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

#Our catch-all build target:
# 1) Ensure the target build directory exists
# 2) Compile the target object file, also generating a dependency file
# NB: This rule is built to compile .cpp files into corresponding .o files
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(MAIN_DIR) -MD -MP -MF ${@:.o=.d} -c $< -o $@

#Include the dependency rules we generate, but ignore any that don't exist
# (as in the case that we haven't built yet
-include $(MAIN_DEPS) $(TEST_DEPS)

