# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/okferret/Developer/Refactor/libical/libical-3.0.20

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64

# Include any dependencies generated for this target.
include src/test/CMakeFiles/icalcomponent_fuzz2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/test/CMakeFiles/icalcomponent_fuzz2.dir/compiler_depend.make

# Include the progress variables for this target.
include src/test/CMakeFiles/icalcomponent_fuzz2.dir/progress.make

# Include the compile flags for this target's objects.
include src/test/CMakeFiles/icalcomponent_fuzz2.dir/flags.make

src/test/CMakeFiles/icalcomponent_fuzz2.dir/codegen:
.PHONY : src/test/CMakeFiles/icalcomponent_fuzz2.dir/codegen

src/test/CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.o: src/test/CMakeFiles/icalcomponent_fuzz2.dir/flags.make
src/test/CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test/icalcomponent_fuzz2.c
src/test/CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.o: src/test/CMakeFiles/icalcomponent_fuzz2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/test/CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64/src/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/test/CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.o -MF CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.o.d -o CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test/icalcomponent_fuzz2.c

src/test/CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64/src/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test/icalcomponent_fuzz2.c > CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.i

src/test/CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64/src/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test/icalcomponent_fuzz2.c -o CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.s

# Object files for target icalcomponent_fuzz2
icalcomponent_fuzz2_OBJECTS = \
"CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.o"

# External object files for target icalcomponent_fuzz2
icalcomponent_fuzz2_EXTERNAL_OBJECTS =

bin/icalcomponent_fuzz2: src/test/CMakeFiles/icalcomponent_fuzz2.dir/icalcomponent_fuzz2.c.o
bin/icalcomponent_fuzz2: src/test/CMakeFiles/icalcomponent_fuzz2.dir/build.make
bin/icalcomponent_fuzz2: lib/libicalvcal.3.0.20.dylib
bin/icalcomponent_fuzz2: lib/libicalss_cxx.3.0.20.dylib
bin/icalcomponent_fuzz2: lib/libicalss.3.0.20.dylib
bin/icalcomponent_fuzz2: lib/libical_cxx.3.0.20.dylib
bin/icalcomponent_fuzz2: lib/libical.3.0.20.dylib
bin/icalcomponent_fuzz2: src/test/CMakeFiles/icalcomponent_fuzz2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../bin/icalcomponent_fuzz2"
	cd /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64/src/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/icalcomponent_fuzz2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/test/CMakeFiles/icalcomponent_fuzz2.dir/build: bin/icalcomponent_fuzz2
.PHONY : src/test/CMakeFiles/icalcomponent_fuzz2.dir/build

src/test/CMakeFiles/icalcomponent_fuzz2.dir/clean:
	cd /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64/src/test && $(CMAKE_COMMAND) -P CMakeFiles/icalcomponent_fuzz2.dir/cmake_clean.cmake
.PHONY : src/test/CMakeFiles/icalcomponent_fuzz2.dir/clean

src/test/CMakeFiles/icalcomponent_fuzz2.dir/depend:
	cd /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/okferret/Developer/Refactor/libical/libical-3.0.20 /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64 /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64/src/test /Users/okferret/Developer/Refactor/libical/build/iphoneos_arm64/src/test/CMakeFiles/icalcomponent_fuzz2.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/test/CMakeFiles/icalcomponent_fuzz2.dir/depend

