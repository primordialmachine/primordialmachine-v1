# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyLibrary2("PrimordialMachine.Ring4.Visuals.Gl")

# GLFW.
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  #message("compiling for x64")
  target_include_directories("PrimordialMachine.Ring4.Visuals.Gl" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/x64/include")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  #message("compiling for x86")
  target_include_directories("PrimordialMachine.Ring4.Visuals.Gl" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/x86/include")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()

# GLAD.
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  #message("compiling for x64")
  target_include_directories("PrimordialMachine.Ring4.Visuals.Gl" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  #message("compiling for x86")
  target_include_directories("PrimordialMachine.Ring4.Visuals.Gl" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()

target_link_libraries("PrimordialMachine.Ring4.Visuals.Gl" "PrimordialMachine.Ring3.Visuals")
