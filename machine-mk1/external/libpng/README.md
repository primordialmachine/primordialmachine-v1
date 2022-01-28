Download release 1.2.11 of Zlib from
`https://www.zlib.net/`.
Unpack zlib to `<root>/zlib`.

Download release 1.6.37 of LibPng from
`https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/`.
Unpack libpng to `<root>/libpng`.

## Install CMake
Install CMake.

## Building
Edit `libpng\CMakeLists.txt`.

Change the line
```
option(PNG_BUILD_ZLIB "Custom zlib Location, else find_package is used" OFF)
```
to the lines
```
option(PNG_BUILD_ZLIB "Custom zlib Location, else find_package is used" ON)
```

Change the lines
```
option(PNG_SHARED "Build shared lib" ON)
```
and
```
option(PNG_TESTS  "Build libpng tests" ON)
```
to 
```
option(PNG_SHARED "Build shared lib" OFF)
```
and
```
option(PNG_TESTS  "Build libpng tests" OFF)
```

## Building for x64

Create the following `CMakeLists.txt` in the directory containing both the `zlib` and `libpng` folders.
```
cmake_minimum_required(VERSION 3.1)
cmake_policy(VERSION 3.1)

add_subdirectory(zlib)
set(ZLIB_INCLUDE_DIR ".\\..\\x64\\zlib" ".\\..\\zlib")
add_subdirectory(libpng)
```

Execute
- `mkdir x64`
- `cd x64`
- `cmake -A x64 ..`
Now you can build the release and debug static libraries.

## Building for x86
Create the following `CMakeLists.txt` in the directory containing both the `zlib` and `libpng` folders.
```
cmake_minimum_required(VERSION 3.1)
cmake_policy(VERSION 3.1)

add_subdirectory(zlib)
set(ZLIB_INCLUDE_DIR ".\\..\\x86\\zlib" ".\\..\\zlib")
add_subdirectory(libpng)
```

Execute
- `mkdir x86`
- `cd x86`
- `cmake -A Win32 ..`
Now you can build the release and debug static libraries.
