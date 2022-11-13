# Building under CMake/Visual Studio 2022/Windows 11
This document describes how to build *Primordial Machine*
using *CMake*, *Microsoft Visual Studio 2022*, and *Microsoft Windows 11*.

## Prerequisites
Please make sure you have a recent *CMake* version installed.
This document assumes *CMake* is in your path.
To test if *CMake* is in your path, simply open a console and enter
```
cmake --version
```
You should see an output similar to
```
cmake version 3.24.1

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```
Important: *Primordial Machine* requires *CMake* version 3.20 or higher.

# Generating and build
Open a console and switch to the directory in which this file is located in.
We describe the process of an out-of-source build.
Enter the parent directory by entering `..`.
Create a directory called `primordialmachine-build` for the build by entering `mkdir primordialmachine-build`.
Enter that directory by `cd primordialmachine-build`.
Generate the Visual Studio solution file and the project files by entering `cmake ./../primordialmachine`.
Open the Visual Studio solution file `primordialmachine.sln` that was generated in the director in which this file is located in.
Build the desired libraries and executables.
