# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/blaclegi/Dev/geneengine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/blaclegi/Dev/geneengine/bin/Default

# Include any dependencies generated for this target.
include CMakeFiles/Gene.Sandbox.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Gene.Sandbox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Gene.Sandbox.dir/flags.make

CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o: CMakeFiles/Gene.Sandbox.dir/flags.make
CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o: ../../Gene.Sandbox/Source/Main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/blaclegi/Dev/geneengine/bin/Default/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o -c /home/blaclegi/Dev/geneengine/Gene.Sandbox/Source/Main.cc

CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/blaclegi/Dev/geneengine/Gene.Sandbox/Source/Main.cc > CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.i

CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/blaclegi/Dev/geneengine/Gene.Sandbox/Source/Main.cc -o CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.s

CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o.requires:
.PHONY : CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o.requires

CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o.provides: CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o.requires
	$(MAKE) -f CMakeFiles/Gene.Sandbox.dir/build.make CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o.provides.build
.PHONY : CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o.provides

CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o.provides.build: CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o

# Object files for target Gene.Sandbox
Gene_Sandbox_OBJECTS = \
"CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o"

# External object files for target Gene.Sandbox
Gene_Sandbox_EXTERNAL_OBJECTS =

Gene.Sandbox: CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o
Gene.Sandbox: CMakeFiles/Gene.Sandbox.dir/build.make
Gene.Sandbox: libGene.so
Gene.Sandbox: CMakeFiles/Gene.Sandbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Gene.Sandbox"
	rm -r /home/blaclegi/Dev/geneengine/bin/Default/Data
	cp -r ../Gene.Sandbox/Data /home/blaclegi/Dev/geneengine/bin/Default
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Gene.Sandbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Gene.Sandbox.dir/build: Gene.Sandbox
.PHONY : CMakeFiles/Gene.Sandbox.dir/build

CMakeFiles/Gene.Sandbox.dir/requires: CMakeFiles/Gene.Sandbox.dir/Gene.Sandbox/Source/Main.cc.o.requires
.PHONY : CMakeFiles/Gene.Sandbox.dir/requires

CMakeFiles/Gene.Sandbox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Gene.Sandbox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Gene.Sandbox.dir/clean

CMakeFiles/Gene.Sandbox.dir/depend:
	cd /home/blaclegi/Dev/geneengine/bin/Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/blaclegi/Dev/geneengine /home/blaclegi/Dev/geneengine /home/blaclegi/Dev/geneengine/bin/Default /home/blaclegi/Dev/geneengine/bin/Default /home/blaclegi/Dev/geneengine/bin/Default/CMakeFiles/Gene.Sandbox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Gene.Sandbox.dir/depend

