# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project03.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/project03.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/project03.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project03.dir/flags.make

CMakeFiles/project03.dir/main.cpp.o: CMakeFiles/project03.dir/flags.make
CMakeFiles/project03.dir/main.cpp.o: ../main.cpp
CMakeFiles/project03.dir/main.cpp.o: CMakeFiles/project03.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project03.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project03.dir/main.cpp.o -MF CMakeFiles/project03.dir/main.cpp.o.d -o CMakeFiles/project03.dir/main.cpp.o -c /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/main.cpp

CMakeFiles/project03.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project03.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/main.cpp > CMakeFiles/project03.dir/main.cpp.i

CMakeFiles/project03.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project03.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/main.cpp -o CMakeFiles/project03.dir/main.cpp.s

# Object files for target project03
project03_OBJECTS = \
"CMakeFiles/project03.dir/main.cpp.o"

# External object files for target project03
project03_EXTERNAL_OBJECTS =

project03: CMakeFiles/project03.dir/main.cpp.o
project03: CMakeFiles/project03.dir/build.make
project03: CMakeFiles/project03.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable project03"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project03.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project03.dir/build: project03
.PHONY : CMakeFiles/project03.dir/build

CMakeFiles/project03.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project03.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project03.dir/clean

CMakeFiles/project03.dir/depend:
	cd /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/cmake-build-debug /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/cmake-build-debug /mnt/c/Users/maxcg/OneDrive/Desktop/PAST/Summer23/CS236/cs236/labs/project05/datalog-interpreter/cmake-build-debug/CMakeFiles/project03.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project03.dir/depend

