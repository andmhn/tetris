# This Makefile assumes the following file structure:
# include/   holds .h header files
# test/      holds doctest test definition .cpp files
# src/       holds tested .cpp source files (excluding main drivers)
# drivers/   holds main.cpp and test.cpp
# bin/       will be created to place created executables main-driver and test-driver
# build/     will be created to hold intermediate .o files

# compiler flags and source directories can be changed here
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -ggdb -pedantic -O0

TARGET_MAIN ?= tetris
TARGET_TEST ?= tester

BUILD_DIR ?= ./build
BIN_DIR   ?= ./exe
SRC_DIRS  ?= ./src
TEST_DIRS ?= ./test
MAIN_DIR  ?= ./drivers
INC_FLAGS ?= -I ./include
MKDIR_P   ?= mkdir -p

LDFLAGS   += -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

MAIN_SRCS := $(shell find $(SRC_DIRS) $(MAIN_DIR)/main.cpp -name "*.cpp")
TEST_SRCS := $(shell find $(SRC_DIRS) $(TEST_DIRS) $(MAIN_DIR)/test.cpp -name "*.cpp")
MAIN_OBJS := $(MAIN_SRCS:%=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:%=$(BUILD_DIR)/%.o)

SRCS := $(shell find $(SRC_DIRS) $(TEST_DIRS) $(MAIN_DIR) -name "*.cpp")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CPPFLAGS := $(INC_FLAGS) -MMD -MP -O0

.PHONY: bin test run clean analyze format

#=========  Targets  ==========

all: $(BIN_DIR)/$(TARGET_MAIN) $(BIN_DIR)/$(TARGET_TEST)

bin: $(BIN_DIR)/$(TARGET_MAIN)

build-test: $(BIN_DIR)/$(TARGET_TEST)

run: $(BIN_DIR)/$(TARGET_MAIN)
	$^

test: $(BIN_DIR)/$(TARGET_TEST)
	$^

run-debug: $(BIN_DIR)/$(TARGET_MAIN)
	gdb $^

test-debug: $(BIN_DIR)/$(TARGET_TEST)
	gdb $^

$(BIN_DIR)/$(TARGET_MAIN): $(MAIN_OBJS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(MAIN_OBJS) -o $@ $(LDFLAGS)

$(BIN_DIR)/$(TARGET_TEST): $(TEST_OBJS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(TEST_OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR) $(BIN_DIR)

# clean and then created a zipped copy of this folder
zip: clean
	d=`pwd | xargs basename`; rm -f $$d.zip
	d=`pwd | xargs basename`; cd ../; zip -r $$d/$$d.zip $$d -x "$$d/.git/*" "$$d/.cache/*";

analyze:
	cppcheck --enable=all $(MAIN_SRCS)

format:
	clang-format -i $(SRCS)

ctags:
	@echo generating ctags
	@$(CXX) -M $(LDFLAGS) $(INC_FLAGS) $(MAIN_SRCS) | sed -e 's/[\\ ]/\n/g' | \
		sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' | \
		ctags -L - --c-kinds=+p --fields=+iaSl --extras=+q --langmap=c:.c.h

# include the dependencies generated using the
-include $(DEPS)

