# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yyatsenk/Desktop/Nibbler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yyatsenk/Desktop/Nibbler/build

# Include any dependencies generated for this target.
include main/CMakeFiles/SDL2Test.dir/depend.make

# Include the progress variables for this target.
include main/CMakeFiles/SDL2Test.dir/progress.make

# Include the compile flags for this target's objects.
include main/CMakeFiles/SDL2Test.dir/flags.make

main/CMakeFiles/SDL2Test.dir/src/main.cpp.o: main/CMakeFiles/SDL2Test.dir/flags.make
main/CMakeFiles/SDL2Test.dir/src/main.cpp.o: ../main/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyatsenk/Desktop/Nibbler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object main/CMakeFiles/SDL2Test.dir/src/main.cpp.o"
	cd /home/yyatsenk/Desktop/Nibbler/build/main && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SDL2Test.dir/src/main.cpp.o -c /home/yyatsenk/Desktop/Nibbler/main/src/main.cpp

main/CMakeFiles/SDL2Test.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SDL2Test.dir/src/main.cpp.i"
	cd /home/yyatsenk/Desktop/Nibbler/build/main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyatsenk/Desktop/Nibbler/main/src/main.cpp > CMakeFiles/SDL2Test.dir/src/main.cpp.i

main/CMakeFiles/SDL2Test.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SDL2Test.dir/src/main.cpp.s"
	cd /home/yyatsenk/Desktop/Nibbler/build/main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyatsenk/Desktop/Nibbler/main/src/main.cpp -o CMakeFiles/SDL2Test.dir/src/main.cpp.s

main/CMakeFiles/SDL2Test.dir/src/main.cpp.o.requires:

.PHONY : main/CMakeFiles/SDL2Test.dir/src/main.cpp.o.requires

main/CMakeFiles/SDL2Test.dir/src/main.cpp.o.provides: main/CMakeFiles/SDL2Test.dir/src/main.cpp.o.requires
	$(MAKE) -f main/CMakeFiles/SDL2Test.dir/build.make main/CMakeFiles/SDL2Test.dir/src/main.cpp.o.provides.build
.PHONY : main/CMakeFiles/SDL2Test.dir/src/main.cpp.o.provides

main/CMakeFiles/SDL2Test.dir/src/main.cpp.o.provides.build: main/CMakeFiles/SDL2Test.dir/src/main.cpp.o


# Object files for target SDL2Test
SDL2Test_OBJECTS = \
"CMakeFiles/SDL2Test.dir/src/main.cpp.o"

# External object files for target SDL2Test
SDL2Test_EXTERNAL_OBJECTS =

main/SDL2Test: main/CMakeFiles/SDL2Test.dir/src/main.cpp.o
main/SDL2Test: main/CMakeFiles/SDL2Test.dir/build.make
main/SDL2Test: main/CMakeFiles/SDL2Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yyatsenk/Desktop/Nibbler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SDL2Test"
	cd /home/yyatsenk/Desktop/Nibbler/build/main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SDL2Test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
main/CMakeFiles/SDL2Test.dir/build: main/SDL2Test

.PHONY : main/CMakeFiles/SDL2Test.dir/build

main/CMakeFiles/SDL2Test.dir/requires: main/CMakeFiles/SDL2Test.dir/src/main.cpp.o.requires

.PHONY : main/CMakeFiles/SDL2Test.dir/requires

main/CMakeFiles/SDL2Test.dir/clean:
	cd /home/yyatsenk/Desktop/Nibbler/build/main && $(CMAKE_COMMAND) -P CMakeFiles/SDL2Test.dir/cmake_clean.cmake
.PHONY : main/CMakeFiles/SDL2Test.dir/clean

main/CMakeFiles/SDL2Test.dir/depend:
	cd /home/yyatsenk/Desktop/Nibbler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yyatsenk/Desktop/Nibbler /home/yyatsenk/Desktop/Nibbler/main /home/yyatsenk/Desktop/Nibbler/build /home/yyatsenk/Desktop/Nibbler/build/main /home/yyatsenk/Desktop/Nibbler/build/main/CMakeFiles/SDL2Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : main/CMakeFiles/SDL2Test.dir/depend

