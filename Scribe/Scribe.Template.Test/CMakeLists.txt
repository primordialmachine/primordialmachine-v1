# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
set(name "PrimordialMachine.Scribe.Template.Test")
MyExecutable2(${name})
target_link_libraries(${name} "PrimordialMachine.Scribe.Template")
set_property(TARGET ${name} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Data")
