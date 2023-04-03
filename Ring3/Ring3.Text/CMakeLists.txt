# Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/PrimordialMachine.cmake")
MyLibrary("PrimordialMachine.Ring3.Text")
target_link_libraries("PrimordialMachine.Ring3.Text" "PrimordialMachine.Ring2.Library")
target_link_libraries("PrimordialMachine.Ring3.Text" "PrimordialMachine.Ring3.Visuals")
target_link_libraries("PrimordialMachine.Ring3.Text" "PrimordialMachine.Ring3.Graphics2")
