# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
set(name "PrimordialMachine.Ring3.Gui")
MyLibrary2(${name})
target_link_libraries(${name} "PrimordialMachine.Ring3.Gdl")
target_link_libraries(${name} "PrimordialMachine.Ring3.Text")
target_link_libraries(${name} "PrimordialMachine.Ring3.Graphics2")
target_link_libraries(${name} "PrimordialMachine.Ring3.Signals")
target_link_libraries(${name} "PrimordialMachine.Ring3.Math")
