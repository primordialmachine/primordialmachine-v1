# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
set(name "PrimordialMachine.Ring3.Fonts.FreeType2")
MyLibrary2(${name})

# LIBPNG.
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  #message("compiling for x64")
  target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/libpng/x64/include")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  #message("compiling for x86")
  target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/libpng/x86/include")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()

target_link_libraries(${name} "PrimordialMachine.Ring3.Visuals")
