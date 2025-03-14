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
CMAKE_BINARY_DIR = /Users/okferret/Developer/Refactor/libical/build/macos_arm64

# Utility rule file for icalss-header.

# Include any custom commands dependencies for this target.
include src/libicalss/CMakeFiles/icalss-header.dir/compiler_depend.make

# Include the progress variables for this target.
include src/libicalss/CMakeFiles/icalss-header.dir/progress.make

src/libicalss/CMakeFiles/icalss-header: src/libicalss/icalss.h

src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/libical_icalss_export.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcalendar.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcalendar.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalclassify.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalclassify.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcluster.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcluster.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalclusterimpl.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalgauge.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalgauge.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalgaugeimpl.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icaldirset.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icaldirset.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icaldirsetimpl.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalfileset.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalfileset.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalfilesetimpl.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalset.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalset.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalssyacc.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalspanlist.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalspanlist.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalmessage.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalmessage.h
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalsslexer.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalssyacc.c
src/libicalss/icalss.h: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalss_file.cmake
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/okferret/Developer/Refactor/libical/build/macos_arm64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating icalss.h"
	cd /Users/okferret/Developer/Refactor/libical/build/macos_arm64/src/libicalss && /usr/local/bin/cmake -DTOPS:FILEPATH=/Users/okferret/Developer/Refactor/libical/libical-3.0.20 -DTOPB:FILEPATH=/Users/okferret/Developer/Refactor/libical/build/macos_arm64 -DICAL_FILE_H_FILE:FILEPATH=/Users/okferret/Developer/Refactor/libical/build/macos_arm64/src/libicalss/icalss.h -DBDB_FOUND= -P /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalss_file.cmake

src/libicalss/CMakeFiles/icalss-header.dir/codegen:
.PHONY : src/libicalss/CMakeFiles/icalss-header.dir/codegen

icalss-header: src/libicalss/CMakeFiles/icalss-header
icalss-header: src/libicalss/icalss.h
icalss-header: src/libicalss/CMakeFiles/icalss-header.dir/build.make
.PHONY : icalss-header

# Rule to build all files generated by this target.
src/libicalss/CMakeFiles/icalss-header.dir/build: icalss-header
.PHONY : src/libicalss/CMakeFiles/icalss-header.dir/build

src/libicalss/CMakeFiles/icalss-header.dir/clean:
	cd /Users/okferret/Developer/Refactor/libical/build/macos_arm64/src/libicalss && $(CMAKE_COMMAND) -P CMakeFiles/icalss-header.dir/cmake_clean.cmake
.PHONY : src/libicalss/CMakeFiles/icalss-header.dir/clean

src/libicalss/CMakeFiles/icalss-header.dir/depend:
	cd /Users/okferret/Developer/Refactor/libical/build/macos_arm64 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/okferret/Developer/Refactor/libical/libical-3.0.20 /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss /Users/okferret/Developer/Refactor/libical/build/macos_arm64 /Users/okferret/Developer/Refactor/libical/build/macos_arm64/src/libicalss /Users/okferret/Developer/Refactor/libical/build/macos_arm64/src/libicalss/CMakeFiles/icalss-header.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/libicalss/CMakeFiles/icalss-header.dir/depend

