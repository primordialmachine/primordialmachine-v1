/// @file Runtime/IO.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO_H_INCLUDED)
#define MACHINE_RUNTIME_IO_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "./../Machine.h"
#include <stdio.h>

/// @brief Open a file for reading.
/// @param path The path.
/// @return The file descriptor.
/// @error #Machine_Status_InvalidArgument @a path is null
/// @error #Machine_Status_EnvironmentFailed unable to open the file for reading. 
FILE* Machine_openFileRead(Machine_String* path);

void Machine_closeFile(FILE* fd);

#endif // MACHINE_RUNTIME_IO_H_INCLUDED
