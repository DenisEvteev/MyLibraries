# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/denis/CLionProjects/clion-2019.1.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/denis/CLionProjects/clion-2019.1.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/denis/CLionProjects/vec_lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/denis/CLionProjects/vec_lib/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/vec_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vec_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vec_lib.dir/flags.make

CMakeFiles/vec_lib.dir/main.cpp.o: CMakeFiles/vec_lib.dir/flags.make
CMakeFiles/vec_lib.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/denis/CLionProjects/vec_lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vec_lib.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vec_lib.dir/main.cpp.o -c /home/denis/CLionProjects/vec_lib/main.cpp

CMakeFiles/vec_lib.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vec_lib.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denis/CLionProjects/vec_lib/main.cpp > CMakeFiles/vec_lib.dir/main.cpp.i

CMakeFiles/vec_lib.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vec_lib.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denis/CLionProjects/vec_lib/main.cpp -o CMakeFiles/vec_lib.dir/main.cpp.s

CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.o: CMakeFiles/vec_lib.dir/flags.make
CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.o: /home/denis/CLionProjects/String_Lib/String.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/denis/CLionProjects/vec_lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.o -c /home/denis/CLionProjects/String_Lib/String.cpp

CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denis/CLionProjects/String_Lib/String.cpp > CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.i

CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denis/CLionProjects/String_Lib/String.cpp -o CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.s

# Object files for target vec_lib
vec_lib_OBJECTS = \
"CMakeFiles/vec_lib.dir/main.cpp.o" \
"CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.o"

# External object files for target vec_lib
vec_lib_EXTERNAL_OBJECTS =

vec_lib: CMakeFiles/vec_lib.dir/main.cpp.o
vec_lib: CMakeFiles/vec_lib.dir/home/denis/CLionProjects/String_Lib/String.cpp.o
vec_lib: CMakeFiles/vec_lib.dir/build.make
vec_lib: CMakeFiles/vec_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/denis/CLionProjects/vec_lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable vec_lib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vec_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vec_lib.dir/build: vec_lib

.PHONY : CMakeFiles/vec_lib.dir/build

CMakeFiles/vec_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vec_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vec_lib.dir/clean

CMakeFiles/vec_lib.dir/depend:
	cd /home/denis/CLionProjects/vec_lib/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/denis/CLionProjects/vec_lib /home/denis/CLionProjects/vec_lib /home/denis/CLionProjects/vec_lib/cmake-build-debug /home/denis/CLionProjects/vec_lib/cmake-build-debug /home/denis/CLionProjects/vec_lib/cmake-build-debug/CMakeFiles/vec_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vec_lib.dir/depend

