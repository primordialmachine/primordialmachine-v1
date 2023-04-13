# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
set(name "PrimordialMachine.Ring4.Demos")
MyExecutable(${name})
target_link_libraries(${name} "PrimordialMachine.Ring3.Graphics2")
target_link_libraries(${name} "PrimordialMachine.Ring3.Gui")
target_link_libraries(${name} "PrimordialMachine.Ring3.Input")
target_link_libraries(${name} "PrimordialMachine.Ring3.Text")
target_link_libraries(${name} "PrimordialMachine.Ring3.Visuals")
target_link_libraries(${name} "PrimordialMachine.Ring4.Scenes")
target_link_libraries(${name} "PrimordialMachine.Ring3.Launcher")
