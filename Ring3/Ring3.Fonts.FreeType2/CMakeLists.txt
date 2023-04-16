# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
set(name "PrimordialMachine.Ring3.Fonts.FreeType2")
MyLibrary2(${name})

###################################################################################################
# ZLIB.
# Create target for the "zLib" library.
add_library(zlib STATIC IMPORTED)
set(prefix "${CMAKE_CURRENT_SOURCE_DIR}/external/zlib/")
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  #message("compiling for x64")
  set(infix "x64")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  #message("compiling for x86")
  set(infix "x86")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()
# Set path to include files for target "zlib".
target_include_directories(zlib INTERFACE "${prefix}/${infix}/include")
# Set path to library file for target "zlib".
set_target_properties(zlib PROPERTIES IMPORTED_LOCATION_RELEASE "${prefix}/${infix}/release/zlibstatic.lib")
set_target_properties(zlib PROPERTIES IMPORTED_LOCATION_RELWITHDEBINFO "${prefix}/${infix}/release/zlibstatic.lib")
set_target_properties(zlib PROPERTIES IMPORTED_LOCATION_MINSIZEREL "${prefix}/${infix}/release/zlibstatic.lib")
set_target_properties(zlib PROPERTIES IMPORTED_LOCATION_DEBUG "${prefix}/${infix}/debug/zlibstaticd.lib")
###################################################################################################

###################################################################################################
# FREETYPE2.
# Create target for the "FreeType 2" library.
add_library(freetype2 STATIC IMPORTED)
set(prefix "${CMAKE_CURRENT_SOURCE_DIR}/external/freetype")
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  #message("compiling for x64")
  set(infix "x64")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  #message("compiling for x86")
  set(infix "x86")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()
# Set path to include files for target "freetype2".
target_include_directories(freetype2 INTERFACE "${prefix}/${infix}/include")
# Set path to library file for target "freetype2".
set_target_properties(freetype2 PROPERTIES IMPORTED_LOCATION_RELEASE "${prefix}/${infix}/release/freetype.lib")
set_target_properties(freetype2 PROPERTIES IMPORTED_LOCATION_RELWITHDEBINFO "${prefix}/${infix}/release/freetype.lib")
set_target_properties(freetype2 PROPERTIES IMPORTED_LOCATION_MINSIZEREL "${prefix}/${infix}/release/freetype.lib")
set_target_properties(freetype2 PROPERTIES IMPORTED_LOCATION_DEBUG "${prefix}/${infix}/debug/freetyped.lib")
###################################################################################################

target_link_libraries(${name} "PrimordialMachine.Ring3.Visuals" "zlib" "freetype2")
