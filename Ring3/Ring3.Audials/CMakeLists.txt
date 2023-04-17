# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyLibrary2("PrimordialMachine.Ring3.Audials")
target_link_libraries("PrimordialMachine.Ring3.Audials" "PrimordialMachine.Ring2.Library")

###################################################################################################
# OPENAL.
# Create target for the "OpenAL" library.
add_library(openal STATIC IMPORTED)
set(prefix "${CMAKE_CURRENT_SOURCE_DIR}/external/openal")
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  #message("compiling for x64")
  set(infix "x64")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  #message("compiling for x86")
  set(infix "x86")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()
# Set path to include files for target "openal".
target_include_directories(openal INTERFACE "${prefix}/include")
# Set path to library file for target "openal".
set_target_properties(openal PROPERTIES IMPORTED_LOCATION_RELEASE "${prefix}/lib/openal32.lib")
set_target_properties(openal PROPERTIES IMPORTED_LOCATION_RELWITHDEBINFO "${prefix}/lib/openal32.lib")
set_target_properties(openal PROPERTIES IMPORTED_LOCATION_MINSIZEREL "${prefix}/lib/openal32.lib")
set_target_properties(openal PROPERTIES IMPORTED_LOCATION_DEBUG "${prefix}/lib/openal32.lib")
###################################################################################################

target_link_libraries("PrimordialMachine.Ring3.Audials" "openal")
