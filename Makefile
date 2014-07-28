#Source file directories
GTEST_DIR = ./src/lib/gtest-1.7.0
MAIN_DIR = ./src/main
TEST_DIR = ./src/test

#Outputs
TESTS = TestRoglick.out

#Compiler flags
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread

#Source file names
MAIN_SOURCES = $(wildcard $(MAIN_DIR)/*.cpp)
MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)
MAIN_DEPS = $(MAIN_SOURCES:.cpp=.d)

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_DEPS = $(TEST_SOURCES:.cpp=.d)

.PHONY : all, runtests, clean

#Main target
all : $(TESTS)

runtests : all
	./$(TESTS)

clean :
	rm -f $(TESTS) $(MAIN_OBJECTS) $(TEST_OBJECTS) $(MAIN_DEPS) $(TEST_DEPS)

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc

#Roglick.o : $(USER_DIR)/Roglick.cpp $(USER_DIR)/Roglick.h $(GTEST_HEADERS)
#	$(CXX) $(CPPFLAGS) -I$(USER_DIR) $(CXXFLAGS) -c $(USER_DIR)/Roglick.cpp
#
#TestRoglick.o : $(TEST_DIR)/TestRoglick.cpp $(GTEST_HEADERS)
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(USER_DIR) -c $(TEST_DIR)/TestRoglick.cpp

TestRoglick.out : $(MAIN_OBJECTS) $(TEST_OBJECTS) gtest-all.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(MAIN_DIR) -MD -MP -MF ${@:.o=.d} -c $< -o $@

-include $(MAIN_DEPS) $(TEST_DEPS)

