#
#Chiika Api CMAKE Configuration
#
#You shouldn't edit this file unless you really have to
#
#
# Copyright 2015 Alperen Gezer
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# To build this project,you will need [Cmake](https://cmake.org/)

# ```
# git clone https://github.com/arkenthera/ChiikaApi.git
# cd ChiikaApi
# mkdir _build
# cd _build
# cmake ..
# ```

# Recomended Cmake settings

# ```
# BUILD_CURL_EXE uncheck
# BUILD_CURL_TESTS uncheck
# BUILD_STATIC_LIBS uncheck
# JSON_CPP_WITH_TESTS uncheck
# If you're on Windows,disable OpenSSL because it conflicts with WinSSl (SChannel)
#```
#Minimum version of CMAKE
cmake_minimum_required(VERSION 2.8.12.2)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

PROJECT(Chiika)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Determine the platform.
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
  set(OS_MACOSX 1)
  set(OS_POSIX 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(OS_LINUX 1)
  set(OS_POSIX 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  set(OS_WINDOWS 1)
endif()

#Determine architecture
if(NOT DEFINED PROJECT_ARCH)
  if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PROJECT_ARCH "x86_64")
  else()
    set(PROJECT_ARCH "x86")
  endif()

  if(OS_MACOSX)
    # PROJECT_ARCH should be specified on Mac OS X.
    message(WARNING "No PROJECT_ARCH value specified, using ${PROJECT_ARCH}")
  endif()
endif()

#Helper macros
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/Modules")
set(CHIIKA_ROOT ${PROJECT_SOURCE_DIR})
include("macros")

# Source include directory.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#
# Linux configuration.
#

if(OS_LINUX)
  # Platform-specific compiler/linker flags.
  set(CHI_LIBTYPE                 SHARED)
  # -fno-strict-aliasing            = Avoid assumptions regarding non-aliasing of objects of different types
  # -fPIC                           = Generate position-independent code for shared libraries
  # -fstack-protector               = Protect some vulnerable functions from stack-smashing (security feature)
  # -funwind-tables                 = Support stack unwinding for backtrace()
  # -fvisibility=hidden             = Give hidden visibility to declarations that are not explicitly marked as visible
  # --param=ssp-buffer-size=4       = Set the minimum buffer size protected by SSP (security feature, related to stack-protector)
  # -pipe                           = Use pipes rather than temporary files for communication between build stages
  # -pthread                        = Use the pthread library
  # -Wall                           = Enable all warnings
  # -Werror                         = Treat warnings as errors
  # -Wno-missing-field-initializers = Don't warn about missing field initializers
  # -Wno-unused-parameter           = Don't warn about unused parameters
  set(CHI_COMPILER_FLAGS          "-pipe -pthread -Wall -Werror -Wno-missing-field-initializers -Wno-unused-parameter")
  # -std=c99                        = Use the C99 language standard
  set(CHI_C_COMPILER_FLAGS        "-std=c99")
  # -fno-exceptions                 = Disable exceptions
  # -fno-rtti                       = Disable real-time type information
  # -fno-threadsafe-statics         = Don't generate thread-safe statics
  # -fvisibility-inlines-hidden     = Give hidden visibility to inlined class member functions
  # -std=gnu++11                    = Use the C++11 language standard including GNU extensions
  # -Wsign-compare                  = Warn about mixed signed/unsigned type comparisons
  set(CHI_CXX_COMPILER_FLAGS      "-fno-rtti -fno-threadsafe-statics -fvisibility-inlines-hidden -std=gnu++11 -Wsign-compare")
  # -O0                             = Disable optimizations
  # -g                              = Generate debug information
  set(CHI_COMPILER_FLAGS_DEBUG    "-O0 -g")
  # -O2                             = Optimize for maximum speed
  # -fdata-sections                 = Enable linker optimizations to improve locality of reference for data sections
  # -ffunction-sections             = Enable linker optimizations to improve locality of reference for function sections
  # -fno-ident                      = Ignore the #ident directive
  # -DNDEBUG                        = Not a debug build
  # -U_FORTIFY_SOURCE               = Undefine _FORTIFY_SOURCE in case it was previously defined
  # -D_FORTIFY_SOURCE=2             = Add memory and string function protection (security feature, related to stack-protector)
  set(CHI_COMPILER_FLAGS_RELEASE  "-O2 -fdata-sections -ffunction-sections -fno-ident -DNDEBUG -U_FORTIFY_SOURCE")
  # -Wl,--disable-new-dtags         = Don't generate new-style dynamic tags in ELF
  # -Wl,--fatal-warnings            = Treat warnings as errors
  # -Wl,-rpath,.                    = Set rpath so that libraries can be placed next to the executable
  # -Wl,-z,noexecstack              = Mark the stack as non-executable (security feature)
  # -Wl,-z,now                      = Resolve symbols on program start instead of on first use (security feature)
  # -Wl,-z,relro                    = Mark relocation sections as read-only (security feature)
  set(CHI_LINKER_FLAGS            "-fPIC -pthread -Wl,--disable-new-dtags -Wl,--fatal-warnings -Wl,-rpath,. -Wl,-z,noexecstack -Wl,-z,now -Wl,-z,relro")
  # -Wl,-O1                         = Enable linker optimizations
  # -Wl,--as-needed                 = Only link libraries that export symbols used by the binary
  # -Wl,--gc-sections               = Remove unused code resulting from -fdata-sections and -function-sections
  set(CHI_LINKER_FLAGS_RELEASE    "-Wl,-O1 -Wl,--as-needed -Wl,--gc-sections")

  include(CheckCCompilerFlag)
  include(CheckCXXCompilerFlag)

  # -Wno-unused-local-typedefs      = Don't warn about unused local typedefs
  CHECK_C_COMPILER_FLAG(-Wno-unused-local-typedefs COMPILER_SUPPORTS_NO_UNUSED_LOCAL_TYPEDEFS)
  if(COMPILER_SUPPORTS_NO_UNUSED_LOCAL_TYPEDEFS)
    set(CEF_C_COMPILER_FLAGS      "${CEF_C_COMPILER_FLAGS} -Wno-unused-local-typedefs")
  endif()

  # -Wno-literal-suffix             = Don't warn about invalid suffixes on literals
  CHECK_CXX_COMPILER_FLAG(-Wno-literal-suffix COMPILER_SUPPORTS_NO_LITERAL_SUFFIX)
  if(COMPILER_SUPPORTS_NO_LITERAL_SUFFIX)
    set(CEF_CXX_COMPILER_FLAGS    "${CEF_CXX_COMPILER_FLAGS} -Wno-literal-suffix")
  endif()

  # -Wno-narrowing                  = Don't warn about type narrowing
  CHECK_CXX_COMPILER_FLAG(-Wno-narrowing COMPILER_SUPPORTS_NO_NARROWING)
  if(COMPILER_SUPPORTS_NO_NARROWING)
    set(CEF_CXX_COMPILER_FLAGS    "${CEF_CXX_COMPILER_FLAGS} -Wno-narrowing")
  endif()

  if(PROJECT_ARCH STREQUAL "x86_64")
    # 64-bit architecture.
    set(CHI_COMPILER_FLAGS        "${CEF_COMPILER_FLAGS} -m64 -march=x86-64")
    set(CHI_LINKER_FLAGS          "${CEF_LINKER_FLAGS} -m64")
  elseif(PROJECT_ARCH STREQUAL "x86")
    # 32-bit architecture.
    set(CHI_COMPILER_FLAGS        "${CEF_COMPILER_FLAGS} -msse2 -mfpmath=sse -mmmx -m32")
    set(CHI_LINKER_FLAGS          "${CEF_LINKER_FLAGS} -m32")
  endif()
endif()

#
# Mac OS X configuration.
#

if(OS_MACOSX)
  # Platform-specific compiler/linker flags.
  # See also SET_XCODE_TARGET_PROPERTIES in macros.cmake.
  set(CHI_LIBTYPE                 SHARED)
  # -fno-strict-aliasing            = Avoid assumptions regarding non-aliasing of objects of different types
  # -fstack-protector               = Protect some vulnerable functions from stack-smashing (security feature)
  # -funwind-tables                 = Support stack unwinding for backtrace()
  # -fvisibility=hidden             = Give hidden visibility to declarations that are not explicitly marked as visible
  # -Wall                           = Enable all warnings
  # -Wendif-labels                  = Warn whenever an #else or an #endif is followed by text
  # -Werror                         = Treat warnings as errors
  # -Wextra                         = Enable additional warnings
  # -Wnewline-eof                   = Warn about no newline at end of file
  # -Wno-missing-field-initializers = Don't warn about missing field initializers
  # -Wno-unused-parameter           = Don't warn about unused parameters
  set(CHI_COMPILER_FLAGS          "-fno-strict-aliasing -fstack-protector -funwind-tables -fvisibility=hidden -Wall -Wendif-labels -Werror -Wextra -Wnewline-eof -Wno-missing-field-initializers -Wno-unused-parameter")
  # -std=c99                        = Use the C99 language standard
  set(CHI_C_COMPILER_FLAGS        "-std=c99")
  # -fno-exceptions                 = Disable exceptions
  # -fno-rtti                       = Disable real-time type information
  # -fno-threadsafe-statics         = Don't generate thread-safe statics
  # -fobjc-call-cxx-cdtors          = Call the constructor/destructor of C++ instance variables in ObjC objects
  # -fvisibility-inlines-hidden     = Give hidden visibility to inlined class member functions
  # -std=gnu++11                    = Use the C++11 language standard including GNU extensions
  # -Wno-narrowing                  = Don't warn about type narrowing
  # -Wsign-compare                  = Warn about mixed signed/unsigned type comparisons
  set(CHI_CXX_COMPILER_FLAGS      "-fno-rtti -fno-threadsafe-statics -fobjc-call-cxx-cdtors -fvisibility-inlines-hidden -std=gnu++11 -Wno-narrowing -Wsign-compare")
  # -O0                             = Disable optimizations
  # -g                              = Generate debug information
  set(CHI_COMPILER_FLAGS_DEBUG    "-O0 -g")
  # -O3                             = Optimize for maximum speed plus a few extras
  set(CHI_COMPILER_FLAGS_RELEASE  "-O3")
  # -Wl,-search_paths_first         = Search for static or shared library versions in the same pass
  # -Wl,-ObjC                       = Support creation of creation of ObjC static libraries
  # -Wl,-pie                        = Generate position-independent code suitable for executables only
  set(CHI_LINKER_FLAGS            "-Wl,-search_paths_first -Wl,-ObjC -Wl,-pie")
  # -Wl,-dead_strip                 = Strip dead code
  set(CHI_LINKER_FLAGS_RELEASE    "-Wl,-dead_strip")

  # Standard libraries.
  set(CHI_STANDARD_LIBS "-lpthread")

  # Find the newest available base SDK.
  execute_process(COMMAND xcode-select --print-path OUTPUT_VARIABLE XCODE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
  foreach(OS_VERSION 10.10 10.9 10.8 10.7)
    set(SDK "${XCODE_PATH}/Platforms/MacOSX.platform/Developer/SDKs/MacOSX${OS_VERSION}.sdk")
    if(NOT "${CMAKE_OSX_SYSROOT}" AND EXISTS "${SDK}" AND IS_DIRECTORY "${SDK}")
      set(CMAKE_OSX_SYSROOT ${SDK})
    endif()
  endforeach()

  # Target SDK.
  set(CHI_TARGET_SDK               "10.6")
  set(CHI_COMPILER_FLAGS           "${CEF_COMPILER_FLAGS} -mmacosx-version-min=${CEF_TARGET_SDK}")
  set(CMAKE_OSX_DEPLOYMENT_TARGET  ${CHI_TARGET_SDK})

  # Target architecture.
  if(PROJECT_ARCH STREQUAL "x86_64")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
  else()
    set(CMAKE_OSX_ARCHITECTURES "i386")
  endif()
endif()

#
# Windows configuration.
#

if(OS_WINDOWS)
  # Platform-specific compiler/linker flags.
  set(CHI_LIBTYPE                 SHARED)
  add_definitions(-DChiikaApiShared)
  # /MP                   = Multiprocess compilation
  # /Gy                   = Enable function-level linking
  # /GR-                  = Disable run-time type information
  # /Zi                   = Enable program database
  # /W4                   = Warning level 4
  # /WX                   = Treat warnings as errors
  # /wd"4100"             = Ignore "unreferenced formal parameter" warning
  # /wd"4127"             = Ignore "conditional expression is constant" warning
  # /wd"4244"             = Ignore "conversion possible loss of data" warning
  # /wd"4512"             = Ignore "assignment operator could not be generated" warning
  # /wd"4701"             = Ignore "potentially uninitialized local variable" warning
  # /wd"4702"             = Ignore "unreachable code" warning
  # /wd"4996"             = Ignore "function or variable may be unsafe" warning
  set(CHI_COMPILER_FLAGS          "/EHsc /Zi /GF /Gm /W4 /wd\"4100\" /wd\"4127\" /wd\"4244\" /wd\"4512\" /wd\"4701\" /wd\"4702\" /wd\"4996\" /wd\"4251\" /wd\"4275\"")
  # /MTd                  = Multithreaded debug runtime
  # /Od                   = Disable optimizations
  # /RTC1                 = Enable basic run-time checks
  set(CHI_COMPILER_FLAGS_DEBUG    "/MTd /RTC1 /Od")
  # /MT                   = Multithreaded release runtime
  # /O2                   = Optimize for maximum speed
  # /Ob2                  = Inline any suitable function
  # /GF                   = Enable string pooling
  # /D NDEBUG /D _NDEBUG  = Not a debug build
  set(CHI_COMPILER_FLAGS_RELEASE  "/MT /O2 /Ob2 /GF /DEBUG")
  # /DEBUG                = Generate debug information
  set(CHI_LINKER_FLAGS_DEBUG      "/DEBUG")
  # /MANIFEST:NO          = No default manifest (see ADD_WINDOWS_MANIFEST macro usage)
  set(CHI_EXE_LINKER_FLAGS        "/MANIFEST:NO")

  # Standard definitions
  # -DWIN32 -D_WIN32 -D_WINDOWS           = Windows platform
  # -DUNICODE -D_UNICODE                  = Unicode build
  # -DWINVER=0x0602 -D_WIN32_WINNT=0x602  = Targeting Windows 8
  # -DNOMINMAX                            = Use the standard's templated min/max
  # -DWIN32_LEAN_AND_MEAN                 = Exclude less common API declarations
  # -D_HAS_EXCEPTIONS=0                   = Disable exceptions
  add_definitions(-DWIN32 -D_WIN32 -D_WINDOWS -DUNICODE -D_UNICODE
                   -D_WIN32_WINNT=0x602 -DNOMINMAX)
endif()

set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE)
set(BUILD_CURL_TESTS OFF CACHE BOOL "" FORCE)

set(CMAKE_USE_OPENSSL OFF CACHE BOOL "" FORCE)
set(ENABLE_MANUAL OFF CACHE BOOL "" FORCE)
set(LOG4CPLUS_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(LOG4CPLUS_BUILD_LOGGINGSERVER OFF CACHE BOOL "" FORCE)
set(UNICODE_DEFAULT OFF CACHE BOOL "" FORCE)
set(WITH_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(LOG4CPLUS_ENABLE_DECORATED_LIBRARY_NAME OFF CACHE BOOL "" FORCE)
set(UNICODE OFF CACHE BOOL "" FORCE)


if(OS_WINDOWS)
  set(ENABLE_UNIX_SOCKETS OFF CACHE BOOL "" FORCE)
  set(LIB_EAY_RELEASE "")
endif()

set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "" FORCE)
set(JSONCPP_WITH_TESTS OFF CACHE BOOL "" FORCE)

option(WITH_SYSTEM_BOOST "Build with system Boost" OFF)

fb_check_boost()



set(CMAKE_C_FLAGS                     "${CHI_COMPILER_FLAGS} ${CHI_C_COMPILER_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG               "${CHI_COMPILER_FLAGS_DEBUG} ${CHI_C_COMPILER_FLAGS_DEBUG}")
set(CMAKE_C_FLAGS_RELEASE             "${CHI_COMPILER_FLAGS_RELEASE} ${CHI_C_COMPILER_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS                   "${CHI_COMPILER_FLAGS} ${CHI_CXX_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG             "${CHI_COMPILER_FLAGS_DEBUG} ${CHI_CXX_COMPILER_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE           "${CHI_COMPILER_FLAGS_RELEASE} ${CHI_CXX_COMPILER_FLAGS_RELEASE}")
set(CMAKE_EXE_LINKER_FLAGS            "${CHI_LINKER_FLAGS} ${CHI_EXE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG      "${CHI_LINKER_FLAGS_DEBUG} ${CHI_EXE_LINKER_FLAGS_DEBUG}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE    "${CHI_LINKER_FLAGS_RELEASE} ${CHI_EXE_LINKER_FLAGS_RELEASE}")
set(CMAKE_SHARED_LINKER_FLAGS         "${CHI_LINKER_FLAGS} ${CHI_SHARED_LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG   "${CHI_LINKER_FLAGS_DEBUG} ${CHI_SHARED_LINKER_FLAGS_DEBUG}")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CHI_LINKER_FLAGS_RELEASE} ${CHI_SHARED_LINKER_FLAGS_RELEASE}")

if ( NOT WITH_SYSTEM_BOOST )
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D BOOST_ALL_NO_LIB=1")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D BOOST_ALL_NO_LIB=1")
endif ( NOT WITH_SYSTEM_BOOST )

add_subdirectory(ChiikaAPI/ThirdParty)
add_subdirectory(ChiikaAPI)




message(STATUS "*** CONFIGURATION SETTINGS ***")
message(STATUS "Generator:                    ${CMAKE_GENERATOR}")
message(STATUS "Platform:                     ${CMAKE_SYSTEM_NAME}")
message(STATUS "Project architecture:         ${PROJECT_ARCH}")


if(${CMAKE_GENERATOR} STREQUAL "Ninja" OR ${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
  message(STATUS "Build type:                   ${CMAKE_BUILD_TYPE}")
endif()

message(STATUS "Standard libraries:           ${LIBRARIES}")

get_directory_property(DEFINITIONS COMPILE_DEFINITIONS)
message(STATUS "Compiler definitions:         ${DEFINITIONS}")

message(STATUS "C_FLAGS:                      ${CMAKE_C_FLAGS}")
message(STATUS "C_FLAGS_DEBUG:                ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "C_FLAGS_RELEASE:              ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "CXX_FLAGS:                    ${CMAKE_CXX_FLAGS}")
message(STATUS "CXX_FLAGS_DEBUG:              ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CXX_FLAGS_RELEASE:            ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "EXE_LINKER_FLAGS:             ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "EXE_LINKER_FLAGS_DEBUG:       ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
message(STATUS "EXE_LINKER_FLAGS_RELEASE:     ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
message(STATUS "SHARED_LINKER_FLAGS:          ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "SHARED_LINKER_FLAGS_DEBUG:    ${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")
message(STATUS "SHARED_LINKER_FLAGS_RELEASE:  ${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
