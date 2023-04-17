/// @file Ring3/Audials/Backends/OpenAL/OpenAL.h
/// @copyright Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @brief OpenAL Backed.
/// See https://www.openal-soft.org/ for more information on OpenAL.

#if !defined(RING3_AUDIALS_BACKENDS_OPENAL_OPENAL_H_INCLUDED)
#define RING3_AUDIALS_BACKENDS_OPENAL_OPENAL_H_INCLUDED

#include "Ring3/Audials/Configuration.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_OpenAL

#include <stddef.h>

// for "bool", "true", "false".
#include <stdbool.h>

#include "Ring3/Audials/_Include.h"
#include "Ring3/Audials/Backends/PcmDescriptor.h"

/// @brief A buffer.
typedef struct _Buffer _Buffer;

/// @brief A source.
typedef struct _Source _Source;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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

// @brief Increment the reference count of a buffer.
// @param buffer A pointer to the buffer.
void
_Buffer_ref
  (
    _Buffer* buffer
  );

// @brief Decrement the reference count of a buffer.
// @param buffer A pointer to the buffer.
void
_Buffer_unref
  (
    _Buffer* buffer
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// @brief Attach a buffer to a source.
// @param source The source
// qparam buffer The buffer.
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

// @brief Increment the reference count of a source.
// @param source A pointer to the source.
void
_Source_ref
  (
    _Source* source
  );

// @brief Decrement the reference count of a source.
// @param source A pointer to the source.
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int
_startup
  (
  );

void
_shutdown
  (
  );

#endif

#endif // RING3_AUDIALS_BACKENDS_OPENAL_OPENAL_H_INCLUDED
