# Building under Visual Studio 2022/Windows 11
In the directory in which this file is located in,
you can find the folders containing solution files.
The following solution folders are available.
- `Scribe` containing `Scribe.sln`
- `Ring1` containing `Ring1.sln`
- `Ring2` containing `Ring2.sln`
- `Ring3` containing `Ring3.sln`

Open the solution file of your choice with Visual Studio 2022 and build the solution.

Build the artifacts for the desired platforms and configuration.

Depending on the solution you opened, you can find the build products in the `<directory>/products/<platform>/<configuration>/<project>`
where 
- `<directory>` is the directory containing the solution file
- `<platform>` is one of `x86` or `x64`
- `<configuration>` is one of `debug` or `release`
- `<project>` is the project in the solution
