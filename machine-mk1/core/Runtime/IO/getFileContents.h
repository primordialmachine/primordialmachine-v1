/// @file Runtime/IO/getFileContents.h`
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO_GETFILECONTENTS_H_INCLUDED)
#define MACHINE_RUNTIME_IO_GETFILECONTENTS_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "Runtime/String.h"
#include "Runtime/ByteBuffer.h"

/// @brief Get the contents of a file.
/// @param path The path.
/// @return The contents.
Machine_ByteBuffer *Machine_getFileContents(Machine_String *path);

#endif // MACHINE_RUNTIME_IO_GETFILECONTENTS_H_INCLUDED
