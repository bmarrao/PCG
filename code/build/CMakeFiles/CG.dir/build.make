# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/marraob/Universidade/CG/PCG/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marraob/Universidade/CG/PCG/code/build

# Include any dependencies generated for this target.
include CMakeFiles/CG.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CG.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CG.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CG.dir/flags.make

CMakeFiles/CG.dir/main.cpp.o: CMakeFiles/CG.dir/flags.make
CMakeFiles/CG.dir/main.cpp.o: /home/marraob/Universidade/CG/PCG/code/main.cpp
CMakeFiles/CG.dir/main.cpp.o: CMakeFiles/CG.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marraob/Universidade/CG/PCG/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CG.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CG.dir/main.cpp.o -MF CMakeFiles/CG.dir/main.cpp.o.d -o CMakeFiles/CG.dir/main.cpp.o -c /home/marraob/Universidade/CG/PCG/code/main.cpp

CMakeFiles/CG.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CG.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marraob/Universidade/CG/PCG/code/main.cpp > CMakeFiles/CG.dir/main.cpp.i

CMakeFiles/CG.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CG.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marraob/Universidade/CG/PCG/code/main.cpp -o CMakeFiles/CG.dir/main.cpp.s

CMakeFiles/CG.dir/tinyxml2.cpp.o: CMakeFiles/CG.dir/flags.make
CMakeFiles/CG.dir/tinyxml2.cpp.o: /home/marraob/Universidade/CG/PCG/code/tinyxml2.cpp
CMakeFiles/CG.dir/tinyxml2.cpp.o: CMakeFiles/CG.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marraob/Universidade/CG/PCG/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CG.dir/tinyxml2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CG.dir/tinyxml2.cpp.o -MF CMakeFiles/CG.dir/tinyxml2.cpp.o.d -o CMakeFiles/CG.dir/tinyxml2.cpp.o -c /home/marraob/Universidade/CG/PCG/code/tinyxml2.cpp

CMakeFiles/CG.dir/tinyxml2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CG.dir/tinyxml2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marraob/Universidade/CG/PCG/code/tinyxml2.cpp > CMakeFiles/CG.dir/tinyxml2.cpp.i

CMakeFiles/CG.dir/tinyxml2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CG.dir/tinyxml2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marraob/Universidade/CG/PCG/code/tinyxml2.cpp -o CMakeFiles/CG.dir/tinyxml2.cpp.s

# Object files for target CG
CG_OBJECTS = \
"CMakeFiles/CG.dir/main.cpp.o" \
"CMakeFiles/CG.dir/tinyxml2.cpp.o"

# External object files for target CG
CG_EXTERNAL_OBJECTS =

CG: CMakeFiles/CG.dir/main.cpp.o
CG: CMakeFiles/CG.dir/tinyxml2.cpp.o
CG: CMakeFiles/CG.dir/build.make
CG: /usr/lib/x86_64-linux-gnu/libGL.so
CG: /usr/lib/x86_64-linux-gnu/libGLU.so
CG: /usr/lib/x86_64-linux-gnu/libglut.so
CG: /usr/lib/x86_64-linux-gnu/libGLEW.so
CG: /usr/lib/x86_64-linux-gnu/libGL.so
CG: /usr/lib/x86_64-linux-gnu/libGLU.so
CG: /usr/lib/x86_64-linux-gnu/libglut.so
CG: /usr/lib/x86_64-linux-gnu/libIL.so
CG: /usr/lib/x86_64-linux-gnu/libGLEW.so
CG: /usr/lib/x86_64-linux-gnu/libIL.so
CG: CMakeFiles/CG.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marraob/Universidade/CG/PCG/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable CG"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CG.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CG.dir/build: CG
.PHONY : CMakeFiles/CG.dir/build

CMakeFiles/CG.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CG.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CG.dir/clean

CMakeFiles/CG.dir/depend:
	cd /home/marraob/Universidade/CG/PCG/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marraob/Universidade/CG/PCG/code /home/marraob/Universidade/CG/PCG/code /home/marraob/Universidade/CG/PCG/code/build /home/marraob/Universidade/CG/PCG/code/build /home/marraob/Universidade/CG/PCG/code/build/CMakeFiles/CG.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CG.dir/depend

