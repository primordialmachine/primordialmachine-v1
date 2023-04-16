# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
set(name "PrimordialMachine.Scribe.Cas")
MyLibrary2(${name})
target_link_libraries(${name} "PrimordialMachine.Scribe.Core")
