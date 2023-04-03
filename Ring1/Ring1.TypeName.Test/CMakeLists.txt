# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyExecutable("PrimordialMachine.Ring1.TypeName.Test")
target_link_libraries("PrimordialMachine.Ring1.TypeName.Test" "PrimordialMachine.Ring1")
