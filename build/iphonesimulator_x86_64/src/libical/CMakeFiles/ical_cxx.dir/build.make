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
CMAKE_BINARY_DIR = /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64

# Include any dependencies generated for this target.
include src/libical/CMakeFiles/ical_cxx.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/libical/CMakeFiles/ical_cxx.dir/compiler_depend.make

# Include the progress variables for this target.
include src/libical/CMakeFiles/ical_cxx.dir/progress.make

# Include the compile flags for this target's objects.
include src/libical/CMakeFiles/ical_cxx.dir/flags.make

src/libical/CMakeFiles/ical_cxx.dir/codegen:
.PHONY : src/libical/CMakeFiles/ical_cxx.dir/codegen

src/libical/CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.o: src/libical/CMakeFiles/ical_cxx.dir/flags.make
src/libical/CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalparameter_cxx.cpp
src/libical/CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.o: src/libical/CMakeFiles/ical_cxx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/libical/CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/libical/CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.o -MF CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.o.d -o CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalparameter_cxx.cpp

src/libical/CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalparameter_cxx.cpp > CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.i

src/libical/CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalparameter_cxx.cpp -o CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.s

src/libical/CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.o: src/libical/CMakeFiles/ical_cxx.dir/flags.make
src/libical/CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalproperty_cxx.cpp
src/libical/CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.o: src/libical/CMakeFiles/ical_cxx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/libical/CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/libical/CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.o -MF CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.o.d -o CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalproperty_cxx.cpp

src/libical/CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalproperty_cxx.cpp > CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.i

src/libical/CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalproperty_cxx.cpp -o CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.s

src/libical/CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.o: src/libical/CMakeFiles/ical_cxx.dir/flags.make
src/libical/CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalvalue_cxx.cpp
src/libical/CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.o: src/libical/CMakeFiles/ical_cxx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/libical/CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/libical/CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.o -MF CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.o.d -o CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalvalue_cxx.cpp

src/libical/CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalvalue_cxx.cpp > CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.i

src/libical/CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalvalue_cxx.cpp -o CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.s

src/libical/CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.o: src/libical/CMakeFiles/ical_cxx.dir/flags.make
src/libical/CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/vcomponent_cxx.cpp
src/libical/CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.o: src/libical/CMakeFiles/ical_cxx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/libical/CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/libical/CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.o -MF CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.o.d -o CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/vcomponent_cxx.cpp

src/libical/CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/vcomponent_cxx.cpp > CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.i

src/libical/CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/vcomponent_cxx.cpp -o CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.s

# Object files for target ical_cxx
ical_cxx_OBJECTS = \
"CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.o" \
"CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.o" \
"CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.o" \
"CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.o"

# External object files for target ical_cxx
ical_cxx_EXTERNAL_OBJECTS =

lib/libical_cxx.3.0.20.dylib: src/libical/CMakeFiles/ical_cxx.dir/icalparameter_cxx.cpp.o
lib/libical_cxx.3.0.20.dylib: src/libical/CMakeFiles/ical_cxx.dir/icalproperty_cxx.cpp.o
lib/libical_cxx.3.0.20.dylib: src/libical/CMakeFiles/ical_cxx.dir/icalvalue_cxx.cpp.o
lib/libical_cxx.3.0.20.dylib: src/libical/CMakeFiles/ical_cxx.dir/vcomponent_cxx.cpp.o
lib/libical_cxx.3.0.20.dylib: src/libical/CMakeFiles/ical_cxx.dir/build.make
lib/libical_cxx.3.0.20.dylib: lib/libical.3.0.20.dylib
lib/libical_cxx.3.0.20.dylib: src/libical/CMakeFiles/ical_cxx.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library ../../lib/libical_cxx.dylib"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ical_cxx.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && $(CMAKE_COMMAND) -E cmake_symlink_library ../../lib/libical_cxx.3.0.20.dylib ../../lib/libical_cxx.3.dylib ../../lib/libical_cxx.dylib

lib/libical_cxx.3.dylib: lib/libical_cxx.3.0.20.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libical_cxx.3.dylib

lib/libical_cxx.dylib: lib/libical_cxx.3.0.20.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libical_cxx.dylib

# Rule to build all files generated by this target.
src/libical/CMakeFiles/ical_cxx.dir/build: lib/libical_cxx.dylib
.PHONY : src/libical/CMakeFiles/ical_cxx.dir/build

src/libical/CMakeFiles/ical_cxx.dir/clean:
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical && $(CMAKE_COMMAND) -P CMakeFiles/ical_cxx.dir/cmake_clean.cmake
.PHONY : src/libical/CMakeFiles/ical_cxx.dir/clean

src/libical/CMakeFiles/ical_cxx.dir/depend:
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/okferret/Developer/Refactor/libical/libical-3.0.20 /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64 /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_x86_64/src/libical/CMakeFiles/ical_cxx.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/libical/CMakeFiles/ical_cxx.dir/depend

