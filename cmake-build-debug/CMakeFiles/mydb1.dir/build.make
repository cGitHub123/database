# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/caibin/my/database/mydb1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/caibin/my/database/mydb1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mydb1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mydb1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mydb1.dir/flags.make

CMakeFiles/mydb1.dir/lesson1/l.c.o: CMakeFiles/mydb1.dir/flags.make
CMakeFiles/mydb1.dir/lesson1/l.c.o: ../lesson1/l.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/caibin/my/database/mydb1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mydb1.dir/lesson1/l.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mydb1.dir/lesson1/l.c.o   -c /Users/caibin/my/database/mydb1/lesson1/l.c

CMakeFiles/mydb1.dir/lesson1/l.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mydb1.dir/lesson1/l.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/caibin/my/database/mydb1/lesson1/l.c > CMakeFiles/mydb1.dir/lesson1/l.c.i

CMakeFiles/mydb1.dir/lesson1/l.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mydb1.dir/lesson1/l.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/caibin/my/database/mydb1/lesson1/l.c -o CMakeFiles/mydb1.dir/lesson1/l.c.s

CMakeFiles/mydb1.dir/lesson2/l.c.o: CMakeFiles/mydb1.dir/flags.make
CMakeFiles/mydb1.dir/lesson2/l.c.o: ../lesson2/l.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/caibin/my/database/mydb1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mydb1.dir/lesson2/l.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mydb1.dir/lesson2/l.c.o   -c /Users/caibin/my/database/mydb1/lesson2/l.c

CMakeFiles/mydb1.dir/lesson2/l.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mydb1.dir/lesson2/l.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/caibin/my/database/mydb1/lesson2/l.c > CMakeFiles/mydb1.dir/lesson2/l.c.i

CMakeFiles/mydb1.dir/lesson2/l.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mydb1.dir/lesson2/l.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/caibin/my/database/mydb1/lesson2/l.c -o CMakeFiles/mydb1.dir/lesson2/l.c.s

# Object files for target mydb1
mydb1_OBJECTS = \
"CMakeFiles/mydb1.dir/lesson1/l.c.o" \
"CMakeFiles/mydb1.dir/lesson2/l.c.o"

# External object files for target mydb1
mydb1_EXTERNAL_OBJECTS =

mydb1: CMakeFiles/mydb1.dir/lesson1/l.c.o
mydb1: CMakeFiles/mydb1.dir/lesson2/l.c.o
mydb1: CMakeFiles/mydb1.dir/build.make
mydb1: CMakeFiles/mydb1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/caibin/my/database/mydb1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable mydb1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mydb1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mydb1.dir/build: mydb1

.PHONY : CMakeFiles/mydb1.dir/build

CMakeFiles/mydb1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mydb1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mydb1.dir/clean

CMakeFiles/mydb1.dir/depend:
	cd /Users/caibin/my/database/mydb1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/caibin/my/database/mydb1 /Users/caibin/my/database/mydb1 /Users/caibin/my/database/mydb1/cmake-build-debug /Users/caibin/my/database/mydb1/cmake-build-debug /Users/caibin/my/database/mydb1/cmake-build-debug/CMakeFiles/mydb1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mydb1.dir/depend

