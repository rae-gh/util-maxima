# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima

# Include any dependencies generated for this target.
include CMakeFiles/PsuMaxima.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PsuMaxima.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PsuMaxima.dir/flags.make

CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.o: CMakeFiles/PsuMaxima.dir/flags.make
CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.o: PsuMaxima.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.o -c /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/PsuMaxima.cpp

CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/PsuMaxima.cpp > CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.i

CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/PsuMaxima.cpp -o CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.s

CMakeFiles/PsuMaxima.dir/Ccp4.cpp.o: CMakeFiles/PsuMaxima.dir/flags.make
CMakeFiles/PsuMaxima.dir/Ccp4.cpp.o: Ccp4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PsuMaxima.dir/Ccp4.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PsuMaxima.dir/Ccp4.cpp.o -c /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/Ccp4.cpp

CMakeFiles/PsuMaxima.dir/Ccp4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PsuMaxima.dir/Ccp4.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/Ccp4.cpp > CMakeFiles/PsuMaxima.dir/Ccp4.cpp.i

CMakeFiles/PsuMaxima.dir/Ccp4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PsuMaxima.dir/Ccp4.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/Ccp4.cpp -o CMakeFiles/PsuMaxima.dir/Ccp4.cpp.s

# Object files for target PsuMaxima
PsuMaxima_OBJECTS = \
"CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.o" \
"CMakeFiles/PsuMaxima.dir/Ccp4.cpp.o"

# External object files for target PsuMaxima
PsuMaxima_EXTERNAL_OBJECTS =

PsuMaxima: CMakeFiles/PsuMaxima.dir/PsuMaxima.cpp.o
PsuMaxima: CMakeFiles/PsuMaxima.dir/Ccp4.cpp.o
PsuMaxima: CMakeFiles/PsuMaxima.dir/build.make
PsuMaxima: CMakeFiles/PsuMaxima.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable PsuMaxima"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PsuMaxima.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PsuMaxima.dir/build: PsuMaxima

.PHONY : CMakeFiles/PsuMaxima.dir/build

CMakeFiles/PsuMaxima.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PsuMaxima.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PsuMaxima.dir/clean

CMakeFiles/PsuMaxima.dir/depend:
	cd /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima /home/rachel/Documents/Bioinformatics/PsuMaxima/Cpp/PsuMaxima/CMakeFiles/PsuMaxima.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PsuMaxima.dir/depend
