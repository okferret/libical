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
CMAKE_BINARY_DIR = /Users/okferret/Developer/Refactor/libical/build/macos_x86_64

# Include any dependencies generated for this target.
include src/test/CMakeFiles/icaltime_fuzz.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/test/CMakeFiles/icaltime_fuzz.dir/compiler_depend.make

# Include the progress variables for this target.
include src/test/CMakeFiles/icaltime_fuzz.dir/progress.make

# Include the compile flags for this target's objects.
include src/test/CMakeFiles/icaltime_fuzz.dir/flags.make

src/test/CMakeFiles/icaltime_fuzz.dir/codegen:
.PHONY : src/test/CMakeFiles/icaltime_fuzz.dir/codegen

src/test/CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.o: src/test/CMakeFiles/icaltime_fuzz.dir/flags.make
src/test/CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test/icaltime_fuzz.c
src/test/CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.o: src/test/CMakeFiles/icaltime_fuzz.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/test/CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/macos_x86_64/src/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/test/CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.o -MF CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.o.d -o CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test/icaltime_fuzz.c

src/test/CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/macos_x86_64/src/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test/icaltime_fuzz.c > CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.i

src/test/CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/macos_x86_64/src/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test/icaltime_fuzz.c -o CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.s

# Object files for target icaltime_fuzz
icaltime_fuzz_OBJECTS = \
"CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.o"

# External object files for target icaltime_fuzz
icaltime_fuzz_EXTERNAL_OBJECTS =

bin/icaltime_fuzz: src/test/CMakeFiles/icaltime_fuzz.dir/icaltime_fuzz.c.o
bin/icaltime_fuzz: src/test/CMakeFiles/icaltime_fuzz.dir/build.make
bin/icaltime_fuzz: lib/libicalvcal.3.0.20.dylib
bin/icaltime_fuzz: lib/libicalss_cxx.3.0.20.dylib
bin/icaltime_fuzz: lib/libicalss.3.0.20.dylib
bin/icaltime_fuzz: lib/libical_cxx.3.0.20.dylib
bin/icaltime_fuzz: lib/libical.3.0.20.dylib
bin/icaltime_fuzz: src/test/CMakeFiles/icaltime_fuzz.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../bin/icaltime_fuzz"
	cd /Users/okferret/Developer/Refactor/libical/build/macos_x86_64/src/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/icaltime_fuzz.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/test/CMakeFiles/icaltime_fuzz.dir/build: bin/icaltime_fuzz
.PHONY : src/test/CMakeFiles/icaltime_fuzz.dir/build

src/test/CMakeFiles/icaltime_fuzz.dir/clean:
	cd /Users/okferret/Developer/Refactor/libical/build/macos_x86_64/src/test && $(CMAKE_COMMAND) -P CMakeFiles/icaltime_fuzz.dir/cmake_clean.cmake
.PHONY : src/test/CMakeFiles/icaltime_fuzz.dir/clean

src/test/CMakeFiles/icaltime_fuzz.dir/depend:
	cd /Users/okferret/Developer/Refactor/libical/build/macos_x86_64 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/okferret/Developer/Refactor/libical/libical-3.0.20 /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/test /Users/okferret/Developer/Refactor/libical/build/macos_x86_64 /Users/okferret/Developer/Refactor/libical/build/macos_x86_64/src/test /Users/okferret/Developer/Refactor/libical/build/macos_x86_64/src/test/CMakeFiles/icaltime_fuzz.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/test/CMakeFiles/icaltime_fuzz.dir/depend

