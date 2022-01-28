Download release 2.11.1 of FreeType 2 from
`https://download.savannah.gnu.org/releases/freetype/`.

Install CMake.

Execute
- `mkdir x64`
- `cd x64`
- `cmake -A x64 ..`
Now you can build the release and debug static libraries.

Execute
- `mkdir x86`
- `cd x86`
- `cmake -A Win32 ..`
Now you can build the release and debug static libraries.
