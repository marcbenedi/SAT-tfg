# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/marcbenedi/Desktop/SAT-tfg/pblib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcbenedi/Desktop/SAT-tfg/pblib

# Include any dependencies generated for this target.
include CMakeFiles/pbo2maxsat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pbo2maxsat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pbo2maxsat.dir/flags.make

CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o: CMakeFiles/pbo2maxsat.dir/flags.make
CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o: pbo2maxsat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcbenedi/Desktop/SAT-tfg/pblib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o -c /home/marcbenedi/Desktop/SAT-tfg/pblib/pbo2maxsat.cpp

CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcbenedi/Desktop/SAT-tfg/pblib/pbo2maxsat.cpp > CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.i

CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcbenedi/Desktop/SAT-tfg/pblib/pbo2maxsat.cpp -o CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.s

CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o.requires:

.PHONY : CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o.requires

CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o.provides: CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o.requires
	$(MAKE) -f CMakeFiles/pbo2maxsat.dir/build.make CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o.provides.build
.PHONY : CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o.provides

CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o.provides.build: CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o


# Object files for target pbo2maxsat
pbo2maxsat_OBJECTS = \
"CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o"

# External object files for target pbo2maxsat
pbo2maxsat_EXTERNAL_OBJECTS =

pbo2maxsat: CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o
pbo2maxsat: CMakeFiles/pbo2maxsat.dir/build.make
pbo2maxsat: libpblib.a
pbo2maxsat: CMakeFiles/pbo2maxsat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcbenedi/Desktop/SAT-tfg/pblib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pbo2maxsat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pbo2maxsat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pbo2maxsat.dir/build: pbo2maxsat

.PHONY : CMakeFiles/pbo2maxsat.dir/build

CMakeFiles/pbo2maxsat.dir/requires: CMakeFiles/pbo2maxsat.dir/pbo2maxsat.cpp.o.requires

.PHONY : CMakeFiles/pbo2maxsat.dir/requires

CMakeFiles/pbo2maxsat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pbo2maxsat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pbo2maxsat.dir/clean

CMakeFiles/pbo2maxsat.dir/depend:
	cd /home/marcbenedi/Desktop/SAT-tfg/pblib && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcbenedi/Desktop/SAT-tfg/pblib /home/marcbenedi/Desktop/SAT-tfg/pblib /home/marcbenedi/Desktop/SAT-tfg/pblib /home/marcbenedi/Desktop/SAT-tfg/pblib /home/marcbenedi/Desktop/SAT-tfg/pblib/CMakeFiles/pbo2maxsat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pbo2maxsat.dir/depend
