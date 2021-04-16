## Building GLFW
Enter the `glfw-3.3.4` directory.
Type `cmake -E make_directory build`.
Type `cmake -E chdir build cmake ..`.
Open `build/GLFW.sln`.
Perform the release and debug builds.
You can find the corresponding libraries `build/src/Release/glfw3.lib` and `build/src/Debug/glfw3.lib`, respectively.
You can find the required includes in `include`.

## Building FreeType
Enter the `freetype-2.9.1` directory.
Type `cmake -E make_directory build`.
Type `cmake -E chdir build cmake ..`.
Open `build/freetype.sln`.
Perform the release and debug builds.
You can find the corresponding libraries in `build/Release/freetype.lib` and `build/Debug/freetyped.lib`, respectively.
You can find the required includes in `include`.

## Building zlib
Enter the `zlib-1.2.11` directory.
Type `cmake .`.
Open `zlib.sln`.
Perform the release and debug builds.
You can find the corresponding libraries `Release/zlibstatic.lib` and `Debug/zlibstaticd.lib`, respectively.
You can find the required includes in `.`.

## Building LibPNG
Enter the `zlib-1.2.11` directory.

Edit CMakeLists and change
```
option(PNG_BUILD_ZLIB "Custom zlib Location, else find_package is used" OFF)

if(NOT PNG_BUILD_ZLIB)
  find_package(ZLIB REQUIRED)
  include_directories(${ZLIB_INCLUDE_DIR})
endif()
```
to
```
set(ZLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/./../zlib-1.2.11)
set(ZLIB_LIBRARY optimized ${CMAKE_SOURCE_DIR}/./../zlib-1.2.11/build/Release/zlibstatic.lib debug ${CMAKE_SOURCE_DIR}/./../zlib-1.2.11/build/Debug/zlibstaticd.lib)

#option(PNG_BUILD_ZLIB "Custom zlib Location, else find_package is used" OFF)

#if(NOT PNG_BUILD_ZLIB)
  #find_package(ZLIB REQUIRED)
  include_directories(${ZLIB_INCLUDE_DIR})
#endif()
```
Type `cmake -E make_directory build`.
Type `cmake -E chdir build cmake ..`.
Open `build/libpng.sln`.
Perform the release and debug builds.
You can find the corresponding libraries `Release/libpng16.lib` and `Debug/libpng16d.lib`, respectively.
You can find the required includes in `.` and `./build`.
