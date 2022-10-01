/// @file Runtime/Io/setFileContents.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO_SETFILECONTENTS_H_INCLUDED)
#define MACHINE_RUNTIME_IO_SETFILECONTENTS_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/Io/setFileContents.h` directly, include `_Runtime.h` instead.")
#endif

#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"

/// @brief Set the contents of a file.
/// @param path The path.
/// @param bytes The Bytes.
void Machine_setFileContents(Ring2_String* path, Machine_ByteBuffer* bytes);

#endif // MACHINE_RUNTIME_IO_SETFILECONTENTS_H_INCLUDED
