# Copyright (c) 2022 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

set(name "PrimordialMachine.Ring1.Console.Demo")

file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files})

file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${header_files})

file(GLOB_RECURSE inlay_files  "${CMAKE_CURRENT_SOURCE_DIR}/*.i")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inlay_files})

set(files ${source_files} ${header_files} ${inlay_files})

add_executable(${name} ${files})
target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${name} "PrimordialMachine.Ring1")
