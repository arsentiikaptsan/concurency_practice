# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Task7LockFreeQueue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Task7LockFreeQueue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Task7LockFreeQueue.dir/flags.make

CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o: CMakeFiles/Task7LockFreeQueue.dir/flags.make
CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o -c /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/main.cpp

CMakeFiles/Task7LockFreeQueue.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Task7LockFreeQueue.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/main.cpp > CMakeFiles/Task7LockFreeQueue.dir/main.cpp.i

CMakeFiles/Task7LockFreeQueue.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Task7LockFreeQueue.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/main.cpp -o CMakeFiles/Task7LockFreeQueue.dir/main.cpp.s

CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o.requires

CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o.provides: CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Task7LockFreeQueue.dir/build.make CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o.provides

CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o.provides.build: CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o


# Object files for target Task7LockFreeQueue
Task7LockFreeQueue_OBJECTS = \
"CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o"

# External object files for target Task7LockFreeQueue
Task7LockFreeQueue_EXTERNAL_OBJECTS =

Task7LockFreeQueue: CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o
Task7LockFreeQueue: CMakeFiles/Task7LockFreeQueue.dir/build.make
Task7LockFreeQueue: CMakeFiles/Task7LockFreeQueue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Task7LockFreeQueue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Task7LockFreeQueue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Task7LockFreeQueue.dir/build: Task7LockFreeQueue

.PHONY : CMakeFiles/Task7LockFreeQueue.dir/build

CMakeFiles/Task7LockFreeQueue.dir/requires: CMakeFiles/Task7LockFreeQueue.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Task7LockFreeQueue.dir/requires

CMakeFiles/Task7LockFreeQueue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Task7LockFreeQueue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Task7LockFreeQueue.dir/clean

CMakeFiles/Task7LockFreeQueue.dir/depend:
	cd /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/cmake-build-debug /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/cmake-build-debug /Users/arsentii/Documents/MyFiles/Projects/C:C++/concurency_practice/Task7LockFreeQueue/cmake-build-debug/CMakeFiles/Task7LockFreeQueue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Task7LockFreeQueue.dir/depend

