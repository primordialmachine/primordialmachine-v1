# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyExecutable2("PrimordialMachine.Ring3.Gdl.Test")
target_link_libraries("PrimordialMachine.Ring3.Gdl.Test" "PrimordialMachine.Ring3.Gdl")
