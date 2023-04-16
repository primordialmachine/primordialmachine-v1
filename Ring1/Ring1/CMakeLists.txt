# Copyright (c) 2022 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

set(name "PrimordialMachine.Ring1")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(STATUS "Architecture: X64")
  file(GLOB_RECURSE asm_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Ring1/Intrinsic/*/X64/*.asm")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
  message(STATUS "Architecture: X86")
  file(GLOB_RECURSE asm_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Ring1/Intrinsic/*/X86/*.asm")
  set_source_files_properties(
      ${asm_files}
      PROPERTIES
      COMPILE_FLAGS "/safeseh"
  )
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${asm_files})
message(STATUS "ASM: ${asm_files}")
#Enable ASM provided by MASM
enable_language(ASM_MASM)

file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.c")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${source_files})

file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.h")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${header_files})

file(GLOB_RECURSE inlay_files  "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.i")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${inlay_files})

set(files ${source_files} ${header_files} ${inlay_files} ${asm_files})

add_library(${name} STATIC ${files})
target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
