# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyExecutable2("PrimordialMachine.Ring2.Library.Test")
target_link_libraries("PrimordialMachine.Ring2.Library.Test" "PrimordialMachine.Ring2.Library")
