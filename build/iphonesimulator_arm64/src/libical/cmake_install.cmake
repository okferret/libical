# Install script for directory: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/okferret/Developer/Refactor/libical/output/iphonesimulator_arm64")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/lib/libical.3.0.20.dylib"
    "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/lib/libical.3.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical.3.0.20.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical.3.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/lib/libical.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/lib/libical.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/lib/libical_cxx.3.0.20.dylib"
    "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/lib/libical_cxx.3.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical_cxx.3.0.20.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical_cxx.3.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/lib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/lib/libical_cxx.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/lib/libical_cxx.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical_cxx.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical_cxx.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libical_cxx.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libical" TYPE FILE FILES
    "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libical/ical.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalarray.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalattach.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalcomponent.h"
    "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libical/icalderivedproperty.h"
    "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libical/icalderivedparameter.h"
    "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libical/icalderivedvalue.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalduration.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalenums.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalerror.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icallangbind.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalmemory.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalmime.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalparameter.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalparser.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalperiod.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalproperty.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalrecur.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalrestriction.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icaltime.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icaltz-util.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icaltimezone.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icaltypes.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalvalue.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/libical_ical_export.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/pvl.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/sspm.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libical" TYPE FILE FILES
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalparameter_cxx.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalproperty_cxx.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icalvalue_cxx.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/icptrholder_cxx.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libical/vcomponent_cxx.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/okferret/Developer/Refactor/libical/build/iphonesimulator_arm64/src/libical/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
