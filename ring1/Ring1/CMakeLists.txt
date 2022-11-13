# Copyright (c) 2022 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

set(name "PrimordialMachine.Ring1")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(STATUS "Architecture: X64")
  file(GLOB_RECURSE asm_files "${CMAKE_CURRENT_SOURCE_DIR}/Ring1/Intrinsic/*/X64/*.asm")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
  message(STATUS "Architecture: X86")
  file(GLOB_RECURSE asm_files "${CMAKE_CURRENT_SOURCE_DIR}/Ring1/Intrinsic/*/X86/*.asm")
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${asm_files})
message(STATUS "ASM: ${asm_files}")
#Enable ASM provided by MASM
enable_language(ASM_MASM)

file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files})

file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${header_files})

file(GLOB_RECURSE inlay_files  "${CMAKE_CURRENT_SOURCE_DIR}/*.i")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inlay_files})

set(files ${source_files} ${header_files} ${inlay_files} ${asm_files})

add_library(${name} STATIC ${files})
target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
