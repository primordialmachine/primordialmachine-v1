/// @file Ring3/Audials/Demo/Backends/Buffer.h
/// @copyright Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @brief Part of the interface of an audio backend.

#if !defined(RING3_AUDIALS_BACKENDS_BUFFER_H_INCLUDED)
#define RING3_AUDIALS_BACKENDS_BUFFER_H_INCLUDED

#include "Ring3/Audials/Backends/PcmDescriptor.h"


/// @brief A buffer.
typedef struct _Buffer _Buffer;

/// @brief Create a buffer.
/// @param source A pointer to a <code>_Source*</code> variable.
/// @param p, n The audio data. @a p is a pointer to an array of size @a n.
/// @return @a 0 on success. A non-zero value on failure.
/// @post <code>*buffer</code> wa assigned a pointer to the source.
/// @remarks The array @a p is pointing to is not required after the call to this function terminates.
int
_Buffer_create
  (
    _Buffer** buffer,
    _PcmDescriptor const* pcmDescriptor,
    void* p,
    size_t n
  );

/// @brief Increment the reference count of a buffer.
/// @param buffer A pointer to the buffer.
void
_Buffer_ref
  (
    _Buffer* buffer
  );

/// @brief Decrement the reference count of a buffer.
/// @param buffer A pointer to the buffer.
void
_Buffer_unref
  (
    _Buffer* buffer
  );


#endif // RING3_AUDIALS_BACKENDS_BUFFER_H_INCLUDED
