# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = /Users/meister/Development/cando/externals/src/cmake-2.8.5/Bootstrap.cmk/cmake

# The command to remove a file.
RM = /Users/meister/Development/cando/externals/src/cmake-2.8.5/Bootstrap.cmk/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/meister/Development/cando/externals/src/cmake-2.8.5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/meister/Development/cando/externals/src/cmake-2.8.5

# Include any dependencies generated for this target.
include Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/depend.make

# Include the progress variables for this target.
include Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/progress.make

# Include the compile flags for this target's objects.
include Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/flags.make

Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o: Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/flags.make
Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o: Tests/CMakeLib/run_compile_commands.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/meister/Development/cando/externals/src/cmake-2.8.5/CMakeFiles $(CMAKE_PROGRESS_1)
	@echo "Building CXX object Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o"
	cd /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o -c /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib/run_compile_commands.cxx

Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.i"
	cd /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib/run_compile_commands.cxx > CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.i

Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.s"
	cd /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib/run_compile_commands.cxx -o CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.s

Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o.requires:
.PHONY : Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o.requires

Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o.provides: Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o.requires
	$(MAKE) -f Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/build.make Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o.provides.build
.PHONY : Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o.provides

Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o.provides.build: Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o

# Object files for target runcompilecommands
runcompilecommands_OBJECTS = \
"CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o"

# External object files for target runcompilecommands
runcompilecommands_EXTERNAL_OBJECTS =

Tests/CMakeLib/runcompilecommands: Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o
Tests/CMakeLib/runcompilecommands: Source/libCMakeLib.a
Tests/CMakeLib/runcompilecommands: Source/kwsys/libcmsys.a
Tests/CMakeLib/runcompilecommands: Utilities/cmexpat/libcmexpat.a
Tests/CMakeLib/runcompilecommands: Utilities/cmlibarchive/libarchive/libcmlibarchive.a
Tests/CMakeLib/runcompilecommands: Utilities/cmbzip2/libcmbzip2.a
Tests/CMakeLib/runcompilecommands: Utilities/cmcompress/libcmcompress.a
Tests/CMakeLib/runcompilecommands: Utilities/cmcurl/libcmcurl.a
Tests/CMakeLib/runcompilecommands: Utilities/cmzlib/libcmzlib.a
Tests/CMakeLib/runcompilecommands: Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/build.make
Tests/CMakeLib/runcompilecommands: Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/link.txt
	@echo "Linking CXX executable runcompilecommands"
	cd /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runcompilecommands.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/build: Tests/CMakeLib/runcompilecommands
.PHONY : Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/build

Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/requires: Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/run_compile_commands.cxx.o.requires
.PHONY : Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/requires

Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/clean:
	cd /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib && $(CMAKE_COMMAND) -P CMakeFiles/runcompilecommands.dir/cmake_clean.cmake
.PHONY : Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/clean

Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/depend:
	cd /Users/meister/Development/cando/externals/src/cmake-2.8.5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/meister/Development/cando/externals/src/cmake-2.8.5 /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib /Users/meister/Development/cando/externals/src/cmake-2.8.5 /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib /Users/meister/Development/cando/externals/src/cmake-2.8.5/Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Tests/CMakeLib/CMakeFiles/runcompilecommands.dir/depend

