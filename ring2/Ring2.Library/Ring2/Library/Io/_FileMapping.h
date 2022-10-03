// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/_FileMapping.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_IO__FILEMAPPING_H_INCLUDED)
#define RING2_LIBRARY_IO__FILEMAPPING_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Io/_FileMapping.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"
#include "Ring2/Library/Io/_FileHandle.h"

/// @brief Helper for file mappings.
typedef struct _Machine_FileMapping {
  _Machine_FileHandle fileHandle;
  HANDLE hFileMapping;
  char* bytes;
  size_t numberOfBytes;
} _Machine_FileMapping; // struct Nucleus_FileMapping

void
_Machine_FileMapping_openRead
  (
    _Machine_FileMapping* self,
    Ring2_String* path
  );

void
_Machine_FileMapping_openWrite
  (
    _Machine_FileMapping* self,
    Ring2_String* path,
    size_t numberOfBytes
  );

void
_Machine_FileMapping_close
  (
    _Machine_FileMapping* self
  );

#endif // RING2_LIBRARY_IO__FILEMAPPING_H_INCLUDED
