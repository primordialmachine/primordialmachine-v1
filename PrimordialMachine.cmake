# Define a static library.
# name The name of the library e.g. "PrimordialMachine.Ring2".
function(MyLibrary name)

  file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files})

  file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${header_files})

  file(GLOB_RECURSE inlay_files  "${CMAKE_CURRENT_SOURCE_DIR}/*.i")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inlay_files})
  
  set(files ${source_files} ${header_files} ${inlay_files})
  
  add_library(${name} STATIC ${files})
  
  target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  
  if(MSVC)
    # Treat certain warnings as errors.
    target_compile_options(${name} PRIVATE "/we4133")
    target_compile_options(${name} PRIVATE "/we4090")
    target_compile_options(${name} PRIVATE "/we4013")
  endif()
    
endfunction()

# Define an executable.
# name The name of the executable e.g. "PrimordialMachine.Ring2.Test".
function(MyExecutable name)

  file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files})

  file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${header_files})

  file(GLOB_RECURSE inlay_files  "${CMAKE_CURRENT_SOURCE_DIR}/*.i")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inlay_files})
  
  set(files ${source_files} ${header_files} ${inlay_files})
  
  add_executable(${name} ${files})
  
  target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  
  if(MSVC)
    # Treat certain warnings as errors.
    target_compile_options(${name} PRIVATE "/we4133")
    target_compile_options(${name} PRIVATE "/we4090")
    target_compile_options(${name} PRIVATE "/we4013")
  endif()
    
endfunction()

# Define a static library.
# name The name of the library e.g. "PrimordialMachine.Ring2".
# Remark: This is the new version of "MyLibrary" and should soon replace all calls to "MyLibrary".
function(MyLibrary2 name)

  file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.c")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${source_files})

  file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.h")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${header_files})

  file(GLOB_RECURSE inlay_files  "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.i")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${inlay_files})
  
  set(files ${source_files} ${header_files} ${inlay_files})
  
  add_library(${name} STATIC ${files})
  
  target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
  
  if(MSVC)
    # Treat certain warnings as errors.
    target_compile_options(${name} PRIVATE "/we4133")
    target_compile_options(${name} PRIVATE "/we4090")
    target_compile_options(${name} PRIVATE "/we4013")
  endif()
    
endfunction()

# Define an executable.
# name The name of the executable e.g. "PrimordialMachine.Ring2.Test".
# Remark: This is the new version of "MyExecutable" and should soon replace all calls to "MyExecutable".
function(MyExecutable2 name)

  file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.c")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${source_files})

  file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.h")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${header_files})

  file(GLOB_RECURSE inlay_files  "${CMAKE_CURRENT_SOURCE_DIR}/*.i")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sources FILES ${inlay_files})
  
  set(files ${source_files} ${header_files} ${inlay_files})
  
  add_executable(${name} ${files})
  
  target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
  
  if(MSVC)
    # Treat certain warnings as errors.
    target_compile_options(${name} PRIVATE "/we4133")
    target_compile_options(${name} PRIVATE "/we4090")
    target_compile_options(${name} PRIVATE "/we4013")
  endif()
    
endfunction()