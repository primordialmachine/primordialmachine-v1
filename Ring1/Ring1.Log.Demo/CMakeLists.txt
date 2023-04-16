# Copyright (c) 2022 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyExecutable2("PrimordialMachine.Ring1.Log.Demo")
target_link_libraries("PrimordialMachine.Ring1.Log.Demo" "PrimordialMachine.Ring1")
