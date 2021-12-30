/// @file Runtime/Io/_FileMapping.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO__FILEMAPPING_H_INCLUDED)
#define MACHINE_RUNTIME_IO__FILEMAPPING_H_INCLUDED

#include "Runtime/IO/_FileHandle.h"
#include "Runtime/Status.h"

/// @brief Helper for file mappings.
typedef struct _Machine_FileMapping {
  _Machine_FileHandle fileHandle;
  HANDLE hFileMapping;
  char* bytes;
  size_t numberOfBytes;
} _Machine_FileMapping; // struct Nucleus_FileMapping

void _Machine_FileMapping_openRead(_Machine_FileMapping* self, Machine_String* path);

void _Machine_FileMapping_openWrite(_Machine_FileMapping* self, Machine_String* path,
                                                  size_t numberOfBytes);

void _Machine_FileMapping_close(_Machine_FileMapping* self);

#endif // MACHINE_RUNTIME_IO__FILEMAPPING_H_INCLUDED
