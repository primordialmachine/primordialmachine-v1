# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyExecutable2("PrimordialMachine.Ring3.Audials.Demo")
target_link_libraries("PrimordialMachine.Ring3.Audials.Demo" "PrimordialMachine.Ring3.Audials")

add_custom_command(TARGET "PrimordialMachine.Ring3.Audials.Demo" POST_BUILD # add post build event to target
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
                   $<TARGET_RUNTIME_DLLS:PrimordialMachine.Ring3.Audials.Demo> # to copy each file in the generator expression
                   $<TARGET_FILE_DIR:PrimordialMachine.Ring3.Audials.Demo> # to the specified target directory
                   COMMAND_EXPAND_LISTS)  
