# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/felipebuniac/Github/Supercomputing/Aula12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/felipebuniac/Github/Supercomputing/Aula12/build

# Include any dependencies generated for this target.
include CMakeFiles/fs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fs.dir/flags.make

CMakeFiles/fs.dir/exemplo_fs.cpp.o: CMakeFiles/fs.dir/flags.make
CMakeFiles/fs.dir/exemplo_fs.cpp.o: ../exemplo_fs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/felipebuniac/Github/Supercomputing/Aula12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fs.dir/exemplo_fs.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fs.dir/exemplo_fs.cpp.o -c /Users/felipebuniac/Github/Supercomputing/Aula12/exemplo_fs.cpp

CMakeFiles/fs.dir/exemplo_fs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fs.dir/exemplo_fs.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/felipebuniac/Github/Supercomputing/Aula12/exemplo_fs.cpp > CMakeFiles/fs.dir/exemplo_fs.cpp.i

CMakeFiles/fs.dir/exemplo_fs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fs.dir/exemplo_fs.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/felipebuniac/Github/Supercomputing/Aula12/exemplo_fs.cpp -o CMakeFiles/fs.dir/exemplo_fs.cpp.s

# Object files for target fs
fs_OBJECTS = \
"CMakeFiles/fs.dir/exemplo_fs.cpp.o"

# External object files for target fs
fs_EXTERNAL_OBJECTS =

fs: CMakeFiles/fs.dir/exemplo_fs.cpp.o
fs: CMakeFiles/fs.dir/build.make
fs: CMakeFiles/fs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/felipebuniac/Github/Supercomputing/Aula12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fs.dir/build: fs

.PHONY : CMakeFiles/fs.dir/build

CMakeFiles/fs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fs.dir/clean

CMakeFiles/fs.dir/depend:
	cd /Users/felipebuniac/Github/Supercomputing/Aula12/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/felipebuniac/Github/Supercomputing/Aula12 /Users/felipebuniac/Github/Supercomputing/Aula12 /Users/felipebuniac/Github/Supercomputing/Aula12/build /Users/felipebuniac/Github/Supercomputing/Aula12/build /Users/felipebuniac/Github/Supercomputing/Aula12/build/CMakeFiles/fs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fs.dir/depend

