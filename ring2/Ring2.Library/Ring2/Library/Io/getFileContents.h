// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/getFileContents.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_IO_GETFILECONTENTS_H_INCLUDED)
#define RING2_LIBRARY_IO_GETFILECONTENTS_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Io/getFileContents.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"
#include "Ring2/Library/ByteBuffer.h"

/// @brief Get the contents of a file.
/// @param path The path.
/// @return The contents.
Machine_ByteBuffer *
Machine_getFileContents
  (
    Ring2_String *path
  );

#endif // RING2_LIBRARY_IO_GETFILECONTENTS_H_INCLUDED
