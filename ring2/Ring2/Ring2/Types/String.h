// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/String.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_STRING_H_INCLUDED)
#define RING2_TYPES_STRING_H_INCLUDED

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

#include "Ring1/Result.h"
#include "Ring2/Gc.h"
#include "Ring2/Context.h"

/// C level representation of a string.
typedef struct Ring2_String Ring2_String;

Ring1_CheckReturn() Ring1_Result
Ring2_StringModule_startup
  (
  );

void
Ring2_StringModule_shutdown
  (
  );

void
Ring2_StringModule_preMarkCallback
  (
    Ring2_Gc* gc,
    void* context
  );

void
Ring2_StringModule_sweepCallback
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  );

/// @brief Create a string.
/// @param p, n The Bytes.
/// @return The string.
/// @error #Machine_Status_ArgumentNull @a p is a null pointer.
/// @error #Machine_Status_TooLong @a n exceeds a certain limit.
Ring1_CheckReturn() Ring2_String *
Ring2_String_create
  (
    char const* p,
    size_t n
  );

/// @brief Create a string.
/// @param p, n The Bytes.
/// @return The string.
/// @error #Machine_Status_ArgumentNull @a self is a null pointer.
/// @error #Machine_Status_ArgumentNull @a other is a null pointer.
/// @error #Machine_Status_TooLong The sum of the lengths of the strings exceeds a certain limit.
Ring1_CheckReturn() Ring2_String *
Ring2_String_concatenate
  (
    Ring2_String const* self,
    Ring2_String const* other
  );

/// @brief Get the hash value of this string.
/// @param self This string.
/// @return The hash value of this string.
Ring1_CheckReturn() int64_t
Ring2_String_getHashValue
  (
    Ring2_Context* context,
    Ring2_String const* self
  );

/// @brief Get the Bytes of this string.
/// @param self A pointer to this string.
/// @return A pointer to the Bytes of this string.
/// @warning The pointer remains valid only as long as the string object is valid.
/// @warning The memory pointed to may not be modified.
Ring1_CheckReturn() char const *
Ring2_String_getBytes
  (
    Ring2_Context* context,
    Ring2_String const* self
  );

/// @brief Get the number of Bytes of this string.
/// @param self A pointer to this string.
/// @return The number of Bytes.
Ring1_CheckReturn() size_t
Ring2_String_getNumberOfBytes
  (
    Ring2_Context* context,
    Ring2_String const* self
  );

#endif // Ring2_Configuration_withString

#endif // RING2_TYPES_STRING_H_INCLUDED
