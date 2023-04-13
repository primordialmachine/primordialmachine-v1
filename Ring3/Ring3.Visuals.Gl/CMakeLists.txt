# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
set(name "PrimordialMachine.Ring3.Visuals.Gl")
MyLibrary2(${name})


# GLFW.
# Create target for the "GLFW" library.
add_library(glfw STATIC IMPORTED)
set(prefix "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw")
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  #message("compiling for x64")
  set(infix "x64")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  #message("compiling for x86")
  set(infix "x86")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()
# Set path to include files for target "glfw".
target_include_directories(${name} PRIVATE "${prefix}/${infix}/include")
# Set path to library file for target "glfw".
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION_RELEASE "${prefix}/${infix}/release/glfw3.lib")
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION_RELWITHDEBINFO "${prefix}/${infix}/release/glfw3.lib")
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION_MINSIZEREL "${prefix}/${infix}/release/glfw3.lib")
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION_DEBUG "${prefix}/${infix}/debug/glfw3.lib")

# GLAD.
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  #message("compiling for x64")
  target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")
  target_sources(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  #message("compiling for x86")
  target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")
  target_sources(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()


target_link_libraries(${name} "PrimordialMachine.Ring3.Visuals" "glfw")
