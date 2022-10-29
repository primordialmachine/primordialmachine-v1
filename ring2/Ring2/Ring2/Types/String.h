// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/String.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_STRING_H_INCLUDED)
#define RING2_TYPES_STRING_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/String.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

#include "Ring2/Gc.h"

/// C level representation of a string.
typedef struct Ring2_String Ring2_String;

Ring1_Module_Declare(Ring2, StringModule)

/// @brief Create a string.
/// @param p, n The Bytes.
/// @return The string.
/// @error #Ring1_Status_InvalidArgument @a contextis a null pointer.
/// @error #Ring1_Status_InvalidArgument @a bytes is a null pointer.
/// @error #Ring1_Status_TooLong @a numberOfBytes exceeds a certain limit.
Ring1_CheckReturn() Ring2_String *
Ring2_String_create
  (
    char const* bytes,
    int64_t numberOfBytes
  );

/// @brief Concatenate string.
/// @param context A pointer to the context.
/// @param self A poiner to this string.
/// @param other A pointer to another string.
/// @return The string whcih is the concatenation of this string with the other string.
/// @error #Ring1_Status_InvalidArgument @a self is a null pointer.
/// @error #Ring1_Status_InvalidArgument @a other is a null pointer.
/// @error #Ring1_Status_TooLong The sum of the lengths of the strings exceeds a certain limit.
Ring1_CheckReturn() Ring2_String *
Ring2_String_concatenate
  (
    Ring2_Context* context,
    Ring2_String const* self,
    Ring2_String const* other
  );

/// @brief Get the Bytes of this string.
/// @param context A pointer to the context.
/// @param self A pointer to this string.
/// @return A pointer to the Bytes of this string.
/// @warning The pointer remains valid only as long as the string object is valid.
/// @warning The memory pointed to may not be modified.
Ring1_CheckReturn() char const *
Ring2_String_getBytes
  (
    Ring2_String const* self
  );

/// @brief Get the number of Bytes of this string.
/// @param context A pointer to the context.
/// @param self A pointer to this string.
/// @return The number of Bytes.
Ring1_CheckReturn() int64_t
Ring2_String_getNumberOfBytes
  (
    Ring2_String const* self
  );

/// @brief Get the hash value of this string.
/// @param context A pointer to the context.
/// @param self This string.
/// @return The hash value of this string.
Ring1_CheckReturn() int64_t
Ring2_String_getHashValue
  (
    Ring2_Context* context,
    Ring2_String const* self
  );

/// @brief Get the string representation of this string.
/// @param context A pointer to the context.
/// @param self This string.
/// @return The string representation of this string.
/// @remark The string representation of this string is this string itself.
Ring1_CheckReturn() Ring2_String*
Ring2_String_toString
  (
    Ring2_Context* context,
    Ring2_String const *self
  );

/// @brief Get the maximum number of Bytes of a string.
/// @return The maximum number of Bytes of a string.
Ring1_CheckReturn() int64_t
Ring2_String_getMaximumNumberOfBytes
  (
  );

#endif // Ring2_Configuration_withString

#endif // RING2_TYPES_STRING_H_INCLUDED
