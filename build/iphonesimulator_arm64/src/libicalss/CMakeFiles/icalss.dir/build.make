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
CMAKE_BINARY_DIR = /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64

# Include any dependencies generated for this target.
include src/libicalss/CMakeFiles/icalss.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/libicalss/CMakeFiles/icalss.dir/compiler_depend.make

# Include the progress variables for this target.
include src/libicalss/CMakeFiles/icalss.dir/progress.make

# Include the compile flags for this target's objects.
include src/libicalss/CMakeFiles/icalss.dir/flags.make

src/libicalss/CMakeFiles/icalss.dir/codegen:
.PHONY : src/libicalss/CMakeFiles/icalss.dir/codegen

src/libicalss/CMakeFiles/icalss.dir/icalcalendar.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalcalendar.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcalendar.c
src/libicalss/CMakeFiles/icalss.dir/icalcalendar.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalcalendar.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalcalendar.c.o -MF CMakeFiles/icalss.dir/icalcalendar.c.o.d -o CMakeFiles/icalss.dir/icalcalendar.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcalendar.c

src/libicalss/CMakeFiles/icalss.dir/icalcalendar.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalcalendar.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcalendar.c > CMakeFiles/icalss.dir/icalcalendar.c.i

src/libicalss/CMakeFiles/icalss.dir/icalcalendar.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalcalendar.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcalendar.c -o CMakeFiles/icalss.dir/icalcalendar.c.s

src/libicalss/CMakeFiles/icalss.dir/icalclassify.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalclassify.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalclassify.c
src/libicalss/CMakeFiles/icalss.dir/icalclassify.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalclassify.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalclassify.c.o -MF CMakeFiles/icalss.dir/icalclassify.c.o.d -o CMakeFiles/icalss.dir/icalclassify.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalclassify.c

src/libicalss/CMakeFiles/icalss.dir/icalclassify.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalclassify.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalclassify.c > CMakeFiles/icalss.dir/icalclassify.c.i

src/libicalss/CMakeFiles/icalss.dir/icalclassify.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalclassify.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalclassify.c -o CMakeFiles/icalss.dir/icalclassify.c.s

src/libicalss/CMakeFiles/icalss.dir/icalcluster.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalcluster.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcluster.c
src/libicalss/CMakeFiles/icalss.dir/icalcluster.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalcluster.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalcluster.c.o -MF CMakeFiles/icalss.dir/icalcluster.c.o.d -o CMakeFiles/icalss.dir/icalcluster.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcluster.c

src/libicalss/CMakeFiles/icalss.dir/icalcluster.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalcluster.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcluster.c > CMakeFiles/icalss.dir/icalcluster.c.i

src/libicalss/CMakeFiles/icalss.dir/icalcluster.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalcluster.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcluster.c -o CMakeFiles/icalss.dir/icalcluster.c.s

src/libicalss/CMakeFiles/icalss.dir/icalgauge.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalgauge.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalgauge.c
src/libicalss/CMakeFiles/icalss.dir/icalgauge.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalgauge.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalgauge.c.o -MF CMakeFiles/icalss.dir/icalgauge.c.o.d -o CMakeFiles/icalss.dir/icalgauge.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalgauge.c

src/libicalss/CMakeFiles/icalss.dir/icalgauge.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalgauge.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalgauge.c > CMakeFiles/icalss.dir/icalgauge.c.i

src/libicalss/CMakeFiles/icalss.dir/icalgauge.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalgauge.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalgauge.c -o CMakeFiles/icalss.dir/icalgauge.c.s

src/libicalss/CMakeFiles/icalss.dir/icaldirset.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icaldirset.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icaldirset.c
src/libicalss/CMakeFiles/icalss.dir/icaldirset.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/libicalss/CMakeFiles/icalss.dir/icaldirset.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icaldirset.c.o -MF CMakeFiles/icalss.dir/icaldirset.c.o.d -o CMakeFiles/icalss.dir/icaldirset.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icaldirset.c

src/libicalss/CMakeFiles/icalss.dir/icaldirset.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icaldirset.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icaldirset.c > CMakeFiles/icalss.dir/icaldirset.c.i

src/libicalss/CMakeFiles/icalss.dir/icaldirset.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icaldirset.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icaldirset.c -o CMakeFiles/icalss.dir/icaldirset.c.s

src/libicalss/CMakeFiles/icalss.dir/icalfileset.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalfileset.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalfileset.c
src/libicalss/CMakeFiles/icalss.dir/icalfileset.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalfileset.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalfileset.c.o -MF CMakeFiles/icalss.dir/icalfileset.c.o.d -o CMakeFiles/icalss.dir/icalfileset.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalfileset.c

src/libicalss/CMakeFiles/icalss.dir/icalfileset.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalfileset.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalfileset.c > CMakeFiles/icalss.dir/icalfileset.c.i

src/libicalss/CMakeFiles/icalss.dir/icalfileset.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalfileset.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalfileset.c -o CMakeFiles/icalss.dir/icalfileset.c.s

src/libicalss/CMakeFiles/icalss.dir/icalset.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalset.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalset.c
src/libicalss/CMakeFiles/icalss.dir/icalset.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalset.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalset.c.o -MF CMakeFiles/icalss.dir/icalset.c.o.d -o CMakeFiles/icalss.dir/icalset.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalset.c

src/libicalss/CMakeFiles/icalss.dir/icalset.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalset.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalset.c > CMakeFiles/icalss.dir/icalset.c.i

src/libicalss/CMakeFiles/icalss.dir/icalset.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalset.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalset.c -o CMakeFiles/icalss.dir/icalset.c.s

src/libicalss/CMakeFiles/icalss.dir/icalspanlist.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalspanlist.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalspanlist.c
src/libicalss/CMakeFiles/icalss.dir/icalspanlist.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalspanlist.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalspanlist.c.o -MF CMakeFiles/icalss.dir/icalspanlist.c.o.d -o CMakeFiles/icalss.dir/icalspanlist.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalspanlist.c

src/libicalss/CMakeFiles/icalss.dir/icalspanlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalspanlist.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalspanlist.c > CMakeFiles/icalss.dir/icalspanlist.c.i

src/libicalss/CMakeFiles/icalss.dir/icalspanlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalspanlist.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalspanlist.c -o CMakeFiles/icalss.dir/icalspanlist.c.s

src/libicalss/CMakeFiles/icalss.dir/icalmessage.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalmessage.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalmessage.c
src/libicalss/CMakeFiles/icalss.dir/icalmessage.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalmessage.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalmessage.c.o -MF CMakeFiles/icalss.dir/icalmessage.c.o.d -o CMakeFiles/icalss.dir/icalmessage.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalmessage.c

src/libicalss/CMakeFiles/icalss.dir/icalmessage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalmessage.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalmessage.c > CMakeFiles/icalss.dir/icalmessage.c.i

src/libicalss/CMakeFiles/icalss.dir/icalmessage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalmessage.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalmessage.c -o CMakeFiles/icalss.dir/icalmessage.c.s

src/libicalss/CMakeFiles/icalss.dir/icalsslexer.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalsslexer.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalsslexer.c
src/libicalss/CMakeFiles/icalss.dir/icalsslexer.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalsslexer.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalsslexer.c.o -MF CMakeFiles/icalss.dir/icalsslexer.c.o.d -o CMakeFiles/icalss.dir/icalsslexer.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalsslexer.c

src/libicalss/CMakeFiles/icalss.dir/icalsslexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalsslexer.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalsslexer.c > CMakeFiles/icalss.dir/icalsslexer.c.i

src/libicalss/CMakeFiles/icalss.dir/icalsslexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalsslexer.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalsslexer.c -o CMakeFiles/icalss.dir/icalsslexer.c.s

src/libicalss/CMakeFiles/icalss.dir/icalssyacc.c.o: src/libicalss/CMakeFiles/icalss.dir/flags.make
src/libicalss/CMakeFiles/icalss.dir/icalssyacc.c.o: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalssyacc.c
src/libicalss/CMakeFiles/icalss.dir/icalssyacc.c.o: src/libicalss/CMakeFiles/icalss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object src/libicalss/CMakeFiles/icalss.dir/icalssyacc.c.o"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libicalss/CMakeFiles/icalss.dir/icalssyacc.c.o -MF CMakeFiles/icalss.dir/icalssyacc.c.o.d -o CMakeFiles/icalss.dir/icalssyacc.c.o -c /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalssyacc.c

src/libicalss/CMakeFiles/icalss.dir/icalssyacc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icalss.dir/icalssyacc.c.i"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalssyacc.c > CMakeFiles/icalss.dir/icalssyacc.c.i

src/libicalss/CMakeFiles/icalss.dir/icalssyacc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icalss.dir/icalssyacc.c.s"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalssyacc.c -o CMakeFiles/icalss.dir/icalssyacc.c.s

# Object files for target icalss
icalss_OBJECTS = \
"CMakeFiles/icalss.dir/icalcalendar.c.o" \
"CMakeFiles/icalss.dir/icalclassify.c.o" \
"CMakeFiles/icalss.dir/icalcluster.c.o" \
"CMakeFiles/icalss.dir/icalgauge.c.o" \
"CMakeFiles/icalss.dir/icaldirset.c.o" \
"CMakeFiles/icalss.dir/icalfileset.c.o" \
"CMakeFiles/icalss.dir/icalset.c.o" \
"CMakeFiles/icalss.dir/icalspanlist.c.o" \
"CMakeFiles/icalss.dir/icalmessage.c.o" \
"CMakeFiles/icalss.dir/icalsslexer.c.o" \
"CMakeFiles/icalss.dir/icalssyacc.c.o"

# External object files for target icalss
icalss_EXTERNAL_OBJECTS =

lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalcalendar.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalclassify.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalcluster.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalgauge.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icaldirset.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalfileset.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalset.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalspanlist.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalmessage.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalsslexer.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/icalssyacc.c.o
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/build.make
lib/libicalss.3.0.20.dylib: lib/libical.3.0.20.dylib
lib/libicalss.3.0.20.dylib: src/libicalss/CMakeFiles/icalss.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking C shared library ../../lib/libicalss.dylib"
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/icalss.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && $(CMAKE_COMMAND) -E cmake_symlink_library ../../lib/libicalss.3.0.20.dylib ../../lib/libicalss.3.dylib ../../lib/libicalss.dylib

lib/libicalss.3.dylib: lib/libicalss.3.0.20.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libicalss.3.dylib

lib/libicalss.dylib: lib/libicalss.3.0.20.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libicalss.dylib

# Rule to build all files generated by this target.
src/libicalss/CMakeFiles/icalss.dir/build: lib/libicalss.dylib
.PHONY : src/libicalss/CMakeFiles/icalss.dir/build

src/libicalss/CMakeFiles/icalss.dir/clean:
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss && $(CMAKE_COMMAND) -P CMakeFiles/icalss.dir/cmake_clean.cmake
.PHONY : src/libicalss/CMakeFiles/icalss.dir/clean

src/libicalss/CMakeFiles/icalss.dir/depend:
	cd /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/okferret/Developer/Refactor/libical/libical-3.0.20 /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64 /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss /Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libicalss/CMakeFiles/icalss.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/libicalss/CMakeFiles/icalss.dir/depend

