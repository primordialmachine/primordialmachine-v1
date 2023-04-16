# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
set(name "PrimordialMachine.Ring3.ImagesTranscoders.LibPng")
MyLibrary2(${name})

###################################################################################################
# LIBPNG.
# Create target for the "LibPng" library.
add_library(libpng STATIC IMPORTED)
set(prefix "${CMAKE_CURRENT_SOURCE_DIR}/external/libpng")
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  #message("compiling for x64")
  set(infix "x64")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  #message("compiling for x86")
  set(infix "x86")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()
# Set path to include files for target "libpng".
target_include_directories(libpng INTERFACE "${prefix}/${infix}/include")
# Set path to library file for target "libpng".
set_target_properties(libpng PROPERTIES IMPORTED_LOCATION_RELEASE "${prefix}/${infix}/release/libpng16_static.lib")
set_target_properties(libpng PROPERTIES IMPORTED_LOCATION_RELWITHDEBINFO "${prefix}/${infix}/release/libpng16_static.lib")
set_target_properties(libpng PROPERTIES IMPORTED_LOCATION_MINSIZEREL "${prefix}/${infix}/release/libpng16_static.lib")
set_target_properties(libpng PROPERTIES IMPORTED_LOCATION_DEBUG "${prefix}/${infix}/debug/libpng16_staticd.lib")
###################################################################################################

target_link_libraries(${name} "PrimordialMachine.Ring3.Visuals" "libpng")
