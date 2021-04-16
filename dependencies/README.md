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
You can find the corresponding libraries in `build/Release/freetyped.lib` and `build/Debug/freetype.lib`, respectively.
You can find the required includes in `include`.
