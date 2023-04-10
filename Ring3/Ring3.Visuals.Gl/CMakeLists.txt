# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

# Define a static library.
# name The name of the library e.g. "PrimordialMachine.Ring2".
function(MyLibrary2 name)

  file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.c")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${source_files})

  file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.h")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${header_files})

  file(GLOB_RECURSE inlay_files  "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.i")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${inlay_files})
  
  set(files ${source_files} ${header_files} ${inlay_files})
  
  add_library(${name} STATIC ${files})
  
  target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
  
  if(MSVC)
    # Treat certain warnings as errors.
    target_compile_options(${name} PRIVATE "/we4133")
    target_compile_options(${name} PRIVATE "/we4090")
    target_compile_options(${name} PRIVATE "/we4013")
  endif()
    
endfunction()

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyLibrary2("PrimordialMachine.Ring4.Visuals.Gl")

# GLFW.
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  message("compiling for x64")
  target_include_directories("PrimordialMachine.Ring4.Visuals.Gl" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/x64/include")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  message("compiling for x86")
  target_include_directories("PrimordialMachine.Ring4.Visuals.Gl" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/x86/include")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()

# GLAD.
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  message("compiling for x64")
  target_include_directories("PrimordialMachine.Ring4.Visuals.Gl" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  message("compiling for x86")
  target_include_directories("PrimordialMachine.Ring4.Visuals.Gl" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")
else()
  message(FATAL_ERROR "unknown/unsupported/not yet supported target architecture")
endif()

#target_link_libraries("PrimordialMachine.Ring4.Visuals.Gl" "PrimordialMachine.Ring2.Library")
target_link_libraries("PrimordialMachine.Ring4.Visuals.Gl" "PrimordialMachine.Ring3.Visuals")
