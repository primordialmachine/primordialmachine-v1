/// @file Ring3/Audials/Demo/Backends/Source.h
/// @copyright Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @brief Part of the interface of an audio backend.

#if !defined(RING3_AUDIALS_BACKENDS_SOURCE_H_INCLUDED)
#define RING3_AUDIALS_BACKENDS_SOURCE_H_INCLUDED

#include "Ring3/Audials/Backends/PcmDescriptor.h"


/// @brief A source.
typedef struct _Source _Source;

/// @brief Attach a buffer to a source.
/// @param source The source
/// @param buffer The buffer.
int
_Source_attach
  (
    _Source* source,
    _Buffer* buffer
  );

int
_Source_play
  (
    _Source* source
  );

int
_Source_isPlaying
  (
    bool* playing,
    _Source* source
  );

/// @brief Increment the reference count of a source.
/// @param source A pointer to the source.
void
_Source_ref
  (
    _Source* source
  );

/// @brief Decrement the reference count of a source.
/// @param source A pointer to the source.
void
_Source_unref
  (
    _Source* source
  );

/// @brief Create a source.
/// @param source A pointer to a <code>_Source*</code> variable.
/// @return @a 0 on success. A non-zero value on failure.
/// @post <code>*source</code> wa assigned a pointer to the source.
/// @remarks The PCM descriptor object is not required after the call to this function terminates.
int
_Source_create
  (
    _Source** source
  );


#endif // RING3_AUDIALS_BACKENDS_SOURCE_H_INCLUDED
