# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
set(name "PrimordialMachine.Ring3.Text")
MyLibrary2(${name})
target_link_libraries(${name} "PrimordialMachine.Ring2.Library")
target_link_libraries(${name} "PrimordialMachine.Ring3.Visuals")
target_link_libraries(${name} "PrimordialMachine.Ring3.Graphics2")
