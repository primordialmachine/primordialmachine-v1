// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/setFileContents.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_IO_SETFILECONTENTS_H_INCLUDED)
#define RING2_LIBRARY_IO_SETFILECONTENTS_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Io/setFileContents.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"
#include "Ring2/Library/ByteBuffer.h"

/// @brief Set the contents of a file.
/// @param path The path.
/// @param bytes The Bytes.
void
Machine_setFileContents
  (
    Ring2_String* path,
    Ring2_ByteBuffer* bytes
  );

#endif // RING2_LIBRARY_IO_SETFILECONTENTS_H_INCLUDED
