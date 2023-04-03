# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyLibrary("PrimordialMachine.Ring2.Library")
target_link_libraries("PrimordialMachine.Ring2.Library" "PrimordialMachine.Ring2")
