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
CMAKE_SOURCE_DIR = /Users/caibin/my/database/mydb1/lesson7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/caibin/my/database/mydb1/lesson7/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lesson7.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lesson7.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lesson7.dir/flags.make

CMakeFiles/lesson7.dir/l.c.o: CMakeFiles/lesson7.dir/flags.make
CMakeFiles/lesson7.dir/l.c.o: ../l.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/caibin/my/database/mydb1/lesson7/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lesson7.dir/l.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lesson7.dir/l.c.o   -c /Users/caibin/my/database/mydb1/lesson7/l.c

CMakeFiles/lesson7.dir/l.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lesson7.dir/l.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/caibin/my/database/mydb1/lesson7/l.c > CMakeFiles/lesson7.dir/l.c.i

CMakeFiles/lesson7.dir/l.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lesson7.dir/l.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/caibin/my/database/mydb1/lesson7/l.c -o CMakeFiles/lesson7.dir/l.c.s

# Object files for target lesson7
lesson7_OBJECTS = \
"CMakeFiles/lesson7.dir/l.c.o"

# External object files for target lesson7
lesson7_EXTERNAL_OBJECTS =

lesson7: CMakeFiles/lesson7.dir/l.c.o
lesson7: CMakeFiles/lesson7.dir/build.make
lesson7: CMakeFiles/lesson7.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/caibin/my/database/mydb1/lesson7/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable lesson7"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lesson7.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lesson7.dir/build: lesson7

.PHONY : CMakeFiles/lesson7.dir/build

CMakeFiles/lesson7.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lesson7.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lesson7.dir/clean

CMakeFiles/lesson7.dir/depend:
	cd /Users/caibin/my/database/mydb1/lesson7/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/caibin/my/database/mydb1/lesson7 /Users/caibin/my/database/mydb1/lesson7 /Users/caibin/my/database/mydb1/lesson7/cmake-build-debug /Users/caibin/my/database/mydb1/lesson7/cmake-build-debug /Users/caibin/my/database/mydb1/lesson7/cmake-build-debug/CMakeFiles/lesson7.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lesson7.dir/depend

