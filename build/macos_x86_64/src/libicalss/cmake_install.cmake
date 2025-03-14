# Install script for directory: /Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/okferret/Developer/Refactor/libical/output/macos_x86_64")
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
    "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib/libicalss.3.0.20.dylib"
    "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib/libicalss.3.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss.3.0.20.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss.3.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib/libicalss.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib/libicalss.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib/libicalss_cxx.3.0.20.dylib"
    "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib/libicalss_cxx.3.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss_cxx.3.0.20.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss_cxx.3.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib/libicalss_cxx.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/lib/libicalss_cxx.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss_cxx.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss_cxx.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicalss_cxx.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libical" TYPE FILE FILES
    "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/src/libicalss/icalss.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcalendar.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalclassify.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalcluster.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icaldirset.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icaldirsetimpl.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalfileset.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalfilesetimpl.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalgauge.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalgaugeimpl.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalmessage.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalset.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalspanlist.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalssyacc.h"
    "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/libical_icalss_export.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libical" TYPE FILE FILES "/Users/okferret/Developer/Refactor/libical/libical-3.0.20/src/libicalss/icalspanlist_cxx.h")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/okferret/Developer/Refactor/libical/build/macos_x86_64/src/libicalss/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
